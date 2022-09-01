
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

/// brute - O(n.logn.logn)
vector<int> suffix_array_brute(string& s) {
  s += '$';
  int n = (int) s.length();
  vector<int> order(n), cost(n);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int i, int j) {
    return s[i] < s[j];
  });
  for (int i = 1; i < n; i++) {
    int u = order[i - 1], v = order[i];
    cost[v] = cost[u] + (s[u] != s[v]);
  }
  for (int x = 1; x < n; x <<= 1) {
    vector<pair<int, int>> segment(n);
    for (int i = 0; i < n; i++) {
      segment[i] = {cost[i], cost[(i + x) % n]};
    }
    sort(order.begin(), order.end(), [&](int i, int j) {
      return segment[i] < segment[j];
    });
    cost[order[0]] = 0;
    for (int i = 1; i < n; i++) {
      int u = order[i - 1], v = order[i];
      cost[v] = cost[u] + (segment[u] != segment[v]);
    }
  }
  s.pop_back();
  return order;
}

/// O(n.logn) < default with 2 times radix sort;
vector<int> suffix_array(const string& s) {
  int n = s.length() + 1;
  vector<int> order(n), rank(n);
  iota(order.begin(), order.end(), 0);
  for (int i = 0; i < n - 1; i++) {
    rank[i] = s[i];
  }
  auto radix = [&] (int k) {
    int m = max(n, 256);
    vector<int> c(m + 1);
    for (int e : rank) c[e + 1]++;
    for (int i = 0; i < m; i++) {
      c[i + 1] += c[i];
    }
    vector<int> next_order(n);
    for (int i : order) {
      int j = c[rank[(i + k) % n]]++;
      next_order[j] = i;
    }
    swap(order, next_order);
  };
  for (int k = 1; k < n; k <<= 1) {
    radix(k);
    radix(0);
    vector<int> next_rank(n);
    int delta = 0;     
    for (int i = 1; i < n; i++) {
      delta += rank[order[i]] != rank[order[i - 1]] || rank[(order[i] + k) % n] != rank[(order[i - 1] + k) % n];
      next_rank[order[i]] = delta;
    }
    swap(rank, next_rank);
  }
  return order;
}

/// further optimization on O(nlogn), radix once;
/// default O(nlogn) should be fine on most case, use that if not necessary
vector<int> suffix_array2(const string& s) {
  int n = s.length() + 1;
  vector<int> order(n), rank(n);
  iota(order.begin(), order.end(), 0);
  for (int i = 0; i < n - 1; i++) {
    rank[i] = s[i];
  }
  int m = max(n, 256);
  auto radix = [&]() {
    vector<int> c(m + 1);
    for (int e : rank) c[e + 1]++;
    for (int i = 0; i < m; i++) {
      c[i + 1] += c[i];
    }
    vector<int> next_order(n);
    for (int i : order) {
      int j = c[rank[i]]++;
      next_order[j] = i;
    }
    order.swap(next_order);
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
    rank.swap(next_rank);
  }
  return order;
}

vector<int> compute_lcp(const string& s, const vector<int>& sa) {
  int n = sa.size();
  vector<int> phi(n), lcp(n);
  for (int i = 0; i < n; i++) {
    phi[sa[i]] = i;
  }
  int prefix = 0;
  for (int i = 0; i < n; i++) {
    // if(!phi[i]) lcp[phi[i]] = prefix = 0;
    if (!phi[i]) continue;
    
    int a = sa[phi[i]] + prefix;
    int b = sa[phi[i] - 1] + prefix;
    while (s[a++] == s[b++]) prefix++;
    
    lcp[phi[i]] = prefix;
    prefix = max(prefix - 1, 0);
  }
  return lcp;
}

string get_lcs(const string& s, const string& t) {
  int x = s.length(), y = t.length();
  string S = s + '#' + t;
  vector<int> sa = suffix_array(S);
  vector<int> lcp = compute_lcp(S, sa);
  int n = sa.size();
  
  auto partition = [&](int k) {
    return k >= x + 1;
  };
  int ans = 0, pos;
  
  for (int i = 0; i < n - 1; i++) {
    int u = sa[i], v = sa[i + 1];
    if (partition(u) == partition(v)) continue;
    
    if (u > v) swap(u, v);
    v -= x + 1;
    int len = min(x - u, y - v);
    int cur = min(lcp[i + 1], len);
    
    if (cur > ans) ans = cur, pos = v;
  }
  string ret;
  if (ans) ret = t.substr(pos, ans);
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  return 0;
}