
// #pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math,inline")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,lzcnt,mmx,abm,avx,avx2")

#include <bits/stdc++.h>
/*  
// using nsmespace __gnu_cxx;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;

template <typename T>
using Ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
*/

#ifdef LOCAL
//#include "../algo/lib/debug.hpp"
#else
#define debug(...)
#endif

auto random_address = []() -> uint64_t {
  char* foo = new char;
  delete foo;
  return uint64_t(foo);
};
std::mt19937 rng((unsigned) std::chrono::system_clock::now().time_since_epoch().count() ^ random_address());

const int mod = 1e9 + 7;

int ext_euclid(int a, int b, int& x, int& y) {
  x = 1, y = 0;
  int u = 0, v = 1;
  while (b) {
    int q = a / b;
    x -= q * u; std::swap(x, u);
    y -= q * v; std::swap(y, v);
    a -= q * b; std::swap(a, b);
  }
  return a; // a is gcd(originalA, originalB);
}
// linear diophantile eqn's solution exist iff gcd(a, b) | c;
// one solution is {x_ans, y_ans} = {x * c / g, y * c / g} ^^[ext-euclid]
// and we can derive the func to find modular inverse from this-

int modinv(int a, int m) {
  int x, y;
  ext_euclid(a, m, x, y);
  if (x <= -m || x >= m) x %= m;
  if (x < 0) x += m;
  return x;
}
          
// a better way :
template <typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T q = m / a;
    m -= q * a; std::swap(a, m);
    u -= q * v; std::swap(u, v);
  }
  assert(m == 1);
  return u; // this needs normalization (using typename T = Modular is fine)
}

void prefix_2D() {
  using namespace std;
  int n, m;
  cin >> n >> m;
  vector a(n, vector<int> (m));
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < m; j++) {
      a[i][j] = s[j] - 48;
    }
  }
  vector pre(n + 1, vector<int> (m + 1));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      pre[i + 1][j + 1] = a[i][j];
      pre[i + 1][j + 1] += pre[i][j + 1] + pre[i + 1][j];
      pre[i + 1][j + 1] -= pre[i][j];
    }
  }
  auto get_ones = [&](int u, int v, int x, int y) {
    assert(x >= u && y >= v);
    return pre[x + 1][y + 1] - pre[u][y + 1] - pre[x + 1][v] + pre[u][v];
  };
  auto total_cells = [&](int u, int v, int x, int y) {
    assert(x >= u && y >= v);
    return (x - u + 1) * (y - v + 1);
  };
  auto get_zeroes = [&](int u, int v, int x, int y) {
    assert(x >= u && y >= v);
    return total_cells(u, v, x, y) - get_ones(u, v, x, y);
  };
  int q;
  cin >> q;
  while (q--) {
    // do something
    // like how many ones/zeroes in a rectangualar-submatrix
  }
}

int main() {
  std::cout << int('z');
  return 0;
}
