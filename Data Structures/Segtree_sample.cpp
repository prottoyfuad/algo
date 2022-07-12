
#include <vector>
#include <iostream>
#include <algorithm>

namespace Segtree {

template <typename T, typename F = std::function<T(const T&, const T&)>>
struct Segtree {
  int m, n;
  T unit;
  F unite;
  std::vector<T> tree;
  Segtree(int _n = 0, T u = T()) : m(1), n(_n), unit(u) {
    m <<= std::__lg(n) + ((n & (n - 1)) != 0);
    tree = std::vector<T> (m * 2 - 1, unit);
  }
  Segtree(int _n, T u, F f) : m(1), n(_n), unit(u), unite(f) {
    m <<= std::__lg(n) + ((n & (n - 1)) != 0);
    tree = std::vector<T> (m * 2 - 1, unit);
  }
  void apply(int u, int w) {
    u += m - 1;
    tree[u] = unite(tree[u], w);
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
  T get(int at) { return get(at, at + 1); }
};
 
struct Segment {
  int mn, tot;
  Segment(int m = 1e9 + 7, int t = 0) : mn(m), tot(t) {}  
  friend Segment operator + (const Segment& x, const Segment& y) {
    return Segment(std::min(x.mn, y.mn), x.tot + y.tot);
  }
};

template <typename T> struct range_query {
  int n, m;
  T unit;
  std::vector<T> t;
  range_query(int n_ = 0, T u = T()) : n(n_), m(1), unit(u) {
    while (m < n) m *= 2;
    t.resize(m * 2 - 1, unit);
  }
  void update(int x, T w) {
    t[x += m - 1] = w;
    while (x > 0) {
      --x >>= 1;
      t[x] = t[x * 2 + 1] + t[x * 2 + 2];
    }
  }
  T get(int L, int R, int x, int l, int r) {
    if (l >= R || r <= L) {
      return unit;
    }
    else if (l >= L && r <= R) {
      return t[x];
    }
    else {
      int m = (l + r) >> 1, y = x << 1;
      return get(L, R, y + 1, l, m) + get(L, R, y + 2, m, r); 
    }
  }
  T get(int l, int r) {
    return get(l, r, 0, 0, m);
  }
};

template <typename T> struct range_update {
  int n, m;
  T unit;
  std::vector<int> t;
  range_update(int n_ = 0, T u = T()) : n(n_), m(1), unit(u) {
    while (m < n) m *= 2;
    t.resize(m * 2 - 1, unit);
  }  
  void update(int L, int R, T w, int x, int l, int r) {
    if (l >= R || r <= L) {
      return;
    }
    else if (l >= L && r <= R) {
      t[x] = w;
      return;
    }
    else {
      int m = (l + r) >> 1, y = x << 1;
      if (t[x] != unit) {
        t[y + 1] = t[y + 2] = t[x];
        t[x] = unit;
      }
      update(L, R, w, y + 1, l, m);
      update(L, R, w, y + 2, m, r); 
    }
  }
  void update(int l, int r, T w) { update(l, r, w, 0, 0, m); }
  void update(int x, T w) { update(x, x + 1, w, 0, 0, m); }
  T operator[] (int x) {
    T res = t[x += m - 1];
    while (x > 0) {
      --x >>= 1;
      if (t[x] != -1) res = t[x];
    }
    return res;
  }
};

} // namespace Segtree

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while(tt--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      a[i] -= 1;
    }
    Segtree::range_query<Segtree::Segment> inversions(n);
    Segtree::range_update<int> dp(n, -1);
    int ans = 0;
    for (int i = 0; i < n; i++) {
      auto [now, tot] = inversions.get(a[i] + 1, n);
      if (tot == 0) {
        ans += 1;
        dp.update(i, ans);
      } else {
        ans = dp[now];
        dp.update(now, i + 1, ans);
      }
      inversions.update(a[i], Segtree::Segment(i, 1));
    }
    cout << ans << '\n';
  }
  return 0;
}
 