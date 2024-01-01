
const int N = 2e5 + 1;
const long long P = 1e9 + 7;

// precalculating inverses

int inv[N], fac[N], ifac[N];
void calc() {
  inv[1] = 1;
  for (int i = 2; i < N; i++){
    inv[i] = P - inv[P % i] * 1ll * (P / i) % P;
  }
  // or this
  for (int i = 2; i < N; i++) {
    inv[i] = inv[P % i] * 1ll * (P - P / i) % P;  
  }
  fac[0] = ifac[0] = 1;
  for (int i = 1; i < N; i++) {
    fac[i] = fac[i - 1] * 1ll * i % P;
    ifac[i] = ifac[i - 1] * 1ll * inv[i] % P;
  }
}

// SIMPLE, with long long

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

void init() {          
  fac[0] = 1;
  for (int i = 1; i < N; i++) {
    fac[i] = fac[i - 1] * i % P;
  }
  ifac[N - 1] = power(fac[N - 1], P - 2);
  for (int i = N - 1; i > 0; i--) {
    ifac[i - 1] = ifac[i] * i % P;
  }
}

long long C(int n, int k) {
  if (k < 0 || k > n) return 0;
  return (ifac[k] * ifac[n - k] % P) * fac[n] % P;
}

long long sumOverN(int n, int k) {
  return C(n + 1, k + 1);
}

long long sumOverNK(int n, int k) {
  return C(n + k + 1, k);
}

vector<vector<int>> dp(int nax = 2002) {
  vector<vector<int>> f(nax, vector<int> (nax));
  f[0][0] = 1; 
  for(int i = 1; i < nax; i++) {
    f[i][0] = 1;
    for(int j = 1; j <= i; j++) {
      f[i][j] = f[i - 1][j] + f[i - 1][j - 1];
      if(f[i][j] >= P) f[i][j] -= P;
    }
  }
  return f;
}
 
