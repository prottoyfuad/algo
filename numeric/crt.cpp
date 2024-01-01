// copied and modified from atcoder library
#include <array>
#include <vector>
#include <cassert>
#include <iostream>

constexpr long long safe_mod(long long x, long long m) {
  x %= m;
  if (x < 0) x += m;
  return x;
}

// FROM ATCODER
constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
  a = safe_mod(a, b);
  if (a == 0) return {b, 0};
  
  long long s = b, t = a;
  long long m0 = 0, m1 = 1;

  while (t) {
    long long u = s / t;
    s -= t * u;
    m0 -= m1 * u;
                    
    std::swap(s, t);
    std::swap(m0, m1);
  }                       

  if (m0 < 0) m0 += b / s;
  return {s, m0};
}

// returns {remainder, moduli}, if not solvable returned modli = 0 
std::pair<long long, long long> CRT(const std::vector<long long>& r,
                                    const std::vector<long long>& m) {
  assert(r.size() == m.size());
  int n = int(r.size());    

  long long r0 = 0, m0 = 1;
  for (int i = 0; i < n; i++) {
    assert(1 <= m[i]);
    long long r1 = safe_mod(r[i], m[i]), m1 = m[i];
    if (m0 < m1) {
      std::swap(r0, r1);
      std::swap(m0, m1);
    }
    if (m0 % m1 == 0) {
      if (r0 % m1 != r1) return {0, 0};
      continue;
    }        
    auto [g, im] = inv_gcd(m0, m1);                   
    if ((r1 - r0) % g) return {0, 0};

    long long u1 = (m1 / g);
    long long x = (r1 - r0) / g % u1 * im % u1;
    r0 += x * m0;
    m0 *= u1;
    if (r0 < 0) r0 += m0;
  }
  return {r0, m0};
}
//! FROM ATCODER

template <typename T> std::array<T, 3> euclid(T a, T b) {
  if (b == 0) return {a, 1, 0};
  auto [d, x, y] = euclid(b, a % b);
  return {d, y, x - y * (a / b)};
}

std::pair<long long, long long> crt_single(long long a, long long m, 
                                           long long b, long long n) {
  if (n > m) {
    std::swap(a, b);
    std::swap(m, n);
  }
  auto [g, x, y] = euclid(m, n);
  if ((a - b) % g) {
    return {0, 0};
  }
  long long r = (b - a) % n * x % n / g * m + a;
  long long l = m * (n / g);
  return {r < 0 ? r + l : r, l};
}

std::pair<long long, long long> crt(const std::vector<long long>& r,
                                    const std::vector<long long>& m) {
  assert(r.size() == m.size());
  int n = int(r.size());    
  long long rem = 0, mod = 1;
  for (int i = 0; i < n; i++) {
    assert(m[i] > 0);
    auto [re, mo] = crt_single(rem, mod, safe_mod(r[i], m[i]), m[i]);
    if (mo == 0) return {0, 0};
    rem = re, mod = mo;
  }
  return {rem, mod};
}

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);  
  srand(time(0));
  vector<long long> P = {2, 3, 5, 7, 11, 13, 17, 19, 23};
  int K = P.size();
  vector<long long> C(K);
  for (int i = 0; i < K; i++) {
    C[i] = (P[i] + (rand() % P[i])) % P[i];
  }                           
  auto [rem1, mod1] = CRT(C, P);
  auto [rem2, mod2] = crt(C, P);      
  cout << rem1 << ' ' << mod1 << '\n';
  cout << rem2 << ' ' << mod2 << '\n'; 
  assert(rem1 == rem2);
  assert(mod1 == mod2);
  return 0;
}
  
