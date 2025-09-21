
template <typename T>
struct Segtree {
  int n;
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
    int s = (int) base.size();
    n = 1;
    while (n < s) {
      n *= 2;
    }
    tree.assign(n * 2 - 1, T());
    for (int i = 0; i < s; i++) {
      tree[n + i - 1] = (T) base[i];
    }
  }
  
  void apply(const int& L, const int& R, const T& w, int u, int l, int r) {
    if (l >= R || r <= L) {
      return;
    }
    if (l >= L && r <= R) {
      tree[u] += w;
      return;
    }
    int mid = (l + r) >> 1, v = u << 1;
    apply(L, R, w, v + 1, l, mid);
    apply(L, R, w, v + 2, mid, r);
  }

  void apply(const int& L, const int& R, const T& w) { 
    apply(L, R, w, 0, 0, n); 
  }

  void apply(const int& at, const T& w) { 
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

struct Node {
  var val = ...;

  Node(args ...) {
    // default and implicit constructors
  }

  void operator += (const Node& o) {
    // merge
    // commutative; order doesn't matter
  }
};
