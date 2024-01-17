  
#include <set>
#include <vector>
#include <iostream>
#include <functional>

using namespace std;

struct Centroid_tree {
  int n;
  vector<vector<int>> e;
  vector<int> par;
  vector<int> sub;
  vector<bool> was;
  Centroid_tree(int s = 0) : n(s), e(s), par(s), sub(s), was(s) { 
  }
  void add_edge(int u, int v) {
    e[u].push_back(v);
    e[v].push_back(u);
  }
  void calc_sub(int v, int p = -1) {
    sub[v] = 1;
    for (int u : e[v]) {
      if (u != p && !was[u]) {
        calc_sub(u, v);
        sub[v] += sub[u];
      }
    }               
  }
  int find_centroid(int v, const int s, int p = -1) {
    for (int u : e[v]) {
      if (u != p && !was[u] && sub[u] > s / 2) {
        return find_centroid(u, s, v);
      }
    }
    return v;
  }
  void decompose(int v, int p = -1) {
    calc_sub(v);                                 
    int c = find_centroid(v, sub[v]);                                
    was[c] = 1;
    par[c] = p;
    for (int u : e[c]) {
      if (!was[u]) {
        decompose(u, c);
      }
    }
  } 
  int operator[] (int v) {
    return par[v];
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<vector<pair<int, int>>> e(n);
  Centroid_tree f(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--;
    v--;
    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
    f.add_edge(u, v);
  }
  f.decompose(0);                  
  int L = 32 - __builtin_clz(n);
  vector anc(n, vector<int> (L, -1));
  vector<int> dep(n);
  vector<int> dis(n);
  {
    function<void(int, int)> dfs = [&](int v, int p) {
      anc[v][0] = p;
      for (int j = 1; j < L; j++) {
        if (anc[v][j - 1] != -1) {
          anc[v][j] = anc[anc[v][j - 1]][j - 1];
        }
      }
      for (auto [u, w] : e[v]) {
        if (u != p) {
          dep[u] = dep[v] + 1;
          dis[u] = dis[v] + w;
          dfs(u, v);
        }
      }
    };
    dfs(0, -1);
  }
  auto dist = [&](int u, int v) {
    int res = dis[u] + dis[v];                                             
    if (dep[u] > dep[v]) swap(u, v);
    int x = dep[v] - dep[u];
    for (int j = L - 1; j >= 0; j--) {
      if (x >> j & 1) {
        v = anc[v][j];          
      }
    }                                                     
    if (u == v) return res - dis[u] * 2;
    for (int j = L - 1; j >= 0; j--) {
      if (anc[u][j] ^ anc[v][j]) {
        u = anc[u][j];
        v = anc[v][j];
      }
    }                                                  
    return res - dis[anc[v][0]] * 2;
  };
  int m;
  cin >> m;
  vector<set<pair<int, pair<int, int>>>> ans(n);
  for (int i = 0; i < m; i++) {
    int t, v;
    cin >> t >> v;
    t--;
    v--;
    if (t) {
      int res = 0, when = -1;
      for (int u = v; u >= 0; u = f[u]) {
        int d_now = dist(u, v);
        auto it = lower_bound(ans[u].begin(), ans[u].end(), make_pair(d_now, make_pair(-1, -1)));
        if (it != ans[u].end()) {
          auto [c, w] = it->second;
          if (w > when) when = w, res = c;  
        }
      }
      cout << res << '\n';
    }
    else {
      int d, c;
      cin >> d >> c;
      for (int u = v; u >= 0; u = f[u]) {
        int d_now = d - dist(u, v);
        if (d_now >= 0) {
          for (auto it = ans[u].begin(); it != ans[u].end(); it = ans[u].erase(it)) {
            if (it->first > d_now) break;
          }
          ans[u].emplace(d_now, make_pair(c, i));
        }
      }
    }
  }
  return 0;
}
  
