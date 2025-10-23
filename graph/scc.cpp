
struct SCC {
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
    id[v] = comps.size() - 1;
    comps.back().push_back(v);
    for (int u : E[v]) {
      if (!used[u]) {
        dfs2(E, u);
      }
    }
  }

  SCC() {}
  SCC(const std::vector<std::vector<int>>& E) {
    int n = (int) E.size();
    used.resize(n);
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
    id.resize(n);
    std::fill(used.begin(), used.end(), 0);
    for (int i : order) {
      if (!used[i]) {
        comps.emplace_back();
        dfs2(rev, i);
      }
    }
    tree.resize(comps.size());
    std::set<std::pair<int, int>> was;
    for (int i = 0; i < n; i++) {
      for (int j : E[i]) {
        int v = id[i];
        int u = id[j];
        if (v != u && was.find({u, v}) == was.end()) {
          tree[v].push_back(u);
          was.emplace(u, v);
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
