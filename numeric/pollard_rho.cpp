
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

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
T power(T x, U n, T md) {
  T r = 1 % md;
  x %= md;
  while (n) {
    if (n & 1) r = (r * x) % md;
    x = (x * x) % md;
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
  long long n;
  cin >> n;
  vector<long long> facs = pollard(n);
  sort(facs.begin(), facs.end());

  return 0;
}

