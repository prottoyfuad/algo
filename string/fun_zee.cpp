  
#include <vector>
#include <iostream>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  string s;
  cin >> s;
  int n = s.length();

  vector<int> z(n);
  for (int i = 1, l = 0; i < n; i++) {
    z[i] = min(z[i - l], l + z[l] - i);
    z[i] = max(z[i], 0);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i] += 1;
    if (i + z[i] > l + z[l]) l = i;  
  }

  return 0;
}
  
