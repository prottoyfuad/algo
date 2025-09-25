
// #pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math,inline")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,lzcnt,mmx,abm,avx,avx2")

#include <bits/stdc++.h>
 
// using nsmespace __gnu_cxx;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;

template <typename T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

#ifdef LOCAL
#include "../algo/debug.h"
#else
#define debug(...) 0
#endif

uint64_t random_address() {
  char* foo = new char;
  delete foo;
  return uint64_t(foo);
}

// RNG engine - declare globally or static inside function
std::mt19937 rng((unsigned)std::chrono::system_clock::now().time_since_epoch().count() ^ random_address());

// [l, r] inclusive
int getRand(int l, int r) {
  std::uniform_int_distribution<int> dist(l, r);
  return dist(rng);
}

long long floor_div(long long x, long long y) {
  assert(y != 0);
  if (y < 0) {
    y = -y;
    x = -x;
  }
  if (x >= 0) return x / y;
  return (x + 1) / y - 1;
}

long long ceil_div(long long x, long long y) {
  assert(y != 0);
  if (y < 0) {
    y = -y;
    x = -x;
  }
  if (x <= 0) return x / y;
  return (x - 1) / y + 1;
}

// from jiangly - not tested
constexpr uint64_t mulMod(uint64_t a, uint64_t b, uint64_t P) {
  uint64_t res = a * b - uint64_t(1.L * a * b / P - 0.5L) * P;
  res %= P;
  return res;
}

// from jiangly - not tested
constexpr int64_t mulMod(int64_t a, int64_t b, int64_t P) {
  int64_t res = a * b - int64_t(1.L * a * b / P) * P;
  res %= P;
  if (res < 0) {
    res += P;
  }
  return res;
}

// returned `a` is the gcd of param `a, b`
// linear diophantile eqn's solution exist iff `gcd(a, b) | c`;
// one solution is {x_ans, y_ans} = {x * c / g, y * c / g}
int ext_euclid(int a, int b, int& x, int& y) {
  x = 1, y = 0;
  int u = 0, v = 1;
  while (b) {
    int q = a / b;
    x -= q * u; std::swap(x, u);
    y -= q * v; std::swap(y, v);
    a -= q * b; std::swap(a, b);
  }
  return a;
}

// to find modular inverse from this-
int modinv(int a, int m) {
  int x, y;
  ext_euclid(a, m, x, y);
  if (x <= -m || x >= m) x %= m;
  if (x < 0) x += m;
  return x;
}
          
// from tourist's Mod template
template <typename T> T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T q = m / a;
    m -= q * a; std::swap(a, m);
    u -= q * v; std::swap(u, v);
  }
  assert(m == 1);
  return u; 
}

using namespace std;

void prefix_2D() {    
  int n, m;
  cin >> n >> m;
  vector a(n, vector<int> (m));
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < m; j++) {
      a[i][j] = s[j] - '0';
    }
  }
  vector pre(n + 1, vector<int> (m + 1));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      pre[i + 1][j + 1] = a[i][j];
                        + pre[i][j + 1] + pre[i + 1][j];
                        - pre[i][j];
    }
  }
  auto cnt_cells = [&](int u, int v, int x, int y) {
    assert(x >= u && y >= v);
    return (x - u + 1) * (y - v + 1);
  };
  auto cnt_ones = [&](int u, int v, int x, int y) {
    assert(x >= u && y >= v);
    return pre[x + 1][y + 1] - pre[u][y + 1] - pre[x + 1][v] + pre[u][v];
  };
  auto cnt_zeroes = [&](int u, int v, int x, int y) {
    assert(x >= u && y >= v);
    return cnt_cells(u, v, x, y) - cnt_ones(u, v, x, y);
  };
  int q;
  cin >> q;
  while (q--) {
    // do smth
  }
}

int main() {                      
  ios::sync_with_stdio(false);
  cin.tie(0);

  return 0;
}
