
#include <bits/stdc++.h>

using i28 = __int128;
using mod_t = long long;
using mul_t = i28;

#define PRIME_MODULI 0
mod_t P = 1e9 + 7;
                      
template <typename T> T power(T a, long long b) {
  T res = 1;
  while (b) {
    if (b & 1) res *= a;
    a *= a; b /= 2;
  }
  return res;
}

template <typename T> T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T q = m / a;
    m -= q * a; std::swap(a, m);
    u -= q * v; std::swap(u, v);
  }
  assert(m == 1);
  return u;
}

struct Mint {
  mod_t x;
  constexpr Mint() : x() {}
  template <typename T> Mint(const T& v) {
    x = static_cast<mod_t>(v % P);
    if (x < 0) x += P;
  }                                                
  mod_t val() const { 
    return x;
  }           
  Mint operator-() const {
    Mint res;
    res.x = P - x;
    return res;
  }
#if PRIME_MODULI == 1
  Mint inv() const {
    assert(x);
    return power(*this, P - 2);
  }
#else
  Mint inv() const {
    assert(x && std::gcd(x, P) == 1); // or, return Mint(0) to check
    return Mint(inverse(x, P));
  }
#endif
  Mint& operator+=(const Mint &rhs) {
    x += rhs.x;
    if (x >= P) x -= P;
    return *this;
  }
  Mint& operator-=(const Mint &rhs) {
    x += P - rhs.x;
    if (x >= P) x -= P;
    return *this;
  }
  Mint& operator*=(const Mint &rhs) {
    x = x * mul_t(1) * rhs.x % P;
    return *this;
  }
  Mint& operator/=(const Mint &rhs) {
    return *this *= rhs.inv();
  }
   
  friend Mint operator+(const Mint &lhs, const Mint &rhs) {
    Mint res = lhs;
    res += rhs;
    return res;
  }
  friend Mint operator-(const Mint &lhs, const Mint &rhs) {
    Mint res = lhs;
    res -= rhs;
    return res;
  }
  friend Mint operator*(const Mint &lhs, const Mint &rhs) {
    Mint res = lhs;
    res *= rhs;
    return res;
  }
  friend Mint operator/(const Mint &lhs, const Mint &rhs) {
    Mint res = lhs;
    res /= rhs;
    return res;
  }
  friend std::istream& operator>>(std::istream &is, Mint &a) {
    long long v;
    is >> v;
    a = Mint(v);
    return is;
  }
  friend std::ostream& operator<<(std::ostream &os, const Mint &a) {
    return os << a.val();
  }
};

std::vector<Mint> fac(1, 1), invfac(1, 1);
void gen_fac(int N) {
  if ((int) fac.size() > N) return;
  int w = fac.size();
  fac.resize(N + 1);
  invfac.resize(N + 1);
  for (int i = w; i <= N; i++) {
    fac[i] = fac[i - 1] * i;
  }
  invfac[N] = fac[N].inv();
  for (int i = N; i > w; i--) {
    invfac[i - 1] = invfac[i] * i;
  }
}
Mint choose(int n, int k) {
  if (k < 0 || k > n) return 0;
  gen_fac(n);
  return fac[n] * invfac[k] * invfac[n - k];
}

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
         
  return 0;
}
 