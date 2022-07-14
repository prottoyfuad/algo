
#include <bits/stdc++.h>

struct Dsu {
  int n;
  std::vector<int> f;
  Dsu(int n_) : n(n_), f(n_, -1) {}
  int trace(int u) {
    while (f[u] >= 0) {
      if (f[f[u]] >= 0) f[u] = f[f[u]];
      u = f[u];
    }
    return u;
  }
  bool is_trace(int u) {
    return f[u] < 0;
  }
  bool is_friends(int u, int v) {
    return trace(u) == trace(v);
  }
  int size(int u) {
    return -f[trace(u)];
  }  
  int unite(int u, int v) {
    u = trace(u), v = trace(v);
    if (u == v) return -1;
    if (f[u] < f[v]) std::swap(u, v);
    f[v] += f[u];
    f[u] = v;
    return v;
  }
  std::vector<std::vector<int>> get_all() {
    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < n; i++) {
      if (f[i] < 0) g[i].reserve(-f[i]);
    }
    for (int i = 0; i < n; i++) {
      g[trace(i)].push_back(i);
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

struct Dsu {
  int n;
  std::vector<int> data;
  Dsu(int n_ = 0) : n(n_), data(n_, -1) {}
  
  int trace(int u) {
    assert(u >= 0 && u < n);
    if (data[u] < 0) return u;
    return data[u] = trace(data[u]);
  }

  int size(int u) { return -data[trace(u)]; }
  bool is_trace(int u) { return data[u] < 0; }
  bool is_friends(int u, int v) { return trace(u) == trace(v); }

  bool unite(int u, int v) {
    assert(std::min(u, v) >= 0 && std::max(u, v) < n);
    u = trace(u), v = trace(v);
    if (u == v) return false;
    if (data[u] < data[v]) std::swap(u, v);
    data[v] += data[u];
    data[u] = v;
    return true;
  }

  std::vector<std::vector<int>> get_groups() {
    std::vector<int> traces(n);
    for (int i = 0; i < n; i++) traces[i] = trace(i);
    // Saving traces isn't necessay, but it should be a bit faster

    std::vector<std::vector<int>> groups(n);
    for (int i = 0; i < n; i++) groups[i].reserve(i == traces[i] ? -data[i] : 0);
    for (int i = 0; i < n; i++) groups[traces[i]].push_back(i);
    groups.erase(
      std::remove_if(groups.begin(), groups.end(), [&](const std::vector<int>& v) {
        return v.empty();
      }),
      groups.end()
    );
    return groups;
  }
};

class Disjoint_set {
public :
  int n;
  std::vector<int> p, sub;
  Disjoint_set() : n() {}
  Disjoint_set(int _n) : n(_n) {
    assert(n > 0);
    p.resize(n);
    sub.resize(n, 1);
    std::iota(p.begin(), p.end(), 0);
  }
  inline int trace(int x) {
    while(x != p[x]) x = p[x] = p[p[x]];
    return x;
  }
  inline bool unite(int x, int y) {
    x = trace(x), y = trace(y);
    if(x == y) return false;
    if(sub[x] > sub[y]) std::swap(x, y);
    p[x] = y, sub[y] += sub[x];
    return true;
  }
};

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  #ifdef _hogwarts
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
  #endif
  // int n, q;
  // cin >> n >> q;
  Disjoint_set dset(100);
  // while(q--) {}
  return 0;
}
