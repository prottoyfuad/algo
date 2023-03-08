
#include <bits/stdc++.h>

using namespace std;

//https://github.com/yosupo06/library-checker-problems/blob/master/math/factorize/sol/correct.cpp
                                             
long long gcd(long long _a, long long _b) {
  unsigned long long a = abs(_a), b = abs(_b);
  if (a == 0) return b;
  if (b == 0) return a;
  int shift = __builtin_ctzll(a|b);
  a >>= __builtin_ctzll(a);
  do {
    b >>= __builtin_ctzll(b);
    if (a > b) swap(a, b);
    b -= a;
  } while (b);
  return (a << shift);
}

template <class T, class U> 
T power(T x, U n, T P) {
  T r = 1 % P;
  x %= P;
  while (n) {
    if (n & 1) r = (r * x) % P;
    x = (x * x) % P;
    n >>= 1;
  }
  return r;
}

bool is_prime(long long n) {
  if (n <= 1) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;
  long long d = n - 1;
  while (d % 2 == 0) d /= 2;
  for (long long a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (n <= a) break;
    long long t = d;
    long long y = power<__int128_t>(a, t, n);
    while (t != n - 1 && y != 1 && y != n - 1) {
      y = __int128_t(y) * y % n;
      t <<= 1;
    }
    if (y != n - 1 && t % 2 == 0) {
      return false;
    }
  }
  return true;
}

long long pollard_single(long long n) {
  auto f = [&](long long x) { return (__int128_t(x) * x + 1) % n; };
  if (is_prime(n)) return n;
  if (n % 2 == 0) return 2;
  long long st = 0;
  while (true) {
    st++;
    long long x = st, y = f(x);
    while (true) {
      long long p = gcd((y - x + n), n);
      if (p == 0 || p == n) break;
      if (p != 1) return p;
      x = f(x);
      y = f(f(y));
    }
  }
}

vector<long long> pollard(long long n) {
  if (n == 1) return {};
  long long x = pollard_single(n);
  if (x == n) return {x};
  vector<long long> lhs = pollard(x);
  vector<long long> rhs = pollard(n / x);
  lhs.insert(lhs.end(), rhs.begin(), rhs.end());
  return lhs;
}
         
int main() {
  int tt;
  cin >> tt;
  for (int tc = 0; tc < tt; tc++) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int j = 0; j < n; j++) {
      cin >> a[j];
    }
    vector<int> f;
    for (int j = 0; j < n; j++) {
      vector<long long> T = pollard(a[j]);
      sort(T.begin(), T.end());
      T.erase(unique(T.begin(), T.end()), T.end());
      for (int k : T){
        f.push_back(k);
      }
    }
    sort(f.begin(), f.end());
    int cnt = f.size();
    bool ok = false;
    for (int j = 0; j < cnt - 1; j++){
      if (f[j] == f[j + 1]){
        ok = true;
      }
    }
    if (ok){
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
  return 0;
}
