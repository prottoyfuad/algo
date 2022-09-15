
template <typename T, 
          typename Fun = std::function<T(const T&, const T&)>>
struct Segtree {
  T unit;
  int n, m; 
  Fun unite;
  std::vector<T> tree;
  Segtree(int n_ = 0, T u = T()) : unit(u), n(n_) {
    m = 1;
    while (m < n) m *= 2;
    tree = std::vector<T> (m * 2 - 1, unit);
  }
  void apply(int u, T w) {
    u += m - 1;
    tree[u] = w;
    while (u > 0) {
      --u >>= 1;
      int v = u << 1;
      tree[u] = unite(tree[v + 1], tree[v + 2]);
    }
  }
  T get(int l, int r) {
    T u = unit, v = unit;
    l += m - 1, r += m - 1;
    while (l < r) {
      if (~l & 1) u = unite(u, tree[l++]);
      if (~r & 1) v = unite(tree[--r], v);
      l >>= 1, r >>= 1;
    }
    return unite(u, v);
  }
  T operator[] (int at) { return get(at, at + 1); }
};
 
