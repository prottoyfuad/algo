#include <bits/stdc++.h>

template <typename T> struct Segtree {
  int low, high, mid;
  T value, save;
  Segtree *l, *r;

  T merge(T u, T v) {
    return std::min(u, v);
  }

  Segtree(int low, int high): low(low), high(high) {
    mid = (low + high) / 2;
    save = 0;
    value = low;
    if (low == high) {
      l = r = nullptr;
      return;
    }
    l = new Segtree(low, mid);
    r = new Segtree(mid + 1, high);
  }

  void push() {
    if (!save) {
      return;
    }
    l->value += save;
    l->save += save;
    r->value += save;
    r->save += save;
    save = 0;
  }

  void apply(int x, int y, T v) {
    if (low == x && high == y) {
      value += v;
      save += v;
      return;
    }
    push();
    if (x <= mid) {
      l->apply(x, std::min(y, mid), v);
    }
    if (mid < y) {
      r->apply(std::max(x, mid + 1), y, v);
    }
    value = merge(l->value, r->value);
  }
};

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
    int n = 10;
    Segtree<int> segTree(0, n);
    
    segTree.apply(0, 5, 2);
    segTree.apply(6, n, -1);      
    
    cout << segTree.value;  

  return 0;
}
 