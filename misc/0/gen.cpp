
#include <bits/stdc++.h>

#ifdef LOCAL
#include "../algo/debug.h"
#else
#define debug(...) 0
#endif

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

int main(int argc, char* argv[]) {
  // arg[0] is the command
  assert(argc == 2);

  int tc = stoi(argv[1]);
  cout << tc << '\n';

  return 0;
}
