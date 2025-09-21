template <typename T>
struct MergeTree {
  int n;
  std::vector<std::vector<T>> tree;

  MergeTree() {}
  template <typename V>
  MergeTree(const std::vector<V>& base) {
    init(base);
  }

  template <typename V>
  void init(const std::vector<V>& base) {
    int s = base.size();
    n = 1;
    while (n < s) {
      n *= 2;
    }
    tree.assign(n * 2 - 1, {});
    for (int i = 0; i < s; i++) {
      tree[i + n - 1] = { (T) base[i] };
    }
    for (int i = n - 2; i >= 0; i--) {
      int j = i << 1;
      tree[i].resize(tree[j + 1].size() + tree[j + 2].size());
      std::merge(tree[j + 1].begin(), tree[j + 1].end(),
                 tree[j + 2].begin(), tree[j + 2].end(),
                 tree[i].begin());
    }
  }

  // count p : { p < x } in range [L, R]
  int countLess(const int& L, const int& R, const T& x, int u, int l, int r) {
    if (l >= R || r <= L) {
      return 0;
    }
    if (l >= L && r <= R) {
      return (int) (std::lower_bound(tree[u].begin(), tree[u].end(), x) - tree[u].begin());
    }
    int mid = (l + r) >> 1, v = u << 1;
    return countLess(L, R, x, v + 1, l, mid) + countLess(L, R, x, v + 2, mid, r);
  }

  int count(const int& L, const int& R, const int& x) { 
    return countLess(L, R, x, 0, 0, n); 
  }
};
