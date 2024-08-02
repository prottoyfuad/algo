/*
 * Range Affine Range Sum
 * https://atcoder.jp/contests/practice2/tasks/practice2_k
 * Segment tree
 * Update: L, R, B, C = for each L <= x <= R, set a[x] = a[x] * B + C
 * Query: L, R = sum in range
 */

#include <vector>
#include <cassert>  
#include <iostream>  

const long long P = 998244353;
                               
struct Segtree {       
  int low, high;
  Segtree *l, *r;
                      
  using T = long long;
  using U = std::pair<long long, long long>;
     
  static constexpr T def_value() {
    return 0ll;
  }

  static constexpr U def_weight() {
    return std::make_pair(1ll, 0ll);
  }

  T value; 
  U weight;                 

  bool has_weight() {
    return weight != def_weight();
  }
  
  void clear_weight() {
    weight = def_weight();
  }

  static T unite(T u, T v) {
    return (u + v) % P;
  }

  void add_cost(U cost) {
    weight.first *= cost.first;
    weight.first %= P;
    weight.second *= cost.first;
    weight.second += cost.second;
    weight.second %= P;
  }

  void mapping(U cost) {
    value *= cost.first;
    value %= P;
    value += cost.second * (high - low);
    value %= P;
  }     

  Segtree(int lo, int hi) : low(lo), high(hi), l(0), r(0) {
    value = def_value();
    weight = def_weight();
  }

  ~Segtree() {
    if (l) delete l;
    if (r) delete r;
  }

  inline void push() {
    if (low + 1 < high) {                                 
      int mid = (low + high) >> 1;
      if (!l) l = new Segtree(low, mid);
      if (!r) r = new Segtree(mid, high);
      if (has_weight()) {
        l->mapping(weight);
        l->add_cost(weight);
        r->mapping(weight);
        r->add_cost(weight);
        clear_weight();
      }
    }
  }

  void apply(int x, int y, U v) {
    if (low >= x && high <= y) {
      mapping(v); 
      add_cost(v);
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
    value = unite(l->value, r->value);
  }

  T get(int x, int y) {                                                                   
    if (low >= x && high <= y) { 
      return value;
    }
    push();
    int mid = (low + high) >> 1;
    T res = def_value();
    if (x < mid) {
      res = unite(l->get(x, std::min(y, mid)), res);
    }
    if (mid < y) {
      res = unite(res, r->get(std::max(x, mid), y));
    }
    value = unite(l->value, r->value);
    return res;
  }
};

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N, Q;
  cin >> N >> Q;
  Segtree S(0, N); 
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    S.apply(i, i + 1, make_pair(1, x));
  }
  for (int i = 0; i < Q; i++) {
    int t, l, r;
    cin >> t >> l >> r;
    if (t) {
      cout << S.get(l, r) << '\n';
    } else {
      int b, c;
      cin >> b >> c;
      S.apply(l, r, make_pair(b, c));
    }
  }
  return 0;
}

