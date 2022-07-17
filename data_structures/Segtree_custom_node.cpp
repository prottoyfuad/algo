
#include <vector>
#include <cassert>
#include <iostream>
#include <functional>
 
struct Segment {
  long long value, lazy;
  
  template <typename T = int>
  Segment(const T& v = 0) : value(v), lazy(-1) {}
  
  void apply(const Segment& w) {
    // propagate to this from parent
    
  }
    
  void eval(int seg_size = 1) {
    // before propagating to child evaluate this segment
    
  }    
  
  Segment& unite(const Segment& lhs, const Segment& rhs) {
    value = lhs.value + rhs.value;
    
    return *this;
  }
};
 
struct Segtree {
  int m, n;
  std::vector<Segment> tree;
  Segtree(int s = 0) : m(1), n(s) {
    while (m < n) m *= 2;
    tree = std::vector<Segment> (m * 2 - 1);
  }
  template <typename T> 
  void init(const std::vector<T>& a) {
    assert((int) a.size() == n);
    for (int i = 0; i < n; i++) {
      tree[i + m - 1] = a[i];
    }
    for (int i = m - 2; i >= 0; i--) {
      tree[i].unite(tree[i * 2 + 1], tree[i * 2 + 2]);
    }
  }
  void push(int u, int l, int r) {    
    if (tree[u].increase + tree[u].change == 0) return;
    assert((tree[u].change > 0) + (tree[u].increase > 0) != 2);
    int v = u << 1;
    if (u < m - 1) {
      tree[v + 1].apply(tree[u]);
      tree[v + 2].apply(tree[u]);
    }
    tree[u].eval(std::min(n, r) - l);
  }
  void apply(int L, int R, const Segment& w, int u, int l, int r) {
    push(u, l, r);
    if (l >= R || r <= L) return;
    if (l >= L && r <= R) {
      tree[u].apply(w);
      push(u, l, r);
      return;
    }
    int mid = (l + r) >> 1, v = u << 1;
    apply(L, R, w, v + 1, l, mid);
    apply(L, R, w, v + 2, mid, r);
    tree[u].unite(tree[v + 1], tree[v + 2]);
  }
  void apply(int L, int R, const Segment& w) { apply(L, R, w, 0, 0, m); }
  void apply(int at, const Segment& w) { apply(at, at + 1, w, 0, 0, m); }
  
  Segment get(int L, int R, int u, int l, int r) {
    push(u, l, r);
    if (l >= R || r <= L) return Segment();
    if (l >= L && r <= R) return tree[u];
    int mid = (l + r) >> 1, v = u << 1;
    return Segment().unite(get(L, R, v + 1, l, mid), get(L, R, v + 2, mid, r));
  }
  Segment get(int L, int R) { return get(L, R, 0, 0, m); }
  Segment operator[] (int at) { return get(at, at + 1, 0, 0, m); }
};
 
using namespace std;
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  Segtree S(n);
  S.init(a);
  for (int i = 0; i < m; i++) {
    int t, l, r, v;
    cin >> t >> l >> r;
    --l;
    if (t == 3) {
      cout << S.get(l, r).value << '\n';
    } else {
      cin >> v;
      Segment w;
      w.lazy = v;
      S.apply(l, r, w);
    }
  }
  return 0;
}
 