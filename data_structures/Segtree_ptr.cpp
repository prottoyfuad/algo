  
#include <vector>
#include <cassert>  
#include <iostream>  

const long long P = 998244353;
                               
struct Segtree {       
  int low, high, mid;
  Segtree *l, *r;
                      
  using T = long long;
  using U = std::pair<long long, long long>;
     
  static constexpr T def_value = 0;
  static constexpr U def_save = std::make_pair(1, 0);

  T value; U save;                 

  static T unite(T u, T v) {
    return (u + v) % P;
  }

  void add_cost(U cost) {
    save.first *= cost.first;
    save.first %= P;
    save.second *= cost.first;
    save.second += cost.second;
    save.second %= P;
  }

  void mapping(U cost) {
    value *= cost.first;
    value %= P;
    value += cost.second * (high - low);
    value %= P;
  }     

  Segtree(int low, int high) : low(low), high(high) {
    mid = (low + high) / 2;
    value = def_value;
    save = def_save;
    if (low + 1 == high) {
      l = nullptr;
      r = nullptr;
    } else {
      l = new Segtree(low, mid);
      r = new Segtree(mid, high);
    }
  }

  ~Segtree() {
    if (low + 1 < high) {
      delete l;
      delete r;
    }
  }

  inline void push() {
    if (save != def_save && low + 1 < high) {                                 
      l->mapping(save);
      l->add_cost(save);
      r->mapping(save);
      r->add_cost(save);  
      save = def_save;
    }
  }

  void apply(int x, int y, U v) {
    if (low >= x && high <= y) {
      mapping(v); 
      add_cost(v);
      return;
    }
    push();
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
    T res = def_value;
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
