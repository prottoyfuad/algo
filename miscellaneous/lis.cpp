
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void lis(vector<int> a) {
  int n = a.size();
  const int inf = 1e9 + 7;
  vector<int> d(n + 1, inf);
  d[0] = -inf;
  
  vector<int> pos(n + 1), par(n + 1);
  for (int i = 0; i < n; i++) {
    int j = upper_bound(d.begin(), d.end(), a[i]) - d.begin();
    if (d[j - 1] < a[i] && a[i] < d[j]) {
      d[j] = a[i];
      pos[j] = i;
      par[i] = pos[j - 1];
    }
  }
  
  int ans = 0, at = -1;
  for (int i = 1; i <= n; i++) {
    if (d[i] < INF) {
      ans = i;
    }
  }
  cout << '\n' << ans << '\n';
  
  vector<int> lis(ans);
  int u = pos[ans];
  for (int i = ans - 1; i >= 0; i--) {
    lis[i] = a[u];
    u = par[u];
  }
  for (int e : lis) cout << e << ' ' ;
  cout << "\n~done!\n";
}


// non dec. use ub for inc.lis
void lis1(vector<int> a) {
  int n = a.size();
  vector<int> lis;
  for (int i = 0; i < n; i++) {
    int j = lower_bound(lis.begin(), lis.end(), a[i]) - lis.begin();
    if (j == (int) lis.size()) lis.push_back(a[i]);
    else lis[j] = a[i];
  }
  
  for (int e : lis) cout << e << ' ' ; cout << '\n';
}

void lis2(vector<int> a) {
  int n = a.size();
  multiset<int> S;
  for (int i = 0; i < n; i++) {
    S.insert(a[i]);
    auto it = S.lower_bound(a[i]);
    if (++it != S.end()) S.erase(it);
  }
  
  vector<int> lis(S.begin(), S.end());
  for (int e : lis) cout << e << ' ' ; cout << '\n';
}

void lnds2(vector<int> a) {
  int n = a.size();
  multiset<int> S;
  for (int i = 0; i < n; i++) {
    S.insert(a[i]);
    auto it = S.upper_bound(a[i]);
    if (it != S.end()) S.erase(it);
  }
  
  vector<int> lis(S.begin(), S.end());
  for (int e : lis) cout << e << ' ' ; cout << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  lis(a);
  return 0;
}
  