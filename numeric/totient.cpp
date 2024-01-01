
#include <bits/stdc++.h>

using namespace std;

/*           
phi(n) = MULT of all [(p-1) * {p ^ (k-1)}] // prime(p) k times in factorization(n)
implementing directly this way division occurs less (probably, seems like it :3)
but the below implementation is better for extending the idea to generate totient as well
*/

// From SSRS
long long totient(long long x) {
  long long ans = x;
  for (long long i = 2; i * i <= x; i++) {
    if (x % i == 0) {
      ans /= i;
      ans *= i - 1;
      while (x % i == 0) {
        x /= i;
      }
    }
  }
  if (x > 1) {
    ans /= x;
    ans *= x - 1;
  }
  return ans;
}

vector<int> gen_totient(int n) {
  vector<int> phi(n + 1);
  iota(phi.begin(), phi.end(), 0);
  for (int i = 2; i <= n; i++) {
    if (phi[i] == i) {
      for (int j = i; j <= n; j += i) {
        phi[j] /= i;
        phi[j] *= i - 1;
      }
    }
  }
  return phi;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  return 0;
}
  
