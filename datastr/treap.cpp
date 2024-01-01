                
#include <vector>
#include <chrono>
#include <random>
#include <cassert>
#include <iostream>  
#include <functional>

const int N = 5e5 + 5;

uint64_t random_address() {
  char* foo = new char;
  delete foo;
  return uint64_t(foo);
}
std::mt19937 gen((unsigned) std::chrono::system_clock::now().time_since_epoch().count() ^ random_address());
std::uniform_int_distribution<> range(0, N);

struct treap {
  treap *l, *r;
  int x, y, cnt;
  treap(int val = 0) : l(0), r(0), x(val), y(range(gen)), cnt(1) {
  }
  ~treap() {
    if (l) delete l;
    if (r) delete r;
  }
  void recalc() {
    cnt = 1;
    if (l) cnt += l->cnt;
    if (r) cnt += r->cnt;  
  }            
  static int size(treap* v) {
    return v ? v->cnt : 0;
  }
  static std::pair<treap*, treap*> split(treap* v, int k) {
    if (!v) return {};
    if (size(v->l) >= k) {
      auto p = split(v->l, k);
      v->l = p.second;
      v->recalc();
      return {p.first, v};
    }
    else {
      auto p = split(v->r, k - size(v->l) - 1);
      v->r = p.first;
      v->recalc();
      return {v, p.second};
    }
  }
  static treap* merge(treap* a, treap* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->y > b->y) {
      a->r = merge(a->r, b);
      a->recalc();
      return a;
    }
    else {
      b->l = merge(a, b->l);
      b->recalc();
      return b;
    }
  }                   
  template <class F> void dfs(const F& fun) {
    if (l) l->dfs(fun);
    fun(this);
    if (r) r->dfs(fun);
  }
};
    
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
            
  return 0;
}
  
