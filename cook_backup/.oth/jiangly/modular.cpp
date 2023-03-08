#include <bits/stdc++.h>

constexpr int P = 998244353;
using i64 = long long;
// assume -P <= x < 2P
int norm(int x) {
  if (x < 0) x += P;
  if (x >= P) x -= P;
  return x;
}

template<class T> T power(T a, i64 b) {
  T res = 1;
  while (b) {
    if (b % 2) res *= a;
    a *= a; b /= 2;
  }
  return res;
}

struct Mint {
  int x;
  constexpr Mint() : x() {}
  template <typename T> 
  Mint(const T& x) : x(norm(x % P)) {}
  int val() const {
    return x;
  }
  Mint operator-() const {
    return Mint(norm(P - x));
  }
  Mint inv() const {
    assert(x != 0);
    return power(*this, P - 2);
  }
  Mint &operator*=(const Mint &rhs) {
    x = i64(x) * rhs.x % P;
    return *this;
  }
  Mint &operator+=(const Mint &rhs) {
    x = norm(x + rhs.x);
    return *this;
  }
  Mint &operator-=(const Mint &rhs) {
    x = norm(x - rhs.x);
    return *this;
  }
  Mint &operator/=(const Mint &rhs) {
    return *this *= rhs.inv();
  }
  friend Mint operator*(const Mint &lhs, const Mint &rhs) {
    Mint res = lhs;
    res *= rhs;
    return res;
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
  friend Mint operator/(const Mint &lhs, const Mint &rhs) {
    Mint res = lhs;
    res /= rhs;
    return res;
  }
  friend std::istream &operator>>(std::istream &is, Mint &a) {
    i64 v;
    is >> v;
    a = Mint(v);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const Mint &a) {
    return os << a.val();
  }
};
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  return 0;
}
  
