
#include <array>
#include <vector>
#include <iostream>

using namespace std;
  
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

vector<int> sieve_linear(int nax) {
  vector<int> d(nax), primes; // for nax::1e6 -> primes.reserve(8e4);
  for (int i = 2; i < nax; i++) {
    if (!d[i]) {
      d[i] = i;
      primes.push_back(i);
    }
    for (int p : primes) {
      int j = i * p;
      if (p > d[i] || j >= nax) break;
      d[j] = p;
    }
  }
  return primes;
}
/** Another way of linear sieve

std::vector <int> prime;
bool is_composite[MAXN];
void sieve (int n) {
  std::fill (is_composite, is_composite + n, false);
  for (int i = 2; i < n; ++i) {
    if (!is_composite[i]) prime.push_back (i);
    for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
      is_composite[i * prime[j]] = true;
      if (i % prime[j] == 0) break;
    }
  }
}
*/

u64 multiply(u64 a, u64 b, u64 mod) {
  if (a >= mod) a %= mod;
  if (b >= mod) b %= mod;
  if (a > b) swap(a, b);
  u64 r = 0;
  while (b) {
    if (b & 1) {
      r += a;
      if (r >= mod) r -= mod;
    }
    a += a;
    if (a >= mod) a -= mod;
    b >>= 1;
  }
  return r;
}

u64 power(u64 a, u64 p, u64 mod) {
  u64 r = 1;
  while (p) {
    if (p & 1) r = multiply(r, a, mod);
    a = multiply(a, a, mod);
    p >>= 1;
  }
  return r;
}

/// https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test#Testing_against_small_sets_of_bases
/// 1e6 -> p = {2, 3};
/// u32 -> p = {2, 7, 61};
/// u64 -> p = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

bool miller_rabin(u64 n) {
  if (n < 2) return false;
  
  array<u64, 12> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  for (u64 a : primes) if (n % a == 0) return n == a;
  
  int r = __builtin_ctzll(n - 1);
  u64 d = (n - 1) >> r;
  
  for (u64 a : primes) {    
    u64 x = power(a % n, d, n);
    if (x == 1 || x == n - 1) continue;
    
    for (int i = 1; i < r; i++) {
      x = multiply(x, x, n);
      if (x == n - 1) break;
    }
    if (x != n - 1) return false;
  }
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  return 0;
}

