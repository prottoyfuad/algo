  
#include <vector>
#include <iostream>

using namespace std;

vector<int> pre_fun(const string& s) {
  int n = s.length();
  vector<int> pre(n + 1);
  pre[0] = -1; 
  for (int i = 0; i < n; i++) {
    int j = pre[i];
    while (j >= 0 && s[i] != s[j]) {
      j = pre[j];
    }
    pre[i + 1] = j + 1;
  }
  return pre;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  return 0;
}
  
