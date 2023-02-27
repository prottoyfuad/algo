
#include <bits/stdc++.h>

using namespace std;

// with each inv precalc
int inv[N], fact[N], ifact[N];
void init() {
  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i < N; i++) {
    inv[i] = inv[P % i] * 1ll * (P - P / i) % P;  
  }
  for (int i = 1; i < N; i++) {
    fact[i] = fact[i - 1] * 1ll * i % P;
  }
  for (int i = 1; i < N; i++) {
    ifact[i] = ifact[i - 1] * 1ll * inv[i] % P;
  }
}

// SIMPLE, with LL

const int N = 2e5 + 1;
const long long P = 1e9 + 7;

long long power(long long a, long long p) {
  long long ans = 1;
  while (p) {
    if (p & 1) {
      ans *= a;
      ans %= P;
    }                     
    a *= a;
    a %= P;       
    p /= 2;
  }
  return ans;
}

std::vector<long long> fac;
std::vector<long long> ifac;

void init() {          
  fac.resize(N + 1);
  ifac.resize(N + 1);
  fac[0] = 1;
  for (int i = 1; i <= N; i++) {
    fac[i] = fac[i - 1] * i % P;
  }
  ifac[N] = power(fac[N], P - 2);
  for (int i = N; i > 0; i--) {
    ifac[i - 1] = ifac[i] * i % P;
  }
}

long long choose(int n, int k) {
  if (k < 0 || k > n) return 0;
  return (ifac[k] * ifac[n - k] % P) * fac[n] % P;
}

long long sumOverN(int n, int k) {
  return choose(n + 1, k + 1);
}

long long sumOverNK(int n, int k) {
  return choose(n + k + 1, k);
}

//~ with LL

// with INT
const int N = 1e5 + 1;
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

std::vector<int> fac;
std::vector<int> ifac;

void init() {          
  fac.resize(N + 1);
  ifac.resize(N + 1);
  fac[0] = 1;
  for (int i = 1; i <= N; i++) {
    fac[i] = fac[i - 1] * 1ll * i % P;
  }
  ifac[N] = power(fac[N], P - 2);
  for (int i = N; i > 0; i--) {
    ifac[i - 1] = ifac[i] * 1ll * i % P;
  }
}

int choose(int n, int k) {
  if (k < 0 || k > n) return 0;
  return (ifac[k] * 1ll * ifac[n - k] % P) * fac[n] % P;
}

int sumOverN(int n, int k) {
  return choose(n + 1, k + 1);
}

int sumOverNK(int n, int k) {
  return choose(n + k + 1, k);
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
 