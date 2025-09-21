
template <typename T, typename U>
struct Segtree {
  int n, m;
  std::vector<T> nodes;
  std::vector<U> costs;

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
    n = (int) base.size();
    m = 1;
    while (m < n) {
      m *= 2;
    }
    nodes.assign(m * 2 - 1, T());
    costs.assign(m * 2 - 1, U());
    for (int i = 0; i < n; i++) {
      nodes[i + m - 1] = (T) base[i];
    }
    for (int i = m - 2; i >= 0; i--) {
      pull(i);
    }
  }

  void clear() {    
    std::fill(nodes.begin(), nodes.end(), T());
    std::fill(costs.begin(), costs.end(), U());
  }

  void pull(int u) {
    int v = u << 1;
    nodes[u] = nodes[v + 1] + nodes[v + 2];
  }

  void push(int u, int l, int r) {
    int mid = (l + r) >> 1, v = u << 1;
    nodes[v + 1].apply(costs[u], l, mid);
    nodes[v + 2].apply(costs[u], mid, r);
    costs[v + 1].apply(costs[u], l, mid);
    costs[v + 2].apply(costs[u], mid, r);
    costs[u] = U();
  }

  void apply(const int& L, const int& R, const U& w, int u, int l, int r) {
    if (l >= R || r <= L) {
      return;
    }
    if (l >= L && r <= R) {
      nodes[u].apply(w, l, r);
      costs[u].apply(w, l, r);
      return;
    }
    push(u, l, r);
    int mid = (l + r) >> 1, v = u << 1;
    apply(L, R, w, v + 1, l, mid);
    apply(L, R, w, v + 2, mid, r);
    pull(u);
  }

  void apply(const int& L, const int& R, const U& w) {
    apply(L, R, w, 0, 0, m); 
  }

  void apply(const int& at, const U& w) { 
    apply(at, at + 1, w, 0, 0, m); 
  }

  T get(const int& L, const int& R, int u, int l, int r) {
    if (l >= R || r <= L) {
      return T();
    }
    if (l >= L && r <= R) {
      return nodes[u];
    }
    push(u, l, r);
    int mid = (l + r) >> 1, v = u << 1;
    T res = get(L, R, v + 1, l, mid) + get(L, R, v + 2, mid, r);
    pull(u);
    return res;
  }

  T get(const int& L, const int& R) { 
    return get(L, R, 0, 0, m); 
  }

  T operator[] (const int& u) {
    return get(u, u + 1, 0, 0, m); 
  }

  int find_first_knowingly(const std::function<bool(const T&)>& fun, int u, int l, int r) {
    if (r - l == 1) {
      return l;
    }
    push(u, l, r);
    int mid = (l + r) >> 1, v = u << 1;
    int res;
    if (fun(nodes[v + 1])) {
      res = find_first_knowingly(fun, v + 1, l, mid);
    } else {
      res = find_first_knowingly(fun, v + 2, mid, r);
    }
    pull(u);
    return res;
  }

  int find_first(const int& L, const int& R, const std::function<bool(const T&)>& fun, int u, int l, int r) {
    if (l >= R || r <= L) {
      return -1;
    }
    if (l >= L && r <= R) {
      if (!fun(nodes[u])) {
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

  int find_first(const int& L, const int& R, const std::function<bool(const T&)>& fun) {
    return find_first(L, R, fun, 0, 0, m);
  }

  int find_last_knowingly(const std::function<bool(const T&)>& fun, int u, int l, int r) {
    if (r - l == 1) {
      return l;
    }
    push(u, l, r);
    int mid = (l + r) >> 1, v = u << 1;
    int res;
    if (fun(nodes[v + 2])) {
      res = find_last_knowingly(fun, v + 2, mid, r);
    } else {
      res = find_last_knowingly(fun, v + 1, l, mid);
    }
    pull(u);
    return res;
  }

  int find_last(const int& L, const int& R, const std::function<bool(const T&)>& fun, int u, int l, int r) {
    if (l >= R || r <= L) {
      return -1;
    }
    if (l >= L && r <= R) {
      if (!fun(nodes[u])) {
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

  int find_last(const int& L, const int& R, const std::function<bool(const T&)>& fun) {
    return find_last(L, R, fun, 0, 0, m);
  }
};

using namespace std;

struct Cost {
  long long add;

  Cost(long long a = 0) : add(a) {}

  void apply(const Cost& o, int l, int r) {
    add += o.add;
  }
};

struct Node {
  long long sum;

  Node(long long s = 0) : sum(s) {}

  void apply(const Cost& o, int l, int r) {
    sum += o.add * (r - l);
  }

  friend Node operator + (const Node& lhs, const Node& rhs) {
    Node res;
    res.sum = lhs.sum + rhs.sum;
    return res;
  }
};

// When applying or merging, check if value/cost is empty
// Or set to handle identity
