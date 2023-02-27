  
#include <vector>
#include <cassert>  
#include <iostream>  
#include <functional>

const long long P = 998244353;
 
struct Segtree {  
  using T = long long;
  using U = std::pair<long long, long long>;  

  struct node {    
    static constexpr T def_t = 0;
    static constexpr U def_l = std::make_pair(1, 0);

    T val;
    U add;

    node() : val(def_t), add(def_l) {}
    node(const T& x) : val(x), add(def_l) {}

    void apply(int l, int r, U cost) {
      val *= cost.first;
      val %= P;
      val += cost.second * (r - l);
      val %= P;

      add.first *= cost.first;
      add.first %= P;
      add.second *= cost.first;
      add.second += cost.second;
      add.second %= P;
    }
  };

  node unite(const node& lhs, const node& rhs) {
    node res;
    res.val = (lhs.val + rhs.val) % P;
    return res;
  }

  int m, n;
  std::vector<node> tree;

  Segtree(int s = 0) : m(1), n(s) {
    while (m < n) m *= 2;
    tree = std::vector<node> (m * 2 - 1);
  }
  
  inline void push(int u, int l, int r) {    
    if (tree[u].add != node::def_l) {  
      if (u < m - 1) {
        int mid = (l + r) >> 1, v = u << 1;
        if (l < n) {
          tree[v + 1].apply(l, std::min(mid, n), tree[u].add);
        }
        if (mid < n) {
          tree[v + 2].apply(mid, std::min(r, n), tree[u].add);
        }
      }
      tree[u].add = node::def_l;
    }
  }

  inline void pull(int u) {
    if (u < m - 1) {
      int v = u << 1;
      tree[u] = unite(tree[v + 1], tree[v + 2]);
    }    
  }
                        
  void build(const std::vector<T>& a) {
    assert((int) a.size() == n);
    for (int i = 0; i < n; i++) {
      tree[i + m - 1] = node(a[i]);
    }
    for (int i = (int) tree.size() - 1; i >= n + m - 1; i--) {
      tree[i] = node();
    }
    for (int i = m - 2; i >= 0; i--) pull(i);
  }

  void apply(int L, int R, const U& w, int u, int l, int r) {
    if (l >= R || r <= L) {
      return;
    }
    if (l >= L && r <= R) {
      tree[u].apply(l, r, w);
      return;
    }
    push(u, l, r);
    int mid = (l + r) >> 1, v = u << 1;
    apply(L, R, w, v + 1, l, mid);
    apply(L, R, w, v + 2, mid, r);
    pull(u);
  }

  void apply(int L, int R, const U& w) { 
    apply(L, R, w, 0, 0, m); 
  }

  void apply(int at, const U& w) { 
    apply(at, at + 1, w, 0, 0, m); 
  }
  
  node get(int L, int R, int u, int l, int r) {
    if (l >= R || r <= L) {
      return node();
    }
    if (l >= L && r <= R) {
      return tree[u];
    }
    push(u, l, r);
    int mid = (l + r) >> 1, v = u << 1;
    node res = unite(get(L, R, v + 1, l, mid), get(L, R, v + 2, mid, r));
    pull(u);
    return res;
  }

  node get(int L, int R) { 
    return get(L, R, 0, 0, m); 
  }

  node operator[] (int u) { 
    return get(u, u + 1, 0, 0, m); 
  }

  int find_first_knowingly(const std::function<bool(const node&)>& fun, int u, int l, int r) {
    if (r - l == 1) {
      return l;
    }
    push(u, l, r);
    int mid = (l + r) >> 1, v = u << 1;
    int res;
    if (fun(tree[v + 1])) {
      res = find_first_knowingly(fun, v + 1, l, mid);
    } else {
      res = find_first_knowingly(fun, v + 2, mid, r);
    }
    pull(u);
    return res;
  }

  int find_first(int L, int R, const std::function<bool(const node&)>& fun, int u, int l, int r) {
    if (l >= R || r <= L) {
      return -1;
    }
    if (l >= L && r <= R) {
      if (!fun(tree[u])) {
        return -1;
      }
      return find_first_knowingly(fun, u, l, r);
    }
    push(u, l, r);
    int mid = (l + r) >> 1, v = u << 1;
    int res = find_first(L, R, fun, v + 1, l, mid);
    if (res == -1) {
      res = find_first(L, R, fun, v + 2, mid, r);
    }
    pull(u);
    return res;
  }

  int find_first(int L, int R, const std::function<bool(const node&)>& fun) {
    return find_first(L, R, fun, 0, 0, m);
  }

  int find_last_knowingly(const std::function<bool(const node&)>& fun, int u, int l, int r) {
    if (r - l == 1) {
      return l;
    }
    push(u, l, r);
    int mid = (l + r) >> 1, v = u << 1;
    int res;
    if (fun(tree[v + 2])) {
      res = find_last_knowingly(fun, v + 2, mid, r);
    } else {
      res = find_last_knowingly(fun, v + 1, l, mid);
    }
    pull(u);
    return res;
  }

  int find_last(int L, int R, const std::function<bool(const node&)>& fun, int u, int l, int r) {
    if (l >= R || r <= L) {
      return -1;
    }
    if (l >= L && r <= R) {
      if (!fun(tree[u])) {
        return -1;
      }
      return find_last_knowingly(fun, u, l, r);
    }
    push(u, l, r);
    int mid = (l + r) >> 1, v = u << 1;
    int res = find_last(L, R, fun, v + 2, mid, r);
    if (res == -1) {
      res = find_last(L, R, fun, v + 1, l, mid);
    }
    pull(u);
    return res;
  }

  int find_last(int L, int R, const std::function<bool(const node&)>& fun) {
    return find_last(L, R, fun, 0, 0, m);
  }
};

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  int N, Q;
  cin >> N >> Q;
  vector<long long> a(N); 
  for (int i = 0; i < N; i++) {        
    cin >> a[i];
  }
  Segtree S(N);
  S.build(a);
  for (int i = 0; i < Q; i++) {
    int t, l, r;
    cin >> t >> l >> r;
    if (t) {
      cout << S.get(l, r).val << '\n';
    } else {
      int b, c;
      cin >> b >> c;
      S.apply(l, r, make_pair(b, c));
    }
  }

  return 0;
}
