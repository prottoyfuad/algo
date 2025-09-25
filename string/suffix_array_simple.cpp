
/// brute - O(n.logn.logn)
vector<int> suffix_array_brute(string& s) {
  s += '$';
  int n = (int) s.length();
  vector<int> order(n), cost(n);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int i, int j) {
    return s[i] < s[j];
  });
  for (int i = 1; i < n; i++) {
    int u = order[i - 1], v = order[i];
    cost[v] = cost[u] + (s[u] != s[v]);
  }
  for (int x = 1; x < n; x <<= 1) {
    vector<pair<int, int>> segment(n);
    for (int i = 0; i < n; i++) {
      segment[i] = {cost[i], cost[(i + x) % n]};
    }
    sort(order.begin(), order.end(), [&](int i, int j) {
      return segment[i] < segment[j];
    });
    cost[order[0]] = 0;
    for (int i = 1; i < n; i++) {
      int u = order[i - 1], v = order[i];
      cost[v] = cost[u] + (segment[u] != segment[v]);
    }
  }
  s.pop_back();
  return order;
}

/// O(n.logn) < default with 2 times radix sort;
vector<int> suffix_array_simple(const string& s) {
  int n = s.length() + 1;
  vector<int> order(n), rank(n);
  iota(order.begin(), order.end(), 0);
  for (int i = 0; i < n - 1; i++) {
    rank[i] = s[i];
  }
  auto radix = [&] (int k) {
    int m = max(n, 256);
    vector<int> c(m + 1);
    for (int e : rank) c[e + 1]++;
    for (int i = 0; i < m; i++) {
      c[i + 1] += c[i];
    }
    vector<int> next_order(n);
    for (int i : order) {
      int j = c[rank[(i + k) % n]]++;
      next_order[j] = i;
    }
    swap(order, next_order);
  };
  for (int k = 1; k < n; k <<= 1) {
    radix(k);
    radix(0);
    vector<int> next_rank(n);
    int delta = 0;     
    for (int i = 1; i < n; i++) {
      delta += rank[order[i]] != rank[order[i - 1]] || rank[(order[i] + k) % n] != rank[(order[i - 1] + k) % n];
      next_rank[order[i]] = delta;
    }
    swap(rank, next_rank);
  }
  return order;
}
