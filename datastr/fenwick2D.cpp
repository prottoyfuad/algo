
template <typename T> struct fenwick2d {
  std::vector<std::vector<T>> tree;
  int n, m;

  fenwick2d() {}

  fenwick2d(int _n, int _m) : n(_n), m(_m) {
    tree.resize(n);
    for (int i = 0; i < n; i++) {
      tree[i].resize(m);
    }
  }

  void modify(int i, int j, const T& w) {
    int u = i;
    while (u < n) {
      int v = j;
      while (v < m) {
        tree[u][v] += w;
        v |= (v + 1);
      }
      u |= (u + 1);
    }
  }

  T get(int i, int j) const {
    T ans {};
    int u = i;
    while (u >= 0) {
      int v = j;
      while (v >= 0) {
        ans += tree[u][v];
        v = (v & (v + 1)) - 1;
      }
      u = (u & (u + 1)) - 1;
    }
    return ans;
  }
};

struct node {
  var val = ...; // set default value

  void operator += (const node &o) {
    ...
  }
};

