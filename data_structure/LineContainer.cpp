    
/** 
 * Copied & Modified from KACTL library
 * Author      : Simon Lindholm
 * Date        : 2017-04-20
 * License     : CC0
 * Source      : own work
 * Description : Container where you can add lines of the form kx+m, and query maximum values at points x.
                 Useful for Optimizing DP (also known as, ''convex hull trick'').
 * Time        : O(\log N)
 * Status      : stress-tested
**/

#include <set>
#include <cassert>
#include <iostream>

inline long long floor_div(long long a, long long b) {
  return a / b - ((a ^ b) < 0 && a % b != 0); 
}                         

struct Line {
  mutable long long k, m, p;
  bool operator < (const Line& o) const {
    return k < o.k;
  }
  bool operator < (long long x) const { 
    return p < x; 
  }
};

/*
      for doubles, 
      use inf = 1/.0 and div(a, b) = a / b
*/
struct LineContainer : std::multiset<Line, std::less<>> {
  static const long long inf = 8e18;       
  bool isect(iterator x, iterator y) {
    if (y == end()) {
      x->p = inf;
      return 0;
    }
    if (x->k == y->k) {
      x->p = (x->m > y->m ? inf : -inf);
    }
    else {
      x->p = floor_div(y->m - x->m, x->k - y->k);
    }
    return x->p >= y->p;
  }
  void add(long long k, long long m) {
    auto z = emplace(k, m, 0);
    auto x = z, y = z++;       
    while (isect(y, z)) {
      z = erase(z);
    }
    if (x != begin() && isect(--x, y)) {
      isect(x, y = erase(y));
    }
    while ((y = x) != begin() && (--x)->p >= y->p) {
      isect(x, erase(y));
    }
  }
  long long query(long long x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
};

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  return 0;
}

