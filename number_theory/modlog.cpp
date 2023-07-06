              
#include <cmath>
#include <numeric>
#include <iostream>
#include <unordered_map>

// Discrete Logarithm from CP Algo
// Returns minimum x for which, k * (a ^ x) % m = b % m 
// Solution does not always exists (-1)
int ModLog2(int a, int b, int m) {
  a %= m;
  b %= m;
  int k = 1, add = 0;
  while (true) {
    int g = std::gcd(a, m);
    if (g == 1) {
      break;
    }
    if (b == k) {
      return add;
    }
    if (b % g) {
      return -1;
    }
    b /= g;
    m /= g;
    add += 1;
    k = (k * 1ll * a / g) % m;
  }
  int n = sqrt(m) + 1;
  std::unordered_map<int, int> vals;
  for (int q = 0, cur = b; q <= n; q++) {
    vals[cur] = q;
    cur = (cur * 1ll * a) % m;
  }
  int an = 1;
  for (int i = 0; i < n; i++) {
    an = (an * 1ll * a) % m;
  }
  for (int p = 1, cur = k; p <= n; ++p) {
    cur = (cur * 1ll * an) % m;
    if (vals.count(cur)) {
      int ans = n * p - vals[cur] + add;
      return ans;
    }
  }
  return -1;
}

// Simple implementation when, a and m are coprime.
int ModLog(int a, int b, int m) {
  a %= m;
  b %= m;
  int n = sqrt(m) + 1;
  std::unordered_map<int, int> vals;
  for (int q = 0, cur = b; q <= n; ++q) {
    vals[cur] = q;
    cur = (cur * 1ll * a) % m;
  }
  int an = 1;
  for (int i = 0; i < n; ++i) {
    an = (an * 1ll * a) % m;
  }
  for (int p = 1, cur = 1; p <= n; ++p) {
    cur = (cur * 1ll * an) % m;
    if (vals.count(cur)) {
      int ans = n * p - vals[cur];
      return ans;
    }
  }
  return -1;
}

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while
  return 0;
}
  
