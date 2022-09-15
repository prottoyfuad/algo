
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
 
