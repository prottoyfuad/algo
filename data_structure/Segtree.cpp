/*
  implementation 1
  use monoid as T which contains default constructor, implicit constructors and +operator
*/
template <typename T> struct Segtree {
  int n;
  std::vector<T> tree;
  Segtree() : n() {}
  Segtree(int s) : n(1) {
    while (n < s) n *= 2;
    tree = std::vector<T> (n * 2 - 1);
  }
  void apply(int u, const T& w) {
    u += n - 1;
    tree[u] = w;
    while (u > 0) {
      --u >>= 1;
      int v = u << 1;
      tree[u] = tree[v + 1] + tree[v + 2];
    }
  }
  T get(int l, int r) {
    T u, v;
    l += n - 1, r += n - 1;
    while (l < r) {
      if (~l & 1) u = u + tree[l++];
      if (~r & 1) v = tree[--r] + v;
      l >>= 1, r >>= 1;
    }
    return u + v;
  }
  T operator[] (int at) { return get(at, at + 1); }
};

/*
  implementation 2
  send default unit value and unite(+) function as template parameter
*/  
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
  