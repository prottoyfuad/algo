
/*
    forward_hash(prefix) was tested;
    reversed_hash(suffix) not yet
    should be fine
*/

#include <vector>
#include <chrono>
#include <cassert>
#include <iostream>

struct custom_hash {
  // http://xorshift.di.unimi.it/splitmix64.c
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  
  size_t operator() (uint64_t x) const {
    static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

template <const auto base, const auto mod> struct PolyHash {
  int n;
  using T = decltype(mod);  
  std::vector<T> power, pre, suf;
  
  template <typename A, typename B> static T mod_mul(A x, B y) {
    return static_cast<T>(1ll * x * y % mod);
  }  
  T get_mod() {
    return mod;
  }
  
  // initially elements of the container should be normalized;
  PolyHash() {} 
  template <typename T_container>
  PolyHash(const T_container& v, bool initForward = 1, bool initReverse = 1) {
    n = v.size();
    power.resize(n + 1);
    power[0] = 1;
    for (int i = 0; i < n; i++) {
      power[i + 1] = mod_mul(power[i], base);
    }
    if (initForward) {
      pre.resize(n + 1);
      for (int i = 0; i < n; i++) {
        pre[i + 1] = mod_mul(pre[i], base) + v[i];
        if (pre[i + 1] >= mod) pre[i + 1] -= mod;
      }
    }
    if (initReverse) {
      suf.resize(n + 1);
      for (int i = n - 1; i >= 0; i--) {
        suf[i] = mod_mul(suf[i + 1], base) + v[i];
        if (suf[i] >= mod) suf[i] -= mod;
      }
    }
  }
  
  T get_hash(int l, int r) {
    assert(l <= r);
    T h = pre[r] - mod_mul(pre[l], power[r - l]);
    return h < T(0) ? h + mod : h;
  }
  
  T rev_hash(int l, int r) {
    assert(l <= r);
    T h = suf[l] - mod_mul(suf[r], power[r - l]);
    return h < T(0) ? h + mod : h;
  }
  
  template <typename T_container> static T get_hash(const T_container& v) {
    int n_ = v.size();
    T t {};
    for (int i = 0; i < n_; i++) {
      t = mod_mul(t, base) + v[i];
      if (t >= mod) t -= mod;
    }
    return t;
  }
  
  template <typename T_container> static T rev_hash(const T_container& v) {
    int n_ = v.size();
    T t {};
    for (int i = n_ - 1; i >= 0; i--) {
      t = mod_mul(t, base) + v[i];
      if (t >= mod) t -= mod;
    }
    return t;
  }
};

int main() {

  return 0;
}
 