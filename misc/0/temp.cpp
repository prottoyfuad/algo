
// #pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math,inline")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,lzcnt,mmx,abm,avx,avx2")

#include <bits/stdc++.h>

/// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun> class y_combinator_result {
  Fun fun_;
public:
  template<class T> explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
  template<class ...Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...); }
};
template<class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }

struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    /// http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator() (uint64_t x) const {
    static const uint64_t seed = std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + seed);
  }
};

template <typename U, typename T> using hash_map = std::unordered_map<U, T, custom_hash>;
/*  
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;

template <typename T>
using Ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
template <typename U, typename T> using gp_hash_map = __gnu_pbds::gp_hash_table<U, T, custom_hash>;
*/

#ifdef LOCAL
#include "../algo/lib/debug.hpp"
#else
#define debug(...) 42
#endif

template <unsigned L = 0> struct Timer {
  using i64 = long long;
  static i64 clock_now() { return std::chrono::steady_clock::now().time_since_epoch().count(); }
  i64 start;
  Timer() { start = clock_now(); }
  double time() { return (clock_now() - start) / 1e6; }
#ifdef LOCAL
  ~Timer() { std::cerr << L << ".Time elapsed: " << std::fixed << std::setprecision(4) << time() << " ms!" << std::endl; }
#endif
};

template <typename T>
void vector_out(const std::vector<T>& v, int add = 0, int head = 0, int tail = 0x7fffffff) {
  tail = std::min(tail, (int)v.size());
  for(int i = head; i < tail; i++) {
    if(i > head) std::cout << ' ';
    std::cout << static_cast<T>(v[i] + add);
  }
  std::cout << '\n';
}

template <typename T> using Min_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template <typename T> inline bool Min(T& a, const T& b) { if(b < a) return a = b, 1; return 0; }
template <typename T> inline bool Max(T& a, const T& b) { if(a < b) return a = b, 1; return 0; }

uint64_t random_address() {
  char* foo = new char;
  delete foo;
  return uint64_t(foo);
}
std::mt19937_64 rng((uint64_t) std::chrono::steady_clock::now().time_since_epoch().count() ^ random_address());

long long myRand(long long B) {
	return (uint64_t) rng() % B;
}

long long floor_div(long long x, long long y) {
	assert(y != 0);
	if (y < 0) {
		y = -y;
		x = -x;
	}
	if (x >= 0) {
    return x / y;
  }
	return (x + 1) / y - 1;
}

long long ceil_div(long long x, long long y) {
	assert(y != 0);
	if (y < 0) {
		y = -y;
		x = -x;
	}
	if (x <= 0) {
    return x / y;
  }
	return (x - 1) / y + 1;
}

using namespace std;

void solve(int tt = 1) {

}

int main() {
  solve();
  return 0;
}
 
