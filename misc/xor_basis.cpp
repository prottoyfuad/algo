
#include <bits/stdc++.h>
 
using namespace std;

vector<int> basis;
 
void add(int x) {
  for (int b : basis) {
    if ((x ^ b) < x) {
      x ^= b;
    }
  }
  for (int& b : basis) {
    if ((x ^ b) < b) {
      b ^= x;
    }
  }
  if (x) {      
    basis.push_back(x);
    for (int i = (int) basis.size() - 1; i >= 0; i--) {
      if (basis[i] < basis[i - 1]) {
        swap(basis[i], basis[i - 1]);
      }
    }
  }
}
 
int get(int k) {
  k--;
  int ans = 0;
  for (int i = 0; i < (int) basis.size(); i++) {
    if ((k >> i) & 1) {
      ans ^= basis[i];
    }
  }
  return ans;
}
 
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  while (n--) {
    int t, x;
    cin >> t >> x;
    if (t == 1) {
      add(x);
    } else {
      cout << get(x) << "\n";
    }
  }
  return 0;
}
 