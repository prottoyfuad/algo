/*
@for reversed hash: calculate suffix 

suf.resize(n + 1);
for (int i = n - 1; i >= 0; i--) {
  suf[i] = mod_mul(suf[i + 1], base) + v[i];
  if (suf[i] >= mod) suf[i] -= mod;
}

T rev_hash(int l, int r) {
  assert(l <= r);
  T h = suf[l] - mod_mul(suf[r], power[r - l]);
  return h < T(0) ? h + mod : h;
}

*/

uint64_t random_address() {
  char* foo = new char;
  delete foo;
  return uint64_t(foo);
}
std::mt19937 rng((unsigned) std::chrono::system_clock::now().time_since_epoch().count() ^ random_address());

struct Polyhash {
  static const int L = 2;
  const int P[L] = {(int) 1e9 + 97, (int) 1e9 + 123}; 
  int n, cap, base;
  std::vector<int> power[L];
  std::vector<int> pre[L];

  Polyhash() = delete;
  explicit Polyhash(int S) : n(-1), cap(std::max(S, 3)) {
    init();
  }
  template <typename T_container> 
  explicit Polyhash(const T_container& a) : n(-1), cap(std::max((int) a.size(), 3)) {
    init();
    calc(a);
  }

  void init() {
    base = rng() % cap;
    if (base < 0) {
      base += cap;
    }
    base += cap;
    while (++base) {
      bool p = 1;
      for (int i = 2; i * i <= base; i++) {
        if (base % i == 0) {
          p = 0;
          break;
        }
      }
      if (p) {
        break;
      }
    }
    for (int j = 0; j < L; j++) {
      pre[j].resize(cap + 1);
      power[j].resize(cap + 1);
      power[j][0] = 1;
      for (int i = 0; i < cap; i++) {
        power[j][i + 1] = power[j][i] * 1ll * base % P[j];
      }
    }
  }
  
  template <typename T_container> 
  void calc(const T_container& a) {
    n = (int) a.size();
    assert(n <= cap);
    for (int j = 0; j < L; j++) {
      pre[j][0] = 0;
      for (int i = 0; i < n; i++) {
        pre[j][i + 1] = (pre[j][i] * 1ll * base % P[j]) + a[i];
        if (pre[j][i + 1] >= P[j]) {
          pre[j][i + 1] -= P[j];
        }
      }
    }
  }    

  inline long long get(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    long long h = 0;
    for (int j = 0; j < L; j++) {
      int x = pre[j][r] - (pre[j][l] * 1ll * power[j][r - l] % P[j]);
      if (x < 0) {
        x += P[j];
      }
      h = h << 32 | x;
    }
    return h;
  }
};

