
#include <bits/stdc++.h>

// tested

template <typename T> struct Fenwick {
  int n;
  std::vector<T> tree;
  Fenwick(int s = 0) : n(s), tree(s) {};
  void add(int u, T v) {
    while (u < n) {
      tree[u] += v;
      u |= u + 1;
    }
  }
  T operator[] (int u) {
    T v {};
    while (u >= 0) {
      v += tree[u];
      u = (u & (u + 1)) - 1;
    }
    return v;
  }
  int lower_bound(T v) {
    int u = 0;
    for (int p = 1 << std::__lg(n); p > 0; p /= 2) {
      if (u + p <= n && tree[u + p - 1] < v) {
        u += p;
        v -= tree[u - 1];
      }       
    }
    return u;
  }
};
// lb returns x -> sum(x - 1) < v && sum(x) >= v;

template <typename T> struct Fenwick2D {
  int n, m;
  std::vector<Fenwick<T>> tree;
  Fenwick2D(int a = 0, int b = 0) : n(a) {
    m = b ? b : n;
    tree = std::vector<Fenwick<T>> (n, Fenwick<T> (m));
  }
  void add(int u, int v, T w) {
    while (u < n) {
      tree[u].add(v, w);
      u |= u + 1;
    }
  }
  T get(int u, int v) {
    T s {};
    while (u >= 0) {
      s += tree[u][v];
      u = (u & (u + 1)) - 1;
    }
    return s;
  }
};

//~//
  
template <typename T> struct fenwick {
  int n;
  std::vector<T> data;
  fenwick() : n(0) {}
  fenwick(int n_) : n(n_), data(n_) {}
  void add(int p, T x) {
    p++;
    assert(0 < p && p <= n);
    while (p <= n) {
      data[p - 1] += T(x);
      p += p & -p;
    }
  }
  T sum(int r) {
    T s = 0;
    while (r > 0) {
      s += data[r - 1];
      r -= r & -r;
    }
    return s;
  }
  void add(int l, int r, T w) {
    assert(0 <= l && l <= r && r <= n);
    add(l, w);
    add(r, -w);
  }
  T sum(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    return sum(r) - sum(l);
  }
};

int main() {
  
  return 0;
}
