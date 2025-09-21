
template <typename T, typename U>
struct Segtree {
  int low, high;
  Segtree<T, U> *l, *r;

  T node;
  U cost;

  Segtree(int lo, int hi) : low(lo), high(hi), l(0), r(0), node(T()), cost(U()) {}

  ~Segtree() {
    if (l) delete l;
    if (r) delete r;
  }

  void push() {
    if (low + 1 < high) {
      int mid = (low + high) >> 1;
      if (!l) {
        l = new Segtree(low, mid);
      }
      if (!r) {
        r = new Segtree(mid, high);
      }
      l->node.apply(cost, low, mid);
      r->node.apply(cost, mid, high);
      l->cost.apply(cost, low, mid);
      r->cost.apply(cost, mid, high);
      cost = U();
    }
  }

  void pull() {
    node = l->node + r->node;
  }

  void apply(const int& x, const int& y, const U& v) {
    if (x <= low && high <= y) {
      node.apply(v, low, high); 
      cost.apply(v, low, high);
      return;
    }
    push();
    int mid = (low + high) >> 1;
    if (x < mid) {
      l->apply(x, std::min(y, mid), v);
    }
    if (mid < y) {
      r->apply(std::max(x, mid), y, v);
    }
    pull();
  }

  T get(const int& x, const int& y) {
    if (x <= low && high <= y) {
      return node;
    }
    push();
    int mid = (low + high) >> 1;
    T res = T();
    if (x < mid) {
      res = unite(l->get(x, std::min(y, mid)), res);
    }
    if (mid < y) {
      res = unite(res, r->get(std::max(x, mid), y));
    }
    pull();
    return res;
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

// When applying or merging, check if node/cost is empty
// Or set to handle identity

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int N;
  Segtree<Node, Cost> S(0, N); 

  S.apply(l, r, Cost());
  Node node = S.get(l, r);

  return 0;
}
