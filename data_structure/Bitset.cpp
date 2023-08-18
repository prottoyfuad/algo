  
#include <vector>
#include <cassert>
#include <iostream>
#include <functional>

using i64 = long long;
using u64 = unsigned long long;

class Bitset {
private:
  i64 N, B;
  std::vector<u64> bits;

  // Reset all extra bits after N.
  void _clean() {
    if (N != B * 64) {
      bits.back() &= (1LLU << (N - 64 * (B - 1))) - 1;
    }
  }

  Bitset& _composition(const Bitset& other, 
                       const std::function<void(u64&, const u64&)>& fun) {
    assert(N == other.N);
    for (int i = 0; i < B; i++) {
      fun(bits[i], other.bits[i]);
    }        
    return *this;
  }

public:
  Bitset(i64 n = 0) {
    init(n);
  }

  void init(i64 n) {
    N = n;
    B = (N + 63) / 64;
    bits.assign(B, 0);
  }

  void clear() {
    N = B = 0;
    bits.clear();
  }

  void reset() {
    bits.assign(B, 0);
  }

  bool get(i64 index) const {
    return bits[index >> 6] >> (index & 63) & 1;
  }

  void set(i64 index, bool value) {
    assert(0 <= index && index < N);
    bits[index >> 6] &= ~(1LLU << (index & 63));
    bits[index >> 6] |= u64(value) << (index & 63);
  }

  void flip(i64 index = -1) {
    if (index != -1) {
      set(index, !get(index));
      return;
    }
    for (i64 i = 0; i < B; i++) {
      bits[i] ^= -1LL;
    }
    _clean();
  }

  Bitset& operator&=(const Bitset& other) {
    return _composition(other, [](u64& to, const u64& from) {
      to &= from;
    });
  }

  Bitset& operator|=(const Bitset& other) {
    return _composition(other, [](u64& to, const u64& from) {
      to |= from;
    });
  }

  Bitset& operator^=(const Bitset& other) {
    return _composition(other, [](u64& to, const u64& from) {
      to ^= from;
    });
  }

  Bitset& operator<<=(i64 shift) {
    i64 div = shift >> 6;
    i64 mod = shift & 63;
    if (mod == 0) {
      for (i64 i = B - 1; i >= div; i--) {
        bits[i] = bits[i - div];
      }      
    }
    else {
      for (i64 i = B - 1; i >= div + 1; i--) {
        bits[i] = bits[i - (div + 1)] >> (64 - mod) | bits[i - div] << mod;
      }
      if (div < B) {
        bits[div] = bits[0] << mod;
      }        
    }  
    for (i64 i = 0; i < div; i++) {
      bits[i] = 0;
    }     
    _clean();   
    return *this;
  }

  // Simulates bs |= bs << shift
  void or_shift_left(i64 shift) {
    i64 div = shift >> 6;
    i64 mod = shift & 63;
    if (mod == 0) {
      for (i64 i = B - 1; i >= div; i--) {
        bits[i] |= bits[i - div];
      }      
    } else {
      for (i64 i = B - 1; i >= div + 1; i--) {
        bits[i] |= bits[i - (div + 1)] >> (64 - mod) | bits[i - div] << mod;
      }
      if (div < B) {
        bits[div] |= bits[0] << mod;
      }
    }
    _clean();
  }
                                  
  Bitset& operator>>=(i64 shift) {
    i64 div = shift >> 6;
    i64 mod = shift & 63;
    if (mod == 0) {
      for (i64 i = div; i < B; i++) {
        bits[i - div] = bits[i];
      }      
    }
    else {
      for (i64 i = 0; i < B - (div + 1); i++) {
        bits[i] = bits[i + (div + 1)] << (64 - mod) | bits[i + div] >> mod;
      }
      if (div < B) {
        bits[B - div - 1] = bits[B - 1] >> mod;
      }        
    }
    for (i64 i = 0; i < div; i++) {
      bits[B - i - 1] = 0;
    }
    _clean();
    return *this;
  }

  // Simulates bs |= bs >> shift
  void or_shift_right(i64 shift) {
    i64 div = shift >> 6;
    i64 mod = shift & 63;
    if (mod == 0) {
      for (i64 i = div; i < B; i++) {
        bits[i - div] |= bits[i];
      }      
    } else {
      for (i64 i = 0; i < B - (div + 1); i++) {
        bits[i] |= bits[i + (div + 1)] << (64 - mod) | bits[i + div] >> mod;
      }
      if (div < B) {
        bits[B - div - 1] |= bits[B - 1] >> mod;
      }
    }
    _clean();
  }

  i64 find_lsb() const {
    for (i64 i = 0; i < B; i++) {
      if (bits[i]) {
        return i << 6 | __builtin_ctzll(bits[i]);
      }
    }
    return N;
  }

  i64 find_msb() const {
    for (i64 i = B - 1; i >= 0; i--) {
      if (bits[i]) {
        return i << 6 | (63 - __builtin_clzll(bits[i]));
      }
    }
    return -1;
  }
};

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);              

  return 0;
}
 