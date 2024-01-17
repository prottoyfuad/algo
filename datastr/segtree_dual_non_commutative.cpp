
template <typename T> struct segtree {                                                          
  int n;
  std::vector<T> tree;

  segtree(int s = 0) : n(1) {
    while (n < s) n *= 2;
    tree.assign(n * 2 - 1, T());
  }

  template <typename U>
  segtree(const std::vector<U>& a) {
    build(a);
  }

  template <typename U>
  void build(const std::vector<U>& a) {
    int s = (int) a.size();
    n = 1;
    while (n < s) n *= 2;
    tree.assign(n * 2 - 1, T());
    for (int i = 0; i < s; i++) {
      tree[n - 1 + i] = (T) a[i];
    }
  }

  inline void push(int u, int l, int r) {
    assert(u < n - 1);
    if (tree[u].empty()) {
      return;
    }
    int mid = (l + r) >> 1;
    int v = u << 1;
    if (l < n) {
      tree[v + 1] += tree[u];                                   
    }
    if (mid < n) { 
      tree[v + 2] += tree[u];                                
    }
    tree[u].clear();
  }

  void apply(int L, int R, const T& w, int u, int l, int r) {
    if (l >= R || r <= L) {
      return;
    }
    if (l >= L && r <= R) {
      tree[u] += w;
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
  
  T operator[] (int u) {
    u += n - 1;
    T ans = tree[u];
    while (u > 0) {
      --u >>= 1;
      ans += tree[u];
    }
    return ans;
  }
};                  

using namespace std;

struct node {
  var val = ...;

  node(args ...) {
    // set default and implicit constructors
  }
  
  void clear() {
    // set vars to identity
  } 

  bool empty() const {
    // check if vars == identity
  } 

  void operator += (const node& o) {
    // merge
    // not commutative; order is important
  }
};

