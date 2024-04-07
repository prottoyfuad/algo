  
#include <vector>
#include <iostream>

using namespace std;

template <typename T>
vector<int> z_fun(const vector<T>& a) {
  int n = (int) a.size();
  vector<int> z(n);
  for (int l = 0, i = 1; i < n; i++) {
    z[i] = min(z[i - l], l + z[l] - i);
    z[i] = max(0, z[i]);
    while (i + z[i] < n && a[z[i]] == a[i + z[i]]) {
      z[i] += 1;
    }
    if (i + z[i] > l + z[l]) {
      l = i;
    }
  }
  return z;
}
 
vector<int> z_fun(const string& s) {
  return z_fun(vector<char>(s.begin(), s.end()));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  string s;
  cin >> s;
  auto z = z_fun(s);

  return 0;
}
  
