
#include<bits/stdc++.h>

namespace CRT {

inline long long normalize(long long a, long long P) { 
  a %= P; 
  if (a < 0) a += P; 
  return a;
}

// array :: {coef_x, coef_y, gcd}
std::array<long long, 3> euclid(long long a, long long b) {
  if (b == 0) {
    return {1, 0, a};
  }  
  auto [x, y, d] = euclid(b, a % b);
  return {y, x - a / b * y, d};
}

std::pair<long long, long long> solve(const std::vector<long long>& a,
                                      const std::vector<long long>& p) {
  int n = (int) a.size();
  assert(n > 0 && (int) p.size() == n);
  for (int i = 0; i < n; i++) {
    normalize(a[i], p[i]);
  }
  long long ans = a[0], lcm = p[0];
  for (int i = 1; i < n; i++) {
    auto [x, y, d] = euclid(lcm, p[i]);
    if ((a[i] - ans) % d != 0) {
      return {-1, -1};
    }
    ans = normalize(ans + x * (a[i] - ans) / d % (p[i] / d) * lcm, lcm * p[i] / d);
    lcm = std::lcm(lcm, p[i]); 
    // you can save time by replacing above lcm * p[i] / d by lcm = lcm * p[i] / d
  }
  return {ans, lcm};
}

} // namespace CRT

using namespace std;

/// solution of :: https://open.kattis.com/problems/generalchineseremainder

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tt;
  cin >> tt;
  vector<long long> a(2), p(2);
  
  while (tt--) {
    cin >> a[0] >> p[0] >> a[1] >> p[1];
    auto [ans, lcm] = CRT::solve(a, p);

    if (ans == -1) cout << "no solution\n";
    else cout << ans << ' ' << lcm << '\n';
  }

  return 0;
}
 