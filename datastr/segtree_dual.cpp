
template <typename T> struct segtree {
  int n;
  std::vector<T> tree;
  segtree() : n() {}
  segtree(int s_ = 0) : n(1) {
    while (n < s) n *= 2;
    tree.assign(n * 2 - 1, T());
  }
  template <typename U> void build(const std::vector<U>& a) {
    int s = (int) a.size();
    n = 1;
    while (n < s) n *= 2;
    tree.assign(n * 2 - 1, T());
    for (int i = 0; i < s; i++) {
      tree[n - 1 + i] = static_cast<T>(a[i]);
    }
  }
  T operator[] (int k) {
    k += n - 1;
    T ans = tree[k];
    while (k > 0) {
      k = (k - 1) / 2;
      ans += tree[k];
    }
    return ans;
  }
  void add(int L, int R, T x, int i, int l, int r) {
    if (R <= l || r <= L) {
      return;
    } 
    if (L <= l && r <= R) {
      tree[i] += x;
      return;
    } 
    int m = (l + r) / 2, j = i * 2;
    add(L, R, x, j + 1, l, m);
    add(L, R, x, j + 2, m, r);
  }
  void add(int L, int R, T x) {
    add(L, R, x, 0, 0, n);
  }
};
 
// maybe it needs to be commutitive
struct node {
  var val = ...;

  void operator += (const node& o) {
    // merge, dont think set is possible
  }
};

