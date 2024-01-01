
#include <vector>
#include <iostream>

struct Bitset2d {
  using i64 = long long;
  using u64 = unsigned long long;
  i64 N, B;
  std::vector<std::vector<u64>> bits;    

  void init(i64 n) {
    N = n;
    B = (N + 7) / 8;
    bits.assign(B, std::vector<u64> (B, u64(0)));
  }

  Bitset2d(i64 n) {
    init(n);
  }

  bool get(i64 i, i64 j) const {                                                                                                       
    i64 xx = i / 8, xy = j / 8;
    i64 yx = i & 7, yy = j & 7;
    return bits[xx][xy] >> (8 * yx + yy) & 1;
  }

  void set(i64 i, i64 j) {                                                                                                       
    i64 xx = i / 8, xy = j / 8;
    i64 yx = i & 7, yy = j & 7;
    bits[xx][xy] = bits[xx][xy] | u64(1) << (8 * yx + yy);
  }

  void or_equal(const Bitset2d& a) {
    for (i64 i = 0; i < B; i++) {
      for (i64 j = 0; j < B; j++) {
        bits[i][j] |= a.bits[i][j];
      }
    }            
  }

  void shift_left(const Bitset2d& a, const i64 shift) {
    for (i64 i = 0; i < B; i++) {
      for (i64 j = 0; j < B; j++) {
        bits[i][j] = 0;
      }
    }
    i64 div = shift / 8;
    i64 mod = shift & 7;
    if (mod == 0) {
      for (i64 i = B - 1; i >= 0; i--) {
        for (i64 j = B - 1; j >= div; j--) {
          bits[i][j] |= a.bits[i][j - div];
        }
      }      
    } 
    else {
      u64 right = 0;
      for (int i = 0; i < 8; i++) {
        right = right << 8 | ((u64(1) << (8 - mod)) - 1);            
      }
      for (i64 i = B - 1; i >= 0; i--) {
        for (i64 j = B - 1; j >= div + 1; j--) {
          u64 lval = ~right & a.bits[i][j - (div + 1)];
          u64 rval = right & a.bits[i][j - div];
          bits[i][j] |= lval >> (8 - mod);
          bits[i][j] |= rval << mod;                                             
        }
      }
      if (div < B) {
        for (i64 i = B - 1; i >= 0; i--) {
          u64 rval = right & a.bits[i][0];                                         
          bits[i][div] |= rval << mod;
        }                              
      }
    }         
  }
  
  void shift_up(const Bitset2d& a, const i64 shift) {    
    for (i64 i = 0; i < B; i++) {
      for (i64 j = 0; j < B; j++) {
        bits[i][j] = 0;
      }
    }
    i64 div = shift / 8;
    i64 mod = shift & 7;
    if (mod == 0) {
      for (i64 j = B - 1; j >= 0; j--) {
        for (i64 i = B - 1; i >= div; i--) {
          bits[i][j] |= a.bits[i - div][j];
        }
      }      
    } 
    else {
      u64 left = (u64(1) << ((8 - mod) * 8)) - 1;
      for (i64 j = B - 1; j >= 0; j--) {
        for (i64 i = B - 1; i >= div + 1; i--) {
          u64 lval = ~left & a.bits[i - (div + 1)][j];
          u64 rval = left & a.bits[i - div][j];
          bits[i][j] |= lval >> (8 * (8 - mod));
          bits[i][j] |= rval << (8 * mod);                                       
        }
      }
      if (div < B) {
        for (i64 j = B - 1; j >= 0; j--) {
          u64 rval = left & a.bits[0][j];
          bits[div][j] |= rval << (8 * mod);
        }                              
      }
    }         
  }
  // similarly implement shift right and down
  // look up 1D Bitset2d if necessary
};

/*
 * A problem using this Bitset2d : given an array 
 * for all the prefix of the array tell if,
 * that prefix can be 3 partitioned into mutisets with equal sum.
 * partitions does not need to be contiguous.
 * all the elements in a prefix must be included exactly once in exactly one multiset
*/

using namespace std;
                    
constexpr int N = 5008;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  Bitset2d f(N), x(N), y(N);     
  f.set(0, 0);
  int sum = 0;
  for (int i = 0; i < n; i++) { 
    sum += a[i];      
    int ans = 0;
    if (sum % 3 == 0 && f.get(sum / 3, sum / 3)) {
      ans = 1;
    } 
    cout << ans << '\n'; // answer for prefix [0, i]
    x.shift_left(f, a[i]);
    y.shift_up(f, a[i]);
    f.or_equal(x);
    f.or_equal(y);
  }     
  return 0;
}
  
