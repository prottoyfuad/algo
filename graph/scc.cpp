
struct SCC {
  int k;
  std::vector<int> id;
  std::vector<int> order;
  std::vector<bool> used;
  std::vector<std::vector<int>> comps;
  std::vector<std::vector<int>> tree;

  void dfs1(const std::vector<std::vector<int>>& E, int v) {
    used[v] = 1;
    for (int u : E[v]) {
      if (!used[u]) {
        dfs1(E, u);
      }
    }
    order.push_back(v);
  }  

  void dfs2(const std::vector<std::vector<int>>& E, int v) {
    used[v] = 1;
    id[v] = k;
    comps.back().push_back(v);
    for (int u : E[v]) {
      if (!used[u]) {
        dfs2(E, u);
      }
    }
  }  

  SCC() : k(0) {}
  SCC(const std::vector<std::vector<int>>& E) {
    int n = (int) E.size();
    used = std::vector<bool> (n);
    order.reserve(n); 
    for (int i = 0; i < n; i++) {
      if (!used[i]) {
        dfs1(E, i);
      }
    }
    std::reverse(order.begin(), order.end());    
    std::vector<std::vector<int>> rev(n);
    for (int i = 0; i < n; i++) {
      for (int u : E[i]) {
        rev[u].push_back(i);
      }
    }
    id = std::vector<int> (n);
    used = std::vector<bool> (n);
    k = 0;
    for (int i : order) {
      if (!used[i]) {
        comps.emplace_back();
        dfs2(rev, i);
        k += 1;
      }
    }
    T.resize(k);
    for (int v = 0; v < N; v++) {
      for (int u : E[v]) {
        if (id[u] != id[v]) {
          T[id[v]].push_back(id[u]);
        }
      }
    }
  }

  int operator[] (int v) {
    return id[v];
  }

  int size(int k = -1) {
    if (k == -1) return (int) comps.size();
    return (int) comps[k].size();
  }
};

