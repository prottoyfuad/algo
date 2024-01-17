
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

int main() {
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
  vector<int> d(n), que(1);
  for (int i = 0; i < (int) que.size(); i++) {
    int v = que[i];
    for (int u : E[v]) {
      if (anc[v][0] != u) {
        d[u] = d[v] + 1;
        anc[u][0] = v;
        que.push_back(u);  
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
  auto get_anc = [&](int v, int k) {
    for (int j = L - 1; j >= 0; j--) {
      if (k >> j & 1) {
        v = anc[v][j];
      }
    }
    return v;
  };
  auto get_lca = [&](int u, int v) {
    if (d[u] > d[v]) swap(u, v);
    v = get_anc(v, d[v] - d[u]);
    if (u == v) {
      return u;
    }
    for (int j = L - 1; j >= 0; j--) {
      if (anc[u][j] ^ anc[v][j]) {
        u = anc[u][j];
        v = anc[v][j];
      }
    }
    return anc[u][0];
  };
  return 0;
}

