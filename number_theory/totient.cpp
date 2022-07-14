
#include <bits/stdc++.h>

using namespace std;

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
  