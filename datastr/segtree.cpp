
template <typename T> struct segtree {
  int n;
  std::vector<T> tree;
  segtree() : n() {}
  segtree(int s) : n(1) {
    while (n < s) n *= 2;
    tree.assign(n * 2 - 1, T());
  }
  void apply(int i, const T& w) {
    i += n - 1;
    tree[i] += w;
    while (i > 0) {
      --i >>= 1;
      int j = i << 1;
      tree[i] = tree[j + 1] + tree[j + 2];
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
  T operator[] (int i) { 
    return get(i, i + 1); 
  }
  int find_first(const int L, const int R, int i, int l, int r) {
    if (R <= l || r <= L || !t[i].good()) {
      return -1;
    } 
    if (r - l == 1) { 
      return l;
    } 
    int m = (l + r) / 2, j = i * 2;
    int lhs = find(L, R, x, j + 1, l, m);
    if (lhs != -1) {
      return lhs;
    }
    return find(L, R, x, j + 2, m, r);
  }
  int find(const int L, const int R) {
    return find_first(L, R, 0, 0, n);
  }
};

struct node {
  var val = ...;

  void operator += (const node& o) {
    // set or update
  }

  friend node operator+ (const node& lhs, const node& rhs) {
    // merge nodes
  }

  bool good() {
    // find condition
  }
};

