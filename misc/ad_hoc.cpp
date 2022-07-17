// #pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math,inline")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,lzcnt,mmx,abm,avx,avx2")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

// using nsmespace __gnu_cxx;
// using namespace __gnu_pbds;

const std::vector<std::pair<int, int>> moves = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
  
const std::vector<std::pair<int, int>> moves4 =
  {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

const std::array<int, 8> dx = {1, 1, 0, -1, -1, -1, 0, 1};
const std::array<int, 8> dy = {0, 1, 1, 1, 0, -1, -1, -1}; // increment(pi / 8)

// const array<int, 8> dx = {1, 0, -1, 0, 1, -1, -1, 1};
// const array<int, 8> dy = {0, 1, 0, -1, 1, 1, -1, -1}; // increment(pi / 4)

template <typename T>
using Ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

template <typename T>
using Min_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template <typename T>
inline bool Min(T& a, const T& b) { if(b < a) return a = b, 1; return 0; }
template <typename T>
inline bool Max(T& a, const T& b) { if(a < b) return a = b, 1; return 0; }

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

const int mod = 1e9 + 7;

auto random_address = []() -> uint64_t {
  char* foo = new char; delete foo;
  return uint64_t(foo);
};
std::mt19937 rng((unsigned)random_address());

void prefix_2D() {
  using namespace std;
  int n, m;
  cin >> n >> m;
  vector a(n, vector<int> (m));
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < m; j++) {
      a[i][j] = s[j] - 48;
    }
  }
  vector pre(n + 1, vector<int> (m + 1));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      pre[i + 1][j + 1] = a[i][j];
      pre[i + 1][j + 1] += pre[i][j + 1] + pre[i + 1][j];
      pre[i + 1][j + 1] -= pre[i][j];
    }
  }
  auto get_ones = [&](int u, int v, int x, int y) {
    assert(x >= u && y >= v);
    return pre[x + 1][y + 1] - pre[u][y + 1] - pre[x + 1][v] + pre[u][v];
  };
  auto total_cells = [&](int u, int v, int x, int y) {
    assert(x >= u && y >= v);
    return (x - u + 1) * (y - v + 1);
  };
  auto get_zeroes = [&](int u, int v, int x, int y) {
    assert(x >= u && y >= v);
    return total_cells(u, v, x, y) - get_ones(u, v, x, y);
  };
  int q;
  cin >> q;
  while (q--) {
    // do something
    // like how many ones/zeroes in a rectangualar-submatrix
  }
}

template <typename T, typename U>
inline T power(T a, U p, T md = std::numeric_limits<T>::max()) {
  assert(p >= 0);
  if(a >= md) a %= md;
  T r = 1;
  while(p > 0) {
    if(p & 1) {
      r *= a;
      if(r >= md) r %= md;
    }
    a *= a;
    if(a >= md) a %= md;
    p >>= 1;
  }
  return r;
}

template <typename T, typename U>
T modular_mul(T a, U b) {
  T ans = 0;
  a %= mod;
  while(b > 0) {
    if(b & 1) ans = (ans + a) % mod;
    a = (a << 1) % mod;
    b >>= 1;
  }
  return ans % mod;
}

int ext_euclid(int a, int b, int& x, int& y) {
  x = 1, y = 0;
  int u = 0, v = 1;
  while (b) {
    int q = a / b;
    x -= q * u; std::swap(x, u);
    y -= q * v; std::swap(y, v);
    a -= q * b; std::swap(a, b);
  }
  return a; // a is gcd(originalA, originalB);
}
// linear diophantile eqn's solution exist iff gcd(a, b) | c;
// one solution is {x_ans, y_ans} = {x * c / g, y * c / g} ^^[ext-euclid]
// and we can derive the func to find modular inverse from this-
// !ahsan0045
int modinv(int a, int m) {
  int x, y;
  ext_euclid(a, m, x, y);
  if (x <= -m || x >= m) x %= m;
  if (x < 0) x += m;
  return x;
}
// ahsan0045
// a better way :
template <typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T q = m / a;
    m -= q * a; std::swap(a, m);
    u -= q * v; std::swap(u, v);
  }
  assert(m == 1);
  return u; // this needs normalization (using typename T = Modular is fine)
}

int main() {
  using namespace std;
  ios::sync_with_stdio(false), cin.tie(nullptr);
  #ifdef _hogwarts
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
  #endif

  cout << "hello\n";
  return 0;
}
