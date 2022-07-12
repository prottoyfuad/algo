
#include <bits/stdc++.h>

// #include <vector>
// #include <cassert>
// #include <iostream>
// #include <functional>

template <typename T, typename Fun = std::function<T(const T&, const T&)>>
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

// ^ this is probably the simplest

template <typename T, class Fun = std::function<T(const T&, const T&)>>
class SparseTable {
private:
  int n;
  Fun fun;
  std::vector<std::vector<T>> mat;
  void init() {
    int max_log = 32 - __builtin_clz(n);
    for (int x = 1, p = 1; x < max_log; x++, p <<= 1) {
      int k = n + 1 - p * 2;
      mat.emplace_back(k);
      for (int i = 0; i < k; i++) {
        mat[x][i] = fun(mat[x - 1][i], mat[x - 1][i + p]);
      }
    }
  }
public:
  SparseTable() {}
  SparseTable(const std::vector<T>& a, const Fun& f) : fun(f) {
    n = static_cast<int>(a.size());
    mat.emplace_back(a);
    init();
  }
  SparseTable(int n_, const T* aa, const Fun& f) : n(n_), fun(f) {
    mat.emplace_back(n);
    for (int i = 0; i < n; i++) mat[0][i] = aa[i];
    init();
  }
  inline T get(int u, int v) const {
    assert(0 <= u && u < v && v <= n);
    int x = 31 - __builtin_clz(v - u);
    return fun(mat[x][u], mat[x][v - (1 << x)]);
  }
};

template <typename T, const unsigned L = 20> struct Sparse {
  int n;
  T aa[L][1 << L];
  inline T unite(T& a, T& b) const { return std::min(a, b); }
  void build(const std::vector<T>& a) {
    n = a.size();
    for (int i = 0; i < n; i++) aa[0][i] = a[i];
    init();
  }
  void build(int n_, const T* a) {
    n = n_;
    for (int i = 0; i < n; i++) aa[0][i] = a[i];
    init();
  }
  void init() {
    for (int j = 1, p = 1; j < L; j++) {
      int d = p; p <<= 1;
      for (int i = 0; i + p <= n; i++) {
        aa[j][i] = unite(aa[j - 1][i], aa[j - 1][i + d]);
      }
    }
  }
  inline T get(int l, int r) const {
    int x = 31 - __builtin_clz(r - l);
    return unite(aa[x][l], aa[x][r - (1 << x)]);
  };
};

int main() {
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(0);
#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif


  return 0;
}