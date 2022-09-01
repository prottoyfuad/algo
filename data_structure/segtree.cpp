
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


template <typename T>
struct Segment_tree{
  int n, m;
  vector<T> t;
  Segment_tree(const vector<T>& a) : m(1) {
    n = (int) a.size(), m = 1;
    while (m < n) m *= 2;
    t = vector<T>(m * 2 - 1, 0);
    for (int i = 0; i < n; i++){
      t[m - 1 + i] = a[i];
    }
  }
  T operator[] (int k) {
    k += m - 1;
    T ans = t[k];
    while (k > 0){
      k = (k - 1) / 2;
      ans += t[k];
    }
    return ans;
  }
  void range_add(int L, int R, T x, int i, int l, int r){
    if (R <= l || r <= L){
      return;
    } 
    if (L <= l && r <= R){
      t[i] += x;
      return;
    } 
    int m = (l + r) / 2, j = i * 2;
    range_add(L, R, x, j + 1, l, m);
    range_add(L, R, x, j + 2, m, r);
  }
  void range_add(int L, int R, T x){
    range_add(L, R, x, 0, 0, m);
  }
};
 