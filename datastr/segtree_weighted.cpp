
template <typename T, typename U> struct segtree {                                                          
  int m, n;
  std::vector<T> tree;
  std::vector<U> weights;

  segtree(int s = 0) : m(1), n(s) {
    while (m < n) m *= 2;                
    tree = std::vector<T> (m * 2 - 1);
    weights = std::vector<U> (m * 2 - 1);
  }
                       
  template <typename V>
  void build(const std::vector<V>& a) {
    assert((int) a.size() == n);
    for (int i = 0; i < n; i++) {
      tree[i + m - 1] = T(a[i]);
    }
    for (int i = (int) tree.size() - 1; i >= n + m - 1; i--) {
      tree[i] = T();
    }
    for (int i = m - 2; i >= 0; i--) pull(i);
  }

  inline void push(int u, int l, int r) {
    if (weights[u].empty()) {
      return;
    }
    if (u < m - 1) {
      int mid = (l + r) >> 1;
      int v = u << 1;
      if (l < n) {
        tree[v + 1] += weights[u];                                   
        weights[v + 1] += weights[u];
      }
      if (mid < n) { 
        tree[v + 2] += weights[u];                                
        weights[v + 2] += weights[u];
      }
    }
    weights[u].clear();
  }

  inline void pull(int u) {
    if (u < m - 1) {
      int v = u << 1;
      assert(weights[u].empty());
      tree[u] = tree[v + 1] + tree[v + 2];
    }    
  }

  void apply(int L, int R, const U& w, int u, int l, int r) {
    if (l >= R || r <= L) {
      return;
    }
    if (l >= L && r <= R) {
      tree[u] += w;
      weights[u] += w;
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
  
  T get(int L, int R, int u, int l, int r) {
    if (l >= R || r <= L) {
      return T();
    }
    if (l >= L && r <= R) {
      return tree[u];
    }
    push(u, l, r);
    int mid = (l + r) >> 1, v = u << 1;
    T res = get(L, R, v + 1, l, mid) + get(L, R, v + 2, mid, r);
    pull(u);
    return res;
  }

  T get(int L, int R) { 
    return get(L, R, 0, 0, m); 
  }

  T operator[] (int u) { 
    return get(u, u + 1, 0, 0, m); 
  }

  int find_first_knowingly(const std::function<bool(const T&)>& fun, int u, int l, int r) {
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

  int find_first(int L, int R, const std::function<bool(const T&)>& fun, int u, int l, int r) {
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

  int find_first(int L, int R, const std::function<bool(const T&)>& fun) {
    return find_first(L, R, fun, 0, 0, m);
  }

  int find_last_knowingly(const std::function<bool(const T&)>& fun, int u, int l, int r) {
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

  int find_last(int L, int R, const std::function<bool(const T&)>& fun, int u, int l, int r) {
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

  int find_last(int L, int R, const std::function<bool(const T&)>& fun) {
    return find_last(L, R, fun, 0, 0, m);
  }
};                  

using namespace std;
 
struct weight {
  // TODO args...

  weight() {
    clear();
  }

  weight(args...) {
    // TODO
  }
  
  void clear() {
    // TODO must be set to identity
  } 
  bool empty() const {
    // TODO necessary when identity value can not be determined
  } 
  void operator += (const weight& cost) {
    // TODO
  }
};
                              
struct node {
  // TODO args...
                            
  node() {
    clear();
  }
                            
  node(args...) {
    // TODO
  }

  void clear() {
    // TODO must be set to identity
  }

  bool empty() const {      
    // TODO necessary when identity value can not be determined
  }                              

  void operator += (const weight& cost) {
    if (cost.empty()) {
      return;
    }                   
    // TODO
  }

  friend node operator+ (const node& lhs, const node& rhs) {
    if (rhs.empty()) {
      return lhs;
    }
    if (lhs.empty()) {
      return rhs;
    }
    node res;
    // TODO merge `lhs` and `rhs` to calculate result
    return res;
  }
}; 

/*
  segtree<node, weight> S(n);
  vector<T> base(n);
  S.build(base);
*/

