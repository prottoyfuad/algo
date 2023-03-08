/**
 *		Given a tree, for each vertex,
 *    Find the number of non-isomorphic subtree considering that vertex as root
 *    https://codeforces.com/contest/763/problem/D
**/

// With bracket sequence polynomial hashing
void DFS(int s, int p) {
    sz[s] = 1;
    for(int x : e[s]) {
        if(x == p) continue;
        DFS(x, s);
        sz[s] += sz[x];
    }
    sort(e[s].begin(), e[s].end(), [](int a, int b) { return h[a] < h[b]; });
    h[s] = {1, 1};
    for(int x : e[s]) {
        if(x == p) continue;
        h[s] = mul(h[s], pw[sz[x] * 2]);
        h[s] = add(h[s], h[x]);
    }
    h[s] = mul(h[s], base);
    h[s] = add(h[s], make_pair(2, 2));
}
// END
 
#include <map>
#include <vector> 
#include <chrono>
#include <random>
#include <cassert>
#include <iostream>
#include <functional>

using namespace std;

constexpr int N = 1e5 + 3;                             

int power(int a, int b, int M) {
  a %= M;
  int res = 1;       
  while (b) {
    if (b & 1) res = res * 1ll * a % M;
    a = a * 1ll * a % M;
    b /= 2;
  }
  return res;
}

constexpr int P[] = {(int) 1e9 + 11, (int) 1e9 + 123, (int) 1e9 + 321};

struct H {
  static const int L = 3;
  array<int, L> h;
  H() {
    for (int j = 0; j < L; j++) {
      h[j] = 1;
    }
  }
  int& operator[](int x) {
    return h[x];
  }
  H inv() {
    H res;
    for (int j = 0; j < L; j++) {
      res[j] = power(h[j], P[j] - 2, P[j]);
    }
    return res;
  }
  void operator += (const H& o) {
    for (int j = 0; j < L; j++) {
      h[j] += o.h[j];
      h[j] %= P[j];
    }
  }
  H operator+ (int x) {
    H res;            
    for (int j = 0; j < L; j++) {
      res[j] = x % P[j];
    }                   
    res += *this;
    return res;
  }
  void operator *= (const H& o) {
    for (int j = 0; j < L; j++) {
      h[j] = h[j] * 1ll * o.h[j] % P[j];
    }
  }
  bool operator < (const H& o) const {
    for (int j = 0; j < L; j++) {
      if (h[j] ^ o.h[j]) {
        return h[j] < o.h[j];
      }
    }
    return 0;
  }
  bool operator == (const H& o) const {
    return h == o.h;
  }
  bool operator != (const H& o) const {
    return h != o.h;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  mt19937 gen((unsigned) chrono::steady_clock().now().time_since_epoch().count());
  vector<int> R(N);
  for (int i = 0; i < N; i++) {
    R[i] = ((gen() % P[0]) + P[0]) % P[0];
  }                 
  int n;
  cin >> n;
  vector<vector<int>> e(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  map<H, int> F;
  auto Add = [&](const H& h) {             
    ++F[h];
  };
  auto Del = [&](const H& h) {
    assert(F.find(h) != F.end());
    if (--F[h] == 0) {
      F.erase(h);
    }
  };                 
  vector<H> hsub(n);
  vector<int> height(n);
  function<void(int, int)> calc = [&](int v, int p) {
    for (int u : e[v]) {
      if (u != p) {
        calc(u, v);
        height[v] = max(height[v], height[u] + 1);
      }
    }
    for (int u : e[v]) {
      if (u != p) {
        hsub[v] *= hsub[u] + R[height[v]];
      }
    }
    Add(hsub[v]);
  };
  calc(0, -1);
  vector<H> hp(n);
  vector<int> height_up(n);
  int ans = 0;
  int best = (int) F.size();
  function<void(int, int)> dfs = [&](int v, int p) {
    Del(hsub[v]);             
    int high = max(height[v], height_up[v]);
    int mxh = -1;
    if (high == height_up[v]) {
      mxh = p;
    }
    for (int u : e[v]) {
      if (u != p && height[u] + 1 == high) {
        if (mxh == -1) {
          mxh = u;
        } else {
          mxh = -1;
          break;
        }
      }
    }           
    H hsh;  
    for (int u : e[v]) {
      if (u == p) {
        hsh *= hp[v] + R[high];
      } else {
        hsh *= hsub[u] + R[high];
      }
    }
    Add(hsh);          
    if ((int) F.size() > best) {
      best = (int) F.size();
      ans = v;
    }
    Del(hsh);
    int K = (int) e[v].size();
    vector<int> preh(K + 1, -1);
    for (int j = 0; j < K; j++) {
      int u = e[v][j];
      if (u == p) {
        preh[j + 1] = preh[j];
      } else {
        preh[j + 1] = max(preh[j], height[u]);
      }
    }
    vector<int> sufh(K + 1, -1);
    for (int j = K - 1; j >= 0; j--) {
      int u = e[v][j];
      if (u == p) {
        sufh[j] = sufh[j + 1];
      } else {
        sufh[j] = max(sufh[j + 1], height[u]);
      }
    }
    for (int j = 0; j < K; j++) {
      int u = e[v][j];
      if (u != p) {
        height_up[u] = height_up[v] + 1;             
        height_up[u] = max(height_up[u], preh[j] + 2);
        height_up[u] = max(height_up[u], sufh[j + 1] + 2);
        if (mxh == u) {                 
          hp[u] = H();
          int high_now = max(preh[j], sufh[j + 1]) + 1;
          high_now = max(high_now, height_up[v]);
          for (int u2 : e[v]) {
            if (u2 != u) {
              if (u2 == p) {
                hp[u] *= hp[v] + R[high_now];
              } else {
                hp[u] *= hsub[u2] + R[high_now];
              }
            }
          }
        } else {
          hp[u] = hsh;                  
          hp[u] *= (hsub[u] + R[high]).inv(); 
        }
        Add(hp[u]);
        dfs(u, v);
        Del(hp[u]);
      }
    }
    Add(hsub[v]);
  };
  dfs(0, -1);
  cout << ans + 1 << '\n';                                                                                                 
  return 0;
}
  