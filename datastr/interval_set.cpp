
#include <bits/stdc++.h>
#include "../debug.h"

template <typename T>
struct interval_set  {
  static const T def = std::numeric_limits<T>::min();
  std::map<T, T> f;

  void insert(T l, T r) {
    if (l >= r) {
      return;
    }
    auto it = f.upper_bound(l);
    if (it != f.begin()) {
      auto last = std::prev(it);
      if (last->second >= l) {
        l = last->first;
        r = std::max(r, last->second);
        it = f.erase(last);
      }
    }
    while (it != f.end() && it->first <= r) {
      r = std::max(r, it->second);
      it = f.erase(it);
    }
    f[l] = r;
  }

  void erase(const T& l, const T& r) {
    if (l >= r) {
      return;
    }
    auto it = f.upper_bound(l);
    T z = r;    
    while (it != f.end() && it->first < r) {
      z = it->second;
      it = f.erase(it);
      if (r < z) {
        break;
      }
    }
    if (it != f.begin()) {
      auto last = std::prev(it);
      T x = last->first, y = last->second;
      if (l < last->second) {
        f.erase(last);
        if (x < l) {
          f[x] = l;
        }
        if (r < y) {
          f[r] = y;
        }
      }
    }
    if (r < z) {
      f[r] = z;
    }
  }

  void invert(const T& l, const T& r) {
    if (l >= r) {
      return;
    }
    auto inter = get_intervals(l, r);
    erase(l, r);
    T beg = l;
    for (auto& [l, r] : inter) {
      if (beg < l) {
        insert(beg, l);
      }
      beg = r;
    }
    if (beg < r) {
      insert(beg, r);
    }
  }

  std::vector<std::pair<T, T>> get_intervals(const T& l, const T& r) const {
    std::vector<std::pair<T, T>> res;
    auto it = f.upper_bound(l);
    if (it != f.begin()) {
      auto last = std::prev(it);
      if (last->second > l) {
        res.emplace_back(l, std::min(last->second, r));
      }
    }
    while (it != f.end() && it->first < r) {
      res.emplace_back(it->first, std::min(it->second, r));
      it++;
    }
    return res;
  }

  void clear() {
    f.clear();
  }

  bool contains(const T& l, const T& r) const {
    auto it = f.upper_bound(l);
    if (it == f.begin()) {
      return 0;
    }
    it = std::prev(it);
    return it->first <= l && l <= r && r <= it->second;
  }

  T count() const {
    T ans = 0;
    for (const auto& [l, r] : f) {
      ans += r - l;
    }
    return ans;
  }

  T find_first_missing(const T& l, const T& r) const {
    if (l >= r) {
      return def;
    }
    auto it = f.upper_bound(l);
    if (it != f.begin()) {
      auto last = std::prev(it);
      T x = last->first, y = last->second;
      if (x <= l && l < y) {
        if (y >= r) {
          return def;
        }
        return y;
      }
    }
    return l;
  }

  T find_last_missing(const T& l, const T& r) const {
    if (l >= r) {
      return def;
    }
    auto it = f.lower_bound(r);
    if (it == f.begin()) {
      return r - 1;
    }
    it = std::prev(it);
    T a = it->first, b = it->second;
    if (b < r) {
      return r - 1;
    }
    if (l < a) {
      return a - 1;
    }
    return def;
  }
};

using namespace std;

uint64_t random_address() {
  char* foo = new char;
  delete foo;
  return uint64_t(foo);
}

mt19937 rng((unsigned) chrono::system_clock::now().time_since_epoch().count() ^ random_address());

int getRand(int l, int r) {
  std::uniform_int_distribution<int> dist(l, r);
  return dist(rng);
}

long long getRand(long long l, long long r) {
  uniform_int_distribution<long long> dist(l, r);
  return dist(rng);
}

double getRand(double l, double r) {
  uniform_real_distribution<double> dist(l, r);
  return dist(rng);
}

void edge_test() {
  debug("Running Edge Tests");
  interval_set<int> S;

  // touching intervals
  S.insert(0, 5);
  S.insert(5, 10);
  assert(S.find_first_missing(0, 10) == S.def);
  assert(S.contains(0, 10));
  debug(S.f);

  // split intervals
  S.erase(3, 7);
  assert(!S.contains(3, 7));
  assert(S.find_first_missing(0, 10) == 3);
  debug(S.f);

  // full coverage gap at end
  S.insert(3, 7);
  assert(S.find_first_missing(0, 10) == S.def);
  debug(S.f);

  // erase at boundaries
  S.erase(0, 1);
  S.erase(9, 10);
  assert(S.find_first_missing(0, 10) == 0);
  debug(S.f);

  // query empty set
  S.clear();
  assert(S.find_first_missing(0, 5) == 0);
  assert(!S.contains(0, 5));
  debug(S.f);

  // inverting intervals
  S.clear();
  S.invert(0, 5);
  assert(S.contains(0, 5));
  S.invert(0, 5);
  assert(!S.contains(0, 5));
  S.insert(0, 2);
  S.insert(4, 6);
  S.insert(8, 10);
  S.invert(1, 9);

  // verify via brute
  const int N = 12;
  vector<int> present(N);
  present[0] = present[1] = 1;
  present[4] = present[5] = 1;
  present[8] = present[9] = 1;
  for (int i = 1; i < 9; i++) {
    present[i] ^= 1;
  }

  map<int, int> current;
  for (int i = 0; i < N; i++) {
    if (present[i]) {
      int j = i;
      while (i + 1 < N && present[i + 1]) {
        i += 1;
      }
      current[j] = i + 1;
    }
  }
  if (current != S.f) {
    debug("++++++++++FAIL++++++++++");
    debug(current);
    debug(S.f);
    debug("EDGE: MISMATCHED INTERVAL SET");
    debug("++++++++++FAIL++++++++++");
    assert(0);
  }

  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      int fm = S.def, lm = S.def;
      for (int k = i; k < j; k++) {
        if (!present[k]) { 
          fm = k;
          break; 
        }
      }
      for (int k = j - 1; k >= i; k--) {
        if (!present[k]) { 
          lm = k; 
          break; 
        }
      }
      bool contains_res = S.contains(i, j);
      int fm_res = S.find_first_missing(i, j);
      int lm_res = S.find_last_missing(i, j);
      if ((fm == S.def) != contains_res) {
        debug("++++++++++FAIL++++++++++");
        debug(current);
        debug(S.f);
        debug("EDGE: CONTAINS MISMATCH");
        debug(i, j, fm, contains_res);
        debug("++++++++++FAIL++++++++++");
        assert(0);
      }
      if (fm != fm_res) {
        debug("++++++++++FAIL++++++++++");
        debug(current);
        debug(S.f);
        debug("EDGE: FIND_FIRST_MISSING MISMATCH");
        debug(i, j, fm, fm_res);
        debug("++++++++++FAIL++++++++++");
        assert(0);
      }
      if (lm != lm_res) {
        debug("++++++++++FAIL++++++++++");
        debug(current);
        debug(S.f);
        debug("EDGE: FIND_LAST_MISSING MISMATCH");
        debug(i, j, lm, lm_res);
        debug("++++++++++FAIL++++++++++");
        assert(0);
      }
    }
  }

  debug("All edge cases passed...");
  debug();
}

void random_test() {
  debug("Running Random Tests");
  const int N = 500, tt = 1e6;

  interval_set<long long> S;
  vector<char> present(N, 0);
  map<long long, long long> current;

  int inserts = 0, erases = 0, inverts = 0;
  int contains = 0, first_missing = 0, last_missing = 0;

  for (int tc = 0; tc < tt; tc++) {
    if (tc > 0 && tc % int(5e4) == 0) {
      debug(tc, inserts, erases, inverts);
    }
    int op = getRand(0, 3);
    int a = getRand(0, N - 1);
    int b = getRand(0, N - 1);
    int L = min(a, b);
    int R = max(a, b) + 1;

    if (op == 1) {
      S.insert(L, R);
      for (int i = L; i < R; i++) {
        present[i] = 1;
      }
      inserts++;
    }
    if (op == 2) {
      S.erase(L, R);
      for (int i = L; i < R; i++) {
        present[i] = 0;
      }
      erases++;
    }    
    if (op == 3) {
      S.invert(L, R);
      for (int i = L; i < R; i++) {
        present[i] ^= 1;
      }
      inverts++;
    }
    
    if (op) {
      long long last_end = S.def;
      for (auto [l, r] : S.f) {
        if (l >= r || last_end > l) {
          debug("++++++++++FAIL++++++++++");
          debug(S.f);
          debug("INVALID INTERVAL FOUND IN SET");
          debug(last_end, l, r);
          debug("++++++++++FAIL++++++++++");
          assert(0);          
        }
        last_end = r;
      }
      current.clear();
      for (int i = 0; i < N; i++) {
        if (present[i]) {
          int j = i;
          while (i + 1 < N && present[i + 1]) {
            i += 1;
          }
          current[j] = i + 1;
        }
      }
    }
    if (current != S.f) {
      debug("++++++++++FAIL++++++++++");
      debug(current);
      debug(S.f);
      debug("MISMATCHED INTERVAL SET");
      debug("++++++++++FAIL++++++++++");
      assert(0);
    }

    for (int t = 0; t < 2; t++) {
      {
        bool brute = 1;
        for (int i = L; i < R; i++) {
          if (!present[i]) {
            brute = 0;
            break;
          }
        }
        bool mine = S.contains(L, R);
        if (brute != mine) {
          debug("++++++++++FAIL++++++++++");
          debug(current);
          debug(S.f);
          debug("CONTAINS MISMATCH");
          debug(L, R);
          debug(brute, mine);
          debug("++++++++++FAIL++++++++++");
          assert(0);
        }
        contains++;
      }
      {
        long long brute = S.def;
        for (int i = L; i < R; i++) {
          if (!present[i]) {
            brute = i;
            break;
          }
        }
        long long mine = S.find_first_missing(L, R);
        if (brute != mine) {
          debug("++++++++++FAIL++++++++++");
          debug(current);
          debug(S.f);
          debug("FIND_FIRST_MISSING MISMATCH");
          debug(L, R);
          debug(brute, mine);
          debug("++++++++++FAIL++++++++++");
          assert(0);
        }
        first_missing++;
      }
      {
        long long brute = S.def;
        for (int i = R - 1; i >= L; i--) {
          if (!present[i]) {
            brute = i;
            break;
          }
        }
        long long mine = S.find_last_missing(L, R);
        if (brute != mine) {
          debug("++++++++++FAIL++++++++++");
          debug(current);
          debug(S.f);
          debug("FIND_LAST_MISSING MISMATCH");
          debug(L, R);
          debug(brute, mine);
          debug("++++++++++FAIL++++++++++");
          assert(0);
        }
        last_missing++;
      }
      a = getRand(0, N - 1);
      b = getRand(0, N - 1);
      L = min(a, b);
      R = max(a, b) + 1;
    }
  }

  debug(tt, inserts, erases, inverts);
  debug("All tests passed...");
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  edge_test();
  random_test();

  return 0;
}
