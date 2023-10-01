  
#include <vector>
#include <cassert>  
#include <iostream>  
#include <functional>

struct cost_t {
  // TODO args...

  cost_t() {
    clear();
  }

  cost_t(args...) {
    // TODO
  }
  
  // must be set to identity
  void clear() {
    // TODO
  } 
  // necessary when identity value can not be determined
  bool empty() const {
    // TODO
  } 
  void operator += (const cost_t& cost) {
    // TODO
  }
};
                              
struct value_t {
  // TODO args...
                            
  value_t() {
    clear();
  }
                            
  value_t(args...) {
    // TODO
  }

  // must be set to identity
  void clear() {
    // TODO
  }

  // necessary when identity value can not be determined
  bool empty() const {      
    // TODO
  }                              

  void operator += (const cost_t& cost) {
    if (cost.empty()) {
      return;
    }                   
    // TODO
  }

  friend value_t operator+ (const value_t& lhs, const value_t& rhs) {
    if (rhs.empty()) {
      return lhs;
    }
    if (lhs.empty()) {
      return rhs;
    }
    value_t res;
    // TODO merge `lhs` and `rhs` to calculate result
    return res;
  }
};         
 
struct Segtree {                                                          
  int m, n;
  std::vector<value_t> values;
  std::vector<cost_t> costs;

  Segtree(int s = 0) : m(1), n(s) {
    while (m < n) m *= 2;                
    values = std::vector<value_t> (m * 2 - 1);
    costs = std::vector<cost_t> (m * 2 - 1);
  }
                       
  template <typename T>
  void build(const std::vector<T>& a) {
    assert((int) a.size() == n);
    for (int i = 0; i < n; i++) {
      values[i + m - 1] = value_t(a[i]);
    }
    for (int i = (int) values.size() - 1; i >= n + m - 1; i--) {
      values[i] = value_t();
    }
    for (int i = m - 2; i >= 0; i--) pull(i);
  }

  inline void push(int u, int l, int r) {
    if (costs[u].empty()) {
      return;
    }
    if (u < m - 1) {
      int mid = (l + r) >> 1;
      int v = u << 1;
      if (l < n) {
        values[v + 1] += costs[u];                                   
        costs[v + 1] += costs[u];
      }
      if (mid < n) { 
        values[v + 2] += costs[u];                                
        costs[v + 2] += costs[u];
      }
    }
    costs[u].clear();
  }

  inline void pull(int u) {
    if (u < m - 1) {
      int v = u << 1;
      assert(costs[u].empty());
      values[u] = values[v + 1] + values[v + 2];
    }    
  }

  void apply(int L, int R, const cost_t& w, int u, int l, int r) {
    if (l >= R || r <= L) {
      return;
    }
    if (l >= L && r <= R) {
      values[u] += w;
      costs[u] += w;
      return;
    }
    push(u, l, r);
    int mid = (l + r) >> 1, v = u << 1;
    apply(L, R, w, v + 1, l, mid);
    apply(L, R, w, v + 2, mid, r);
    pull(u);
  }

  void apply(int L, int R, const cost_t& w) { 
    apply(L, R, w, 0, 0, m); 
  }

  void apply(int at, const cost_t& w) { 
    apply(at, at + 1, w, 0, 0, m); 
  }
  
  value_t get(int L, int R, int u, int l, int r) {
    if (l >= R || r <= L) {
      return value_t();
    }
    if (l >= L && r <= R) {
      return values[u];
    }
    push(u, l, r);
    int mid = (l + r) >> 1, v = u << 1;
    value_t res = get(L, R, v + 1, l, mid) + get(L, R, v + 2, mid, r);
    pull(u);
    return res;
  }

  value_t get(int L, int R) { 
    return get(L, R, 0, 0, m); 
  }

  value_t operator[] (int u) { 
    return get(u, u + 1, 0, 0, m); 
  }

  int find_first_knowingly(const std::function<bool(const value_t&)>& fun, int u, int l, int r) {
    if (r - l == 1) {
      return l;
    }
    push(u, l, r);
    int mid = (l + r) >> 1, v = u << 1;
    int res;
    if (fun(values[v + 1])) {
      res = find_first_knowingly(fun, v + 1, l, mid);
    } else {
      res = find_first_knowingly(fun, v + 2, mid, r);
    }
    pull(u);
    return res;
  }

  int find_first(int L, int R, const std::function<bool(const value_t&)>& fun, int u, int l, int r) {
    if (l >= R || r <= L) {
      return -1;
    }
    if (l >= L && r <= R) {
      if (!fun(values[u])) {
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

  int find_first(int L, int R, const std::function<bool(const value_t&)>& fun) {
    return find_first(L, R, fun, 0, 0, m);
  }

  int find_last_knowingly(const std::function<bool(const value_t&)>& fun, int u, int l, int r) {
    if (r - l == 1) {
      return l;
    }
    push(u, l, r);
    int mid = (l + r) >> 1, v = u << 1;
    int res;
    if (fun(values[v + 2])) {
      res = find_last_knowingly(fun, v + 2, mid, r);
    } else {
      res = find_last_knowingly(fun, v + 1, l, mid);
    }
    pull(u);
    return res;
  }

  int find_last(int L, int R, const std::function<bool(const value_t&)>& fun, int u, int l, int r) {
    if (l >= R || r <= L) {
      return -1;
    }
    if (l >= L && r <= R) {
      if (!fun(values[u])) {
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

  int find_last(int L, int R, const std::function<bool(const value_t&)>& fun) {
    return find_last(L, R, fun, 0, 0, m);
  }
};                  

using namespace std;
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  return 0;
}
  