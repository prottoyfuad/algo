
#include <bits/stdc++.h>
#include "../debug.h"

struct interval_set  {
  static const long long def = -1;
  std::map<long long, long long> f;

  void insert(long long l, long long r) {
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

  void erase(long long l, long long r) {
    if (l >= r) {
      return;
    }
    auto it = f.upper_bound(l);
    long long z = r;    
    while (it != f.end() && it->first < r) {      
      z = it->second;
      it = f.erase(it);
      if (r < z) {
        break;
      }
    }
    if (it != f.begin()) {
      auto last = std::prev(it);
      long long x = last->first, y = last->second;
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

  bool contains(long long l, long long r) {
    auto it = f.upper_bound(l);
    if (it == f.begin()) {
      return 0;
    }
    it = std::prev(it);
    return it->first <= l && l <= r && r <= it->second;
  }

  long long find_first_missing(long long l, long long r) {
    if (l >= r) {
      return def;
    }
    auto it = f.upper_bound(l);
    if (it != f.begin()) {
      auto last = std::prev(it);
      long long x = last->first, y = last->second;
      if (x <= l && l < y) {
        if (y >= r) {
          return def;
        }
        return y;
      }
    }
    return l;
  }

  long long count() {
    long long ans = 0;
    for (auto& [l, r] : f) {
      ans += r - l;
    }
    return ans;
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
  interval_set S;

  // touching intervals
  S.insert(0, 5);
  S.insert(5, 10); // should merge [0,10)
  assert(S.find_first_missing(0, 10) == S.def);
  assert(S.contains(0, 10));
  debug(S.f);

  // split intervals
  S.erase(3, 7); // should create [0,3) and [7,10)
  assert(!S.contains(3, 7));
  assert(S.find_first_missing(0, 10) == 3);
  debug(S.f);

  // full coverage gap at end
  S.insert(3, 7); // merge back to [0,10)
  assert(S.find_first_missing(0, 10) == S.def);
  debug(S.f);

  // erase at boundaries
  S.erase(0, 1);
  S.erase(9, 10);
  assert(S.find_first_missing(0, 10) == 0);
  debug(S.f);

  // query empty set
  interval_set empty;
  assert(empty.find_first_missing(0, 5) == 0);
  assert(!empty.contains(0, 5));
  debug(empty.f);

  debug("All edge cases passed...");
  debug();
}

void random_test() {
  debug("Running Random Tests");
  const int N = 2e3;
  const int tt = 1e6;

  interval_set S;
  vector<char> present(N, 0);
  map<long long, long long> current;
  int last_calc = -1;

  auto calculate_current = [&](int tc) {
    if (tc <= last_calc) {
      return;
    }
    last_calc = tc;
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
  };

  int inserts = 0;
  int erases = 0;
  int contains_checks = 0;
  int find_missing_checks = 0;

  for (int tc = 0; tc < tt; tc++) {
    if (tc > 0 && tc % int(5e4) == 0) {
      debug(tc, inserts, erases, contains_checks, find_missing_checks);
    }

    int a = getRand(0, N - 1);
    int b = getRand(0, N - 1);
    int L = min(a, b);
    int R = max(a, b) + 1;
    int op = getRand(0, 3);

    if (op == 0) {
      S.insert(L, R);
      for (int i = L; i < R; i++) {
        present[i] = 1;
      }
      inserts++;
    }

    if (op == 1) {
      S.erase(L, R);
      for (int i = L; i < R; i++) {
        present[i] = 0;
      }
      erases++;
    }

    if (op == 2) {
      int c = getRand(0, N - 1);
      int d = getRand(0, N - 1);
      int ql = min(c, d);
      int qr = max(c ,d) + 1;
      bool brute = 1;
      for (int i = ql; i < qr; i++) {
        if (!present[i]) {
          brute = 0;
          break;
        }
      }
      bool mine = S.contains(ql, qr);
      if (brute != mine) {
        debug("++++++++++FAIL++++++++++");
        calculate_current(tc);
        debug(current);
        debug(S.f);
        debug("CONTAINS MISMATCH");
        debug(ql, qr);
        debug(brute, mine);
        debug("++++++++++FAIL++++++++++");
        assert(0);
      }
      contains_checks++;
    }

    if (op == 3) {
      int c = getRand(0, N - 1);
      int d = getRand(0, N - 1);
      int ql = min(c, d);
      int qr = max(c ,d) + 1;
      long long brute = S.def;
      for (int i = ql; i < qr; i++) {
        if (!present[i]) {
          brute = i;
          break;
        }
      }
      long long mine = S.find_first_missing(ql, qr);
      if (brute != mine) {
        debug("++++++++++FAIL++++++++++");
        calculate_current(tc);
        debug(current);
        debug(S.f);
        debug("FIND_FIRST_MISSING MISMATCH");
        debug(ql, qr);
        debug(brute, mine);
        debug("++++++++++FAIL++++++++++");
        assert(0);
      }
      find_missing_checks++;
    }

    calculate_current(tc);
    if (current != S.f) {
      debug("++++++++++FAIL++++++++++");
      debug(current);
      debug(S.f);
      debug("MISMATCHED INTERVAL SET");
      debug("++++++++++FAIL++++++++++");
      assert(0);
    }
  }

  debug(tt, inserts, erases, contains_checks, find_missing_checks);
  debug("All tests passed...");
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  edge_test();
  random_test();

  return 0;
}
