
#include <vector>
#include <numeric>
#include <iostream>
#include <functional>

using namespace std;

template <typename T, typename Fun = function<T(const T&, const T&)>>
class SparseTable {
 private:
  int n, m;
  vector<vector<T>> v;
  Fun fun;
 public:
  SparseTable() : n(), m() {}
  SparseTable(const vector<T>& a, const Fun& f) : fun(f) {
    n = static_cast<int> (a.size());
    m = 32 - __builtin_clz(n);
    v.resize(m);
    v[0] = a;
    for(int x = 1; x < m; x++) {
      int k = (n - (1 << x) + 1);
      v[x].resize(k);
      for(int i = 0; i < k; i++) {
        v[x][i] = fun(v[x - 1][i], v[x - 1][i + (1 << (x - 1))]);
      }
    }
  }
  inline T get(int l, int r) const {
    int d = r - l + 1;
    int x = 32 - __builtin_clz(d) - 1;
    return fun(v[x][l], v[x][r - (1 << x) + 1]);
  }
};

class suffix_array {
 public:
  vector<int> order, rank, lcp;
  
  suffix_array() : n() {}
  suffix_array(const string& _s) : s(_s) {
    n = s.length() + 1;
    build();
    calculate_lcp();
    rmq = SparseTable<int> (lcp, [](int a, int b) { return min(a, b); });
  }
  
  int get_lcp(int l, int r) const {
    if (max(l, r) >= n - 1) return 0;
    if (l == r) return n - l - 1;
    int a = rank[l], b = rank[r];
    return get_lcp_from_ranks(a, b);
  }
  
  int get_lcp_from_ranks(int a, int b) const {  
    if (a == b) return n - order[a] - 1;
    if (a > b) swap(a, b);
    return rmq.get(a + 1, b);
  }
  
  int compare_substr(int a, int b, int len = -1) const {
    if (len < 0) len = n - 1;
    if (a == b) return 0;
    int c = get_lcp(a, b);
    if (c >= len) return 0;
    if (a + c >= n - 1) return -1;
    if (b + c >= n - 1) return 1;
    return s[a + c] < s[b + c] ? -1 : (s[a + c] != s[b + c]);
  }
  
  int compare_substr(int a, int lena, int b, int lenb) const {
    int ret = compare_substr(a, b, min(lena, lenb));
    if (lena == lenb || ret) return ret;
    return lena < lenb ? -1 : 1;
  }
/* 
  int compare_substr(int a, int lena, int b, int lenb) const {
    int ret = compare_substr(a, b, min(lena, lenb));
    if (ret) return ret;
    if (lena == lenb) return a < b ? -1 : 1;
    return lena < lenb ? -1 : 1;
  }
*/    
 private:
  int n;
  string s;
  SparseTable<int> rmq;
  
  void build() {
    order.assign(n, 0), rank.assign(n, 0);
    iota(order.begin(), order.end(), 0);
    for (int i = 0; i < n - 1; i++) rank[i] = s[i];
    int m = max(n, 256);
    
    auto radix = [&]() {
      vector<int> c(m + 1);
      for (int e : rank) c[e + 1]++;
      for (int i = 0; i < m; i++) c[i + 1] += c[i];
      
      vector<int> next_order(n);
      for (int i : order) {
        int j = c[rank[i]]++;
        next_order[j] = i;
      }
      swap(order, next_order);
    };
    radix();
    
    for (int k = 1; k < n; k <<= 1) {
      for (int i = 0; i < n; i++) {
        order[i] -= k;
        if (order[i] < 0) order[i] += n;
      }
      radix();
      vector<int> next_rank(n);
      int delta = 0;    
      for (int i = 1; i < n; i++) {
        delta += rank[order[i]] != rank[order[i - 1]] || rank[(order[i] + k) % n] != rank[(order[i - 1] + k) % n];
        next_rank[order[i]] = delta;
      }
      swap(rank, next_rank);
    }
  }
  
  void calculate_lcp() {
    lcp.assign(n, 0);
    int prefix = 0;
       
    for (int i = 0; i < n; i++) {
      if (!rank[i]) continue;      
      int a = order[rank[i]] + prefix;
      int b = order[rank[i] - 1] + prefix;
      
      while (s[a] == s[b]) prefix++, a++, b++;
      lcp[rank[i]] = prefix;
      prefix = max(prefix - 1, 0);
    }
  }
};

string get_lcs(const string& s, const string& t) {
  int x = s.length(), y = t.length();
  suffix_array sa(s + '#' + t);
  
  auto partition = [&](int k) {
    return k >= x + 1;
  };
  int ans = 0, pos;
  
  for (int i = 0; i < x + y + 1; i++) {
    int u = sa.order[i], v = sa.order[i + 1];
    if (partition(u) == partition(v)) continue;
    
    if (u > v) swap(u, v);
    v -= x + 1;
    int len = min(x - u, y - v);
    int cur = min(sa.lcp[i + 1], len);
    
    if (cur > ans) ans = cur, pos = v;
  }
  string ret;
  if (ans) ret = t.substr(pos, ans);
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string s;

  return 0;
}
