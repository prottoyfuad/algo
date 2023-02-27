
template <typename T> struct Segtree_dual {
  int n;
  T unit;
  std::vector<T> t;
  std::function<T(T, T)> unite;
  Segtree_dual(int S = 0, T u = T()) : n(1), unit(u) {
    while (n < S) n *= 2;
    t = std::vector<T>(n * 2 - 1, unit);
  }
  template <typename U>
  Segtree_dual(const std::vector<U>& a, const T& u, const std::function<T(T, T)>& fun) 
  : n(1), unit(u), unite(fun) {
    int S = (int) a.size();
    while (n < S) n *= 2;
    t = std::vector<T>(n * 2 - 1, unit);
    for (int i = 0; i < S; i++){
      t[n - 1 + i] = a[i];
    }
  }
  T operator[] (int k) {
    k += n - 1;
    T ans = t[k];
    while (k > 0) {
      k = (k - 1) / 2;
      ans = unite(ans, t[k]);
    }
    return ans;
  }
  void add(int L, int R, T x, int i, int l, int r) {
    if (R <= l || r <= L) {
      return;
    } 
    if (L <= l && r <= R) {
      t[i] = unite(t[i], x);
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
 