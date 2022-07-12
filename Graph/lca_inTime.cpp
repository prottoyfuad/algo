 
#include <bits/stdc++.h>

template <typename T, 
          typename Fun = std::function<T(const T&, const T&)>>
struct Sparse_table {
  int n;
  Fun fun;
  std::vector<std::vector<T>> mat;
  Sparse_table() {}
  Sparse_table(const std::vector<T>& a, const Fun& f) : fun(f) {
    n = static_cast<int> (a.size());
    int m = 32 - __builtin_clz(n);
    mat.resize(m);
    mat[0] = a;
    for (int x = 1, p = 1; x < m; x++) {
      int d = p; p += p;
      mat[x].resize(n - p + 1);
      for (int i = 0; i + p <= n; i++) {
        mat[x][i] = fun(mat[x - 1][i], mat[x - 1][i + d]);
      }
    }
  }
  T get(int l, int r) const {
    assert(0 <= l && l < r && r <= n);
    int x = 31 - __builtin_clz(r - l);
    return fun(mat[x][l], mat[x][r - (1 << x)]);
  }
};


struct Tree {
  int n, t, root;
  std::vector<std::vector<int>> E;
  std::vector<int> dist, in, order;
  Sparse_table<int> S;

  void dfs(int v, int p) {
    in[v] = t++;
    order.push_back(v);
    for (int u : E[v]) {
      if (u ^ p) {
        dist[u] = dist[v] + 1;
        dfs(u, v);
        order.push_back(v);
        t++;
      }
    }
  }
  
  Tree() {}
  Tree(const std::vector<std::vector<int>>& e, int _root = 0) 
  : n((int) e.size()), t(0), root(_root), E(e), dist(n), in(n)
  {
    order.reserve(n * 2);
    dfs(root, -1);
    S = Sparse_table<int>(order, [&](const int& x, const int& y){
      return dist[x] < dist[y] ? x : y;
    });
  }

  int get_lca(int a, int b) const {
    if (in[a] > in[b]) std::swap(a, b);
    return S.get(in[a], in[b] + 1);
  }

  int get_dist(int a, int b) const {
    int low = get_lca(a, b);
    return dist[a] + dist[b] - dist[low] * 2;
  }
};

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    
  }
  return 0;
}
  