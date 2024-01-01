
struct dsu {
  int n;
  std::vector<int> f;

  dsu(int s) : n(s), f(s, -1) {}

  int trace(int u) {
    while (f[u] >= 0) {          
      // for somewhat path compression
      // if (f[f[u]] >= 0) f[u] = f[f[u]];
      u = f[u];
    }
    return u;
  }

  bool unite(int u, int v) {
    u = trace(u);
    v = trace(v);
    if (u != v) {
      if (f[u] < f[v]) {
        std::swap(u, v);
      }
      f[v] += f[u];
      f[u] = v;
      return 1; 
      // or return int(v), default -1
    }
    return 0;
  }

  std::vector<std::vector<int>> get_sets() {
    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
      p[i] = trace(i);
    }
    // pre calculating traces isn't necessay
    // but it should be a bit faster

    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < n; i++) {
      if (f[i] < 0) g[i].reserve(-f[i]);
    }
    for (int i = 0; i < n; i++) {
      g[p[i]].push_back(i);
    }
    g.erase(
      std::remove_if(g.begin(), g.end(), [&](const std::vector<int>& v) {
        return v.empty();
      }),
      g.end()
    );
    return g;
  }
};

