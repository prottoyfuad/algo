
template <typename T, 
          typename Fun = std::function<T(const T&, const T&)>>
struct SparseTable {
  int n;
  Fun fun;
  std::vector<std::vector<T>> f;

  SparseTable() {}
  SparseTable(const std::vector<T>& a, const Fun& f) : fun(f) {
    n = static_cast<int> (a.size());
    int m = 32 - __builtin_clz(n);
    f.resize(m);
    f[0] = a;
    for (int x = 1, p = 1; x < m; x++) {
      int d = p; p += p;
      f[x].resize(n - p + 1);
      for (int i = 0; i + p <= n; i++) {
        f[x][i] = fun(f[x - 1][i], f[x - 1][i + d]);
      }
    }
  }

  T get(int l, int r) const {
    assert(0 <= l && l < r && r <= n);
    int x = 31 - __builtin_clz(r - l);
    return fun(f[x][l], f[x][r - (1 << x)]);
  }
};
