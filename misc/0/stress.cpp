
#include <bits/stdc++.h>

#ifdef LOCAL
#include "../algo/debug.h"
#else
#define debug(...) 0
#endif

using namespace std;

uintptr_t random_address() {
  int x;
  return reinterpret_cast<uintptr_t>(&x);
}

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

const int N = 101;
const int P = 1e9 + 7;

void init() {

}

void createTest() {

}

long long brute( {
  return 0;
}

long long solve() {
  return 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  init();

  const int tt = 1e9;
  for (int tc = 0; tc <= tt; tc++) {
    if (tc % 1e5 == 0) {
      debug("test passed:", tc);
    }

    createTest();
    auto slow = brute();
    auto fast = solve();

    if (slow != fast) {
      debug("++++++++++++++++")
      debug("fail");
      debug(slow, ans);
      debug("++++++++++++++++")
      debug("Current test");
      debug("++++++++++++++++")
      return 0;
    }
    // cleanup
  }
  return 0;
}

