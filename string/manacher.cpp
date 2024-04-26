
#include <vector>
#include <iostream>

using namespace std;

vector<int> manacher_odd(string s) {
  int N = (int) s.length();
  s = "$" + s + "^";
  vector<int> p(N + 2);
  int l = 1, r = 1;
  for (int i = 1; i <= N; i++) {
    p[i] = max(0, min(r - i, p[l + r - i]));
    while (s[i - p[i]] == s[i + p[i]]) {
      p[i] += 1;
    }
    if (i + p[i] > r) {
      l = i - p[i], r = i + p[i];
    }
  }
  return vector<int>(p.begin() + 1, p.end() - 1);
}

vector<int> manacher(const string& s) {
  int n = (int) s.length();
  string t(n * 2 + 1, '#');
  for (int i = 0; i < n; i++) {
    t[i * 2 + 1] = s[i];
  }
  return manacher_odd(t);
}

void solve(const string& s) {  
  auto pal = manacher(s);
  auto ispal = [&](int l, int r) {
    return (pal[l + r] - 1) / 2 >= (r - l) / 2;
  };
}

// another implementation 
// with separated odd and even length
void manacher2() {
	string s;
  cin >> s;
  int n = (int) s.length();

  vector pal(2, vector<int> (n));
  for (int j = 0; j < 2; j++) {
    for (int i = 0, l = 0, r = 0; i < n; i++) {
      int t = r - i + (j ^ 1);
      if (i < r) {
        pal[j][i] = min(t, pal[j][l + t]);
      }
      int L = i - pal[j][i];
      int R = i + pal[j][i] - (j ^ 1);
      while (L > 0 && R < n - 1 && s[L - 1] == s[R + 1]) {
        pal[j][i] += 1;
        L -= 1, R += 1;
      }
      if (R > r) {
        l = L, r = R;
      }
    }
  } 

  // [l..r)
  auto ispal = [&](int l, int r) {
    int d = r - l, x = (l + r) / 2;
    return pal[d & 1][x] >= d / 2;
  };

  return;
}

int main() {

}

