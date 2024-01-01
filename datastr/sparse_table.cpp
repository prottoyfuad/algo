
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

