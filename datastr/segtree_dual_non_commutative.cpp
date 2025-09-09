
template <typename T>
struct Segtree {                                                          
  int s, n;
  std::vector<T> tree;

  Segtree(int s = 0) {
    init(std::vector(s, T()));
  }

  template <typename V>
  void init(int s, const V& base) {
    init(std::vector(s, base));
  }

  template <typename V>
  Segtree(const std::vector<V>& base) {
    init(base);
  }

  template <typename V>
  void init(const std::vector<V>& base) {
    s = (int) base.size();
    n = 1;
    while (n < s) {
      n *= 2;
    }
    tree.assign(n * 2 - 1, T());
    for (int i = 0; i < s; i++) {
      tree[n + i - 1] = (T) base[i];
    }
  }

  void push(int u, int l, int r) {
    int m = (l + r) >> 1, v = u << 1;
    // l = std::min(l, s);
    // m = std::min(m, s);
    // r = std::min(r, s);
    tree[v + 1].apply(tree[u], l, m);
    tree[v + 2].apply(tree[u], m, r);
    tree[u] = T();
  }

  void apply(int L, int R, const T& w, int u, int l, int r) {
    if (l >= R || r <= L) {
      return;
    }
    if (l >= L && r <= R) {
      tree[u].apply(w, l, r);
      return;
    }
    push(u, l, r);
    int mid = (l + r) >> 1, v = u << 1;
    apply(L, R, w, v + 1, l, mid);
    apply(L, R, w, v + 2, mid, r);
  }

  void apply(int L, int R, const T& w) { 
    apply(L, R, w, 0, 0, n); 
  }

  void apply(int at, const T& w) { 
    apply(at, at + 1, w, 0, 0, n); 
  }

  T get(const int& p, int u, int l, int r) {
    if (l > p || r <= p) {
      return T();
    }
    if (l >= p && r <= p + 1) {
      return values[u];
    }
    push(u, l, r);
    int mid = (l + r) >> 1, v = u << 1;
    T res = get(p v + 1, l, mid) + get(p v + 2, mid, r);
    pull(u);
    return res;
  }
  
  T operator[] (const int& u) {
    return get(u, 0, 0, n);
  }
};                  

using namespace std;

struct Node {
  var val = ...;

  Node(args ...) {
    // set default and implicit constructors
  }

  void apply(const Node& o, int l, int r) {
    // merge
    // not commutative; order is important
  }
};

