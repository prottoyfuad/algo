
// fastest implementation with few more memory(vectors)
// author: tourist
template <typename T>
vector<int> suffix_array_tourist(int n, const T &s, int char_bound) {
  vector<int> a(n);
  if (n == 0) {
    return a;
  }
  if (char_bound != -1) {
    vector<int> aux(char_bound, 0);
    for (int i = 0; i < n; i++) {
      aux[s[i]]++;
    }
    int sum = 0;
    for (int i = 0; i < char_bound; i++) {
      int add = aux[i];
      aux[i] = sum;
      sum += add;
    }
    for (int i = 0; i < n; i++) {
      a[aux[s[i]]++] = i;
    }
  } else {
    iota(a.begin(), a.end(), 0);
    sort(a.begin(), a.end(), [&s](int i, int j) { return s[i] < s[j]; });
  }
  vector<int> sorted_by_second(n);
  vector<int> ptr_group(n);
  vector<int> new_group(n);
  vector<int> group(n);
  group[a[0]] = 0;
  for (int i = 1; i < n; i++) {
    group[a[i]] = group[a[i - 1]] + (!(s[a[i]] == s[a[i - 1]]));
  }
  int cnt = group[a[n - 1]] + 1;
  int step = 1;
  while (cnt < n) {
    int at = 0;
    for (int i = n - step; i < n; i++) {
      sorted_by_second[at++] = i;
    }
    for (int i = 0; i < n; i++) {
      if (a[i] - step >= 0) {
        sorted_by_second[at++] = a[i] - step;
      }
    }
    for (int i = n - 1; i >= 0; i--) {
      ptr_group[group[a[i]]] = i;
    }
    for (int i = 0; i < n; i++) {
      int x = sorted_by_second[i];
      a[ptr_group[group[x]]++] = x;
    }
    new_group[a[0]] = 0;
    for (int i = 1; i < n; i++) {
      if (group[a[i]] != group[a[i - 1]]) {
        new_group[a[i]] = new_group[a[i - 1]] + 1;
      } else {
        int pre = (a[i - 1] + step >= n ? -1 : group[a[i - 1] + step]);
        int cur = (a[i] + step >= n ? -1 : group[a[i] + step]);
        new_group[a[i]] = new_group[a[i - 1]] + (pre != cur);
      }
    }
    swap(group, new_group);
    cnt = group[a[n - 1]] + 1;
    step <<= 1;
  }
  return a;
}

template <typename T>
vector<int> suffix_array_tourist(const T &s, int char_bound) {
  return suffix_array_tourist((int) s.size(), s, char_bound);
}

// best: O(nlogn), radix once;
// default O(nlogn) should be fine on most case, use that if not necessary

template <typename T>
vector<int> suffix_array(const T& s, int char_bound = 256) {
  int n = s.length() + 1;
  vector<int> order(n), rank(n);
  iota(order.begin(), order.end(), 0);
  for (int i = 0; i < n - 1; i++) {
    rank[i] = s[i];
  }
  int m = max(n, char_bound);
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
  int pre = 0;
  for (int i = 0; i < n; i++) {
    // if(!phi[i]) lcp[phi[i]] = pre = 0;
    if (!phi[i]) continue;
    
    int a = sa[phi[i]] + pre;
    int b = sa[phi[i] - 1] + pre;
    while (s[a++] == s[b++]) pre++;
    
    lcp[phi[i]] = pre;
    pre = max(pre - 1, 0);
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
    return k > x;
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

// Answer Q queries:
// Find position of kth occurance of substr[ s[l]..s[r] ] in S
void findKth(const string& s) {
  int n = s.length();
  auto sa = suffix_array(s);
  auto lcp = compute_lcp(s, sa);
  vector<int> phi(n + 1);
  for (int i = 0; i <= n; i++) {
    phi[sa[i]] = i;
  }
  SparseTable<int> st(lcp, [](const int& x, const int& y) { return min(x, y); });
  MergeTree<int> mst(sa);
  int q;
  cin >> q;
  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
    l--;
    int d = r - l;
    int p = phi[l];
    int L = p, R = p + 1;
    if (lcp[p] >= d) {
      int lo = 0, hi = p + 1;
      while (lo + 1 < hi) {
        int x = (lo + hi) / 2;
        if (st.get(x, p + 1) >= d) {
          hi = x;
        } else {
          lo = x;
        }
      }
      L = hi - 1;
    }
    if (p < n) {
      int lo = p, hi = n + 1;
      while (lo + 1 < hi) {
        int x = (lo + hi) / 2;
        if (st.get(p, x + 1) >= d) {
          lo = x;
        } else {
          hi = x;
        }
      }
      R = lo + 1;
    }
    if (R - L < k) {
      cout << -1 << '\n';
    } else {    
      int lo = -1, hi = n;
      while (lo + 1 < hi) {
        int x = (lo + hi) / 2;
        int cnt = mst.count(L, R, x);
        if (cnt < k) {
          lo = x;
        } else {
          hi = x;
        }
      }
      cout << lo + 1 << '\n';
    }
  }
  return;
}
