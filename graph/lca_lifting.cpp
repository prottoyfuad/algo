
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
  vector anc(L, vector<int> (n, -1));
  vector<int> dep(n);
  vector<int> que(1);
  for (int i = 0; i < (int) que.size(); i++) {
    int v = que[i];
    for (int u : E[v]) {
      if (u != anc[0][v]) {
        dep[u] = dep[v] + 1;
        anc[0][u] = v;
        que.push_back(u);  
      }
    }
  }
  for (int j = 1; j < L; j++) {
    for (int i = 0; i < n; i++) {
      if (anc[j - 1][i] != -1) {
        anc[j][i] = anc[j - 1][anc[j - 1][i]];
      }
    }
  }
  auto get_anc = [&](int v, int k) {
    for (int j = L - 1; j >= 0; j--) {
      if (k >> j & 1) {
        v = anc[j][v];
      }
    }
    return v;
  };
  auto get_lca = [&](int u, int v) {
    if (dep[u] > dep[v]) {
      swap(u, v);
    }
    v = get_anc(v, dep[v] - dep[u]);
    if (u == v) {
      return u;
    }
    for (int j = L - 1; j >= 0; j--) {
      if (anc[j][u] ^ anc[j][v]) {
        u = anc[j][u];
        v = anc[j][v];
      }
    }
    return anc[0][u];
  };
  auto get_dist = [&](int u, int v) {
    return dep[u] + dep[v] - 2 * dep[get_lca(u, v)];
  };
  return 0;
}

