  
template <typename T, 
          typename Fun = std::function<T(const T&, const T&)>>
struct Segtree {
  int n; 
  T unit;
  Fun unite;
  std::vector<T> tree;
  Segtree() : n() {}
  Segtree(int s, const T& u, const Fun& fn) : n(1), unit(u), unite(fn) {
    while (n < s) n *= 2;
    tree = std::vector<T> (n * 2 - 1, unit);
  }
  void add(int u, T w) {
    u += n - 1;
    tree[u] = w;
    while (u > 0) {
      --u >>= 1;
      int v = u << 1;
      tree[u] = unite(tree[v + 1], tree[v + 2]);
    }
  }
  T get(int l, int r) {
    T u = unit, v = unit;
    l += n - 1, r += n - 1;
    while (l < r) {
      if (~l & 1) u = unite(u, tree[l++]);
      if (~r & 1) v = unite(tree[--r], v);
      l >>= 1, r >>= 1;
    }
    return unite(u, v);
  }
  T operator[] (int at) { return get(at, at + 1); }
};
  