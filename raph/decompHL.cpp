  
#include <vector>
#include <iostream>
#include <functional>

using namespace std; 

template <typename T> struct Segtree {
  int m, n;
  T unit;
  vector<T> t;
  Segtree(int n, T u) : m(1), n(n), unit(u) {
    while (m < n) m *= 2;
    t.assign(m * 2 - 1, unit);
  }
  inline T fun(const T& u, const T& v) {
    return max(u, v);
  }
  void add(int x, const T& v) {
    x += m - 1;
    t[x] = v;
    while (x > 0) {
      --x /= 2;
      t[x] = fun(t[x * 2 + 1], t[x * 2 + 2]);
    }
  }
  T get(int l, int r) {
    T lhs = T();
    T rhs = T();
    l += m - 1;
    r += m - 1; 
    while (l < r) {
      if (~l & 1) lhs = fun(lhs, t[l++]);
      if (~r & 1) rhs = fun(t[--r], rhs);
      l /= 2, r /= 2;
    }
    return fun(lhs, rhs);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);            
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<vector<int>> e(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  vector<int> sub(n);
  vector<int> dep(n);
  vector<int> par(n);
  {
    par[0] = -1;
    function<void(int)> dfs = [&](int v) {
      sub[v] = 1;
      int who = -1;
      for (int i = 0; i < (int) e[v].size(); i++) {
        int u = e[v][i];
        if (u != par[v]) {
          par[u] = v;
          dep[u] = dep[v] + 1;
          dfs(u);
          sub[v] += sub[u];
          if (who == -1 || sub[u] > sub[e[v][who]]) {
            who = i;
          }
        }
      }
      if (who != -1) swap(e[v][0], e[v][who]);
    };  
    dfs(0);
  }
  vector<int> top(n);
  vector<int> pos(n);
  {
    int timer = 0;
    function<void(int)> dfs = [&](int v) {
      pos[v] = timer++;
      for (int i = 0; i < (int) e[v].size(); i++) {
        int u = e[v][i];
        if (u != par[v]) {
          top[u] = i ? u : top[v];
          dfs(u);
        }
      }
    };
    dfs(0);
  }
  Segtree<int> f(n, -1);
  for (int i = 0; i < n; i++) {
    f.add(pos[i], a[i]);
  }
  for (int i = 0; i < m; i++) {
    int t, u, v;
    cin >> t >> u >> v;
    t--;
    u--;
    if (t) {
      v--;
      int ans = -1;
      while (true) {
        int x = top[u];
        int y = top[v];
        if (x == y) {
          if (dep[u] > dep[v]) {
            swap(u, v);
          }
          ans = max(ans, f.get(pos[u], pos[v] + 1));
          break;
        }
        else if (dep[x] > dep[y]) {
          ans = max(ans, f.get(pos[x], pos[u] + 1));
          u = par[x];
        }
        else {
          ans = max(ans, f.get(pos[y], pos[v] + 1));
          v = par[y];
        }
      }
      cout << ans << '\n';
    }
    else {
      f.add(pos[u], a[u] = v);
    }
  }
  return 0;
}
  