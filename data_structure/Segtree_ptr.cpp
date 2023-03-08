  
#include <vector>
#include <cassert>  
#include <iostream>  

const long long P = 998244353;
                               
struct Segtree {       
  int low, high;
  Segtree *lhs, *rhs;
                      
  using T = long long;
  using U = std::pair<long long, long long>;
     
  static constexpr T def_value = 0;
  static constexpr U def_save = std::make_pair(1, 0);

  T value; U save;                 

  static T unite(T u, T v) {
    return (u + v) % P;
  }

  void add(U cost) {
    value *= cost.first;
    value %= P;
    value += cost.second * (high - low);
    value %= P;

    save.first *= cost.first;
    save.first %= P;
    save.second *= cost.first;
    save.second += cost.second;
    save.second %= P;
  }     

  Segtree(int low, int high) : low(low), high(high) {
    int mid = (low + high) >> 1;
    value = def_value;
    save = def_save;
    if (low + 1 < high) {
      lhs = new Segtree(low, mid);
      rhs = new Segtree(mid, high);
    } else {
      lhs = nullptr;
      rhs = nullptr;
    }
  }

  ~Segtree() {
    if (low + 1 < high) {
      delete lhs;
      delete rhs;
    }
  }

  inline void push() {
    if (save != def_save) {
      if (low + 1 < high) {                                 
        lhs->add(save);
        rhs->add(save);
      }  
      save = def_save;
    }
  }

  void apply(int x, int y, U v) {
    if (x >= y) {
      return;
    }
    if (low >= x && high <= y) {
      add(v);
      return;
    }
    push();
    int mid = (low + high) >> 1;
    if (x < mid) {
      lhs->apply(x, std::min(y, mid), v);
    }
    if (mid < y) {
      rhs->apply(std::max(x, mid), y, v);
    }
    value = unite(lhs->value, rhs->value);
  }

  T get(int x, int y) {
    if (x >= y) {
      return def_value;
    }                                                                   
    if (low >= x && high <= y) { 
      return value;
    }
    push();
    int mid = (low + high) >> 1;
    T res = def_value;
    if (x < mid) {
      res = unite(lhs->get(x, std::min(y, mid)), res);
    }
    if (mid < y) {
      res = unite(res, rhs->get(std::max(x, mid), y));
    }
    value = unite(lhs->value, rhs->value);
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
