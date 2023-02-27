
#include <bits/stdc++.h>

constexpr int P = 1e9 + 7;
                      
template <typename T> T power(T a, long long b) {
  T res = 1;
  while (b) {
    if (b & 1) res *= a;
    a *= a;
    b /= 2;
  }
  return res;
}

struct Mint {
  int x;
  constexpr Mint() : x() {}
  template <typename T> Mint(const T& v) {
    x = static_cast<int>(abs(v) >= P ? v % P : v);
    if (x < 0) x += P;
  }                                                
  int val() const { 
    return x;
  }           
  Mint operator-() const {
    Mint res;
    res.x = P - x;
    return res;
  }
  Mint inv() const {
    return power(*this, P - 2);
  }
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
    x = x * 1ll * rhs.x % P;
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

std::vector<Mint> fac(1, 1);
std::vector<Mint> ifac(1, 1);

void ensure_fac(int N) {                  
  int w = fac.size();
  if (w > N) return;   
  for (int i = w; i <= N; i++) {
    fac.push_back(fac[i - 1] * i);
    ifac.push_back(0);
  }
  ifac[N] = fac[N].inv();
  for (int i = N; i > w; i--) {
    ifac[i - 1] = ifac[i] * i;
  }
}

Mint C(int n, int k) {
  if (k < 0 || k > n) return 0;
  ensure_fac(n);
  return fac[n] * ifac[k] * ifac[n - k];
}

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
         
  return 0;
}
 