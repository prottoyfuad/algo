
#include <vector>
#include <cassert>
#include <iostream>

#include <algorithm>

void fast_run() {
  int n;
  cin >> n;
  vector<vector<int>> E(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    E[u].push_back(v);
    E[v].push_back(u);
  }
  int L = 32 - __builtin_clz(n);
  vector anc(n, vector<int> (L, -1));
  vector<int> d(n), bfs(1);
  for (int i = 0; i < (int) bfs.size(); i++) {
    int v = bfs[i];
    for (int u : E[v]) {
      if (anc[v][0] != u) {
        d[u] = d[v] + 1;
        anc[u][0] = v;
        bfs.push_back(u);  
      }
    }
  }
  for (int j = 1; j < L; j++) {
    for (int i = 0; i < n; i++) {
      if (anc[i][j - 1] != -1) {
        anc[i][j] = anc[anc[i][j - 1]][j - 1];
      }
    }
  }
  auto Get = [&](int v, int k) {
    for (int j = L - 1; j >= 0; j--) {
      if (k >> j & 1) {
        v = anc[v][j];
      }
    }
    return v;
  };
  auto LCA = [&](int u, int v) {
    if (d[u] > d[v]) swap(u, v);
    v = Get(v, d[v] - d[u]);
    if (u == v) return u;
    for (int j = L - 1; j >= 0; j--) {
      if (anc[u][j] ^ anc[v][j]) {
        u = anc[u][j];
        v = anc[v][j];
      }
    }
    return anc[u][0];
  };
    // LCA(x, y);
}
/*
  binary lifting to find kth Ancestor, if ancestor < k, returns -1
  alternatively we can just return root, if anc < k, without initialising
#problems :
  1. https://leetcode.com/problems/kth-ancestor-of-a-tree-node
  2. https://www.spoj.com/problems/LCASQ
*/

struct Tree_ancestor {
  int n, m;
  std::vector<int> depth;
  std::vector<std::vector<int>> mat;
  Tree_ancestor() {}
  Tree_ancestor(const std::vector<int>& p, const std::vector<int>& d) : depth(d) {
    n = p.size(), m = std::__lg(n) + 1;
    mat = std::vector<std::vector<int>> (m, std::vector<int> (n, -1));
    mat[0] = p;
    for (int x = 1; x < m; x++) {
      for (int i = 0; i < n; i++) {
        if (mat[x - 1][i] != -1) {
          mat[x][i] = mat[x - 1][ mat[x - 1][i] ];
        }
      }
    }
  }
  int get_anc(int v, int k) {
    if (k > depth[v]) return -1;
    for (int x = m - 1; x >= 0; x--) {
      if (k >= (1 << x)) {
        v = mat[x][v];
        k -= 1 << x;
      }
    }
    return v;
  }
  int get_lca(int u, int v) {
    if (depth[u] > depth[v]) std::swap(u, v);
    if (depth[u] != depth[v]) v = get_anc(v, depth[v] - depth[u]);
    if (u == v) return u;
    for (int x = m - 1; x >= 0; x--) {
      if (mat[x][u] != mat[x][v]) {
        u = mat[x][u], v = mat[x][v];
      }
    }
    return mat[0][u];
  }
  int get_distance(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
  }
};

struct TreeAncestor {
  int n, m;
  std::vector<std::vector<int>> anc;
  std::vector<int> depth;
  TreeAncestor(std::vector<int>& parent) {
    n = parent.size(), m = std::__lg(n) + 1;
    anc = std::vector<std::vector<int>> (n, std::vector<int> (m, -1));
    for (int i = 0; i < n; i++) {
      anc[i][0] = parent[i];
    }
    for (int x = 1; x < m; x++) {
      for (int i = 1; i < n; i++) {
        int was = anc[i][x - 1];
        if (was != -1) anc[i][x] = anc[was][x - 1];
      }
    }
  }
  TreeAncestor(std::vector<std::vector<int>>& graph, bool initdepth = true) {
    n = graph.size();
    std::vector<int> parent(n, -1);
    for (int i = 0; i < n; i++) {
      for (int j : graph[i]) parent[j] = i;
    }
    *this = parent;
    if (initdepth) {
      depth.resize(n, -1);
      dfs(graph);
    }
  }
  void dfs(std::vector<std::vector<int>>& g, int u = 0, int p = -1) {
    for (int v : g[u]) {
      depth[v] = depth[u] + 1;
      if (v != p) dfs(g, v, u);
    }
  }
  // here kth ancestor might not exist i.e. -1
  // hence the check to avoid out of bounds
  int getAncestor(int u, int k) {
    for (int x = m - 1; x >= 0; x--) {
      if (k >= (1 << x)) {
        u = anc[u][x];
        k -= 1 << x;
        if (u < 0) return u;
      }
    }
    return u;
  }
  int getLCA(int u, int v) {
    if (depth[u] > depth[v]) std::swap(u, v);
    int d = depth[v] - depth[u];
    v = getAncestor(v, d);
    if (u == v) return u;
    assert(depth[u] == depth[v]);    
    for (int x = m - 1; x >= 0; x--) {
      if (anc[u][x] != anc[v][x]) {
        u = anc[u][x], v = anc[v][x];
      }
    }
    assert(anc[u][0] == anc[v][0]);
    return anc[u][0];
  }

  void show() {
    for (int i = 0; i < n; i++) {
      std::cout << i << " : ";
      for (int j = 0; j < m; j++) std::cout << anc[i][j] << ' ';
      std::cout << '\n';
    }
  }
};

using namespace std;

void test() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int& e : a) cin >> e;
  TreeAncestor t(a);
  t.show();
  while (q--) {
    int x, k;
    cin >> x >> k;
    cout << x <<' '<< t.getAncestor(x, k) << '\n';
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  #ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
  #endif
  int n, m;
  cin >> n;
  vector<vector<int>> g(n);
  for (int i = 0; i < n; i++) {
    cin >> m;
    for (int x, j = 0; j < m; j++) {
      cin >> x;
      g[i].emplace_back(x);
    }
  }
  TreeAncestor anc(g, true);
  // anc.show();
  cin >> m;
  while(m--) {
    int u, v;
    cin >> u >> v;
    int ans = anc.getLCA(u, v);
    assert(ans != -1);
    cout << ans << '\n';
  }
  return 0;
}
