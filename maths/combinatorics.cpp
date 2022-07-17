
#include <bits/stdc++.h>

using namespace std;

const int P = 1e9 + 7;
int power(int a, int p) {
  int ans = 1;
  while (p) {
    if (p & 1) ans = ans * 1ll * a % P;
    a = a * 1ll * a % P;
    p /= 2;
  }
  return ans;
}
std::vector<int> fac(1, 1), ifac(1, 1);
void init(int n) {
  if ((int) fac.size() > n) return;
  int was = fac.size();
  fac.resize(n + 1);
  ifac.resize(n + 1);
  for (int i = was; i <= n; i++) {
    fac[i] = fac[i - 1] * 1ll * i % P;
  }
  ifac[n] = power(fac[n], P - 2);
  for (int i = n; i > was; i--) {
    ifac[i - 1] = ifac[i] * 1ll * i % P;
  }
}
int choose(int n, int k) {
  if (k < 0 || k > n) return 0;
  init(n);
  return (ifac[k] * 1ll * ifac[n - k] % P) * fac[n] % P;
}
int sumOverN(int n, int k) {
  return choose(n + 1, k + 1);
}
int sumOverNK(int n, int k) {
  return choose(n + k + 1, k);
}

// with each inv precalc
int inv[N], fact[N], ifact[N];
void init() {
  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i < N; i++) inv[i] = (ll)inv[P % i] * (P - P / i) % P;
  for (int i = 1; i < N; i++) fact[i] = (ll)fact[i - 1] * i % P;
  for (int i = 1; i < N; i++) ifact[i] = (ll)ifact[i - 1] * inv[i] % P;
}

// With long long
long long mod = 1e9 + 7;
long long modpow(long long a, long long b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = (ans * a) % mod;
    a = (a * a) % mod;
    b /= 2;
  }
  return ans;
}
long long modinv(long long a) {
  return modpow(a, mod - 2);
}
std::vector<long long> fac(1, 1), ifac(1, 1);
void init(int n) {
  if ((int) fac.size() > n) return;
  int was = fac.size();
  for (int i = was; i <= n; i++) {
    fac.push_back((fac[i - 1] * i) % mod);
    ifac.push_back(0);
  }
  ifac[n] = modinv(fac[n]);
  for (int i = n; i > was; i--) {
    ifac[i - 1] = (ifac[i] * i) % mod;
  }
}
long long get_fac(int n) {
  init(n);
  return fac[n];
}
long long get_ifac(int n) {
  init(n);
  return ifac[n];
}
long long choose(int n, int k) {
  if (k < 0 || k > n) return 0;
  init(n);
  long long d = (ifac[k] * ifac[n - k]) % mod;
  return (d * fac[n]) % mod;
}

vector<vector<int>> dp(int nax = 2002, int mod = 1e9 + 7) {
  vector<vector<int>> choose(nax, vector<int> (nax));
  choose[0][0] = 1; 
  for(int i = 1; i < nax; i++) {
    choose[i][0] = 1;
    for(int j = 1; j <= i; j++) {
      choose[i][j] = choose[i - 1][j] + choose[i - 1][j - 1];
      if(choose[i][j] >= mod) choose[i][j] -= mod;
    }
  }
  return choose;
}
 
int main() {

  return 0;
}
 