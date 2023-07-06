
#include <bits/stdc++.h>

long long P = 1e9 + 7;
                      
template <typename T, typename U> T power(T a, U b) {
  T res = 1;
  while (b) {
    if (b & 1) res *= a;
    a *= a;
    b /= 2;
  }
  return res;
}

template <typename T> std::array<T, 3> euclid(T a, T b) {
  if (b == 0) return {a, 1, 0};
  auto [d, x, y] = euclid(b, a % b);
  return {d, y, x - y * (a / b)};
}

struct Mint {
private:
  long long x;
public:
  constexpr Mint() : x() {}
  Mint(const long long& v) : x(v) {
    if (abs(x) >= P) x %= P;
    if (x < 0) x += P;
  }                                                
  const long long operator()() const { 
    return x;
  }           
  Mint operator-() const {
    return Mint(-x);
  }
  Mint inv() const {
    // if (primeP) return power(*this, P - 2);
    auto [g, a, b] = euclid(x, P);
    assert(g == 1); 
    return Mint(a);
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
    return os << a.x;
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
 