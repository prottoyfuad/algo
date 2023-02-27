
// find leftmost;

template <typename T> struct Segtree {
  int n;
  T unit;
  std::vector<T> t;
  std::function<T(const T&, const T&)> unite;         
  Segtree(int S = 0, T u = T()) : n(1), unit(u) {
    while (n < S) n *= 2;
    t = std::vector<T>(n * 2 - 1, unit);
  }
  void add(int k, const T& x) {                              
    k += n - 1;
    t[k] = unite(t[k], x);
    while (k > 0) {
      k = (k - 1) / 2;       
      t[k] = unite(t[k * 2 + 1], t[k * 2 + 2]);
    }          
  }
  void del(int k) {
    k += n - 1;  
    t[k] = unit;
    while (k > 0) {
      k = (k - 1) / 2;                           
      t[k] = unite(t[k * 2 + 1], t[k * 2 + 2]);
    }          
  }
  int find(const int L, const int R, const T& x, int i, int l, int r) {
    if (R <= l || r <= L || t[i] < x) {
      return n;
    } 
    if (r - l == 1) { 
      return t[i] < x ? n : l;
    } 
    int m = (l + r) / 2, j = i * 2;
    int lhs = find(L, R, x, j + 1, l, m);
    if (lhs ^ n) return lhs;
    return find(L, R, x, j + 2, m, r);
  }
  int find(const int L, const int R, const T& x) {
    return find(L, R, x, 0, 0, n);
  }
};
