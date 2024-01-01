
/** 
 * Line Container : Copied & Modified from KACTL library
 * Author         : Simon Lindholm
 * Date           : 2017-04-20
 * License        : CC0
 * Source         : own work
 * Time           : O(\log N)
 * Status         : stress-tested
 * Description    : Container where you can add lines of the form kx+m, 
 *                  and query maximum values at points x.
 *                  Useful for Optimizing DP (also known as, 'Convex Hull Trick').
**/

inline long long floor_div(long long a, long long b) {
  return a / b - ((a ^ b) < 0 && a % b != 0); 
}                         

struct line {
  mutable long long k, m, p;
  line(long long k_, long long m_, long long p_) : k(k_), m(m_), p(p_) {
  }

  bool operator < (const line& o) const {
    return k < o.k;
  }

  bool operator < (long long x) const { 
    return p < x; 
  }
};

/*
 * for doubles, 
 * use inf = 1/.0 and floor_div(a, b) = a / b
*/

struct line_container : std::multiset<line, std::less<>> {
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

  long long get(long long x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
};

