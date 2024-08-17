
#include <vector>
#include <iostream>

using namespace std;

struct Ndimsum {
  int D, S;
  vector<int> n, v;
  vector<long long> a;

  // D_dimensions, each having N_length
  explicit Ndimsum(int D_, int N_) : D(D_), S(1) {
    n.assign(D, N_);
    for (int i = 0; i < D; i++) {
      S *= n[i] + 1;
    }
    v.assign(D, 0);
    a.assign(S, 0);
  }

  // Variable length dimentions, n_[i] being the i'th dimention's length
  explicit Ndimsum(vector<int> n_) : D(n_.size()), S(1), n(n_) {
    for (int i = 0; i < D; i++) {
      S *= n[i] + 1;
    }
    v.assign(D, 0);
    a.assign(S, 0);
  }

  int get(const vector<int>& index) {
    int at = 0;
    for (int i = 0; i < D; i++) {
      at *= n[i];
      at += index[i];
    }
    return at;
  }

  long long make(int pos = 0, int del = 0) {
    if (pos >= D) {
      if (del == 0) {
        return 0;
      }
      return del & 1 ? a[get(v)] : -a[get(v)];
    }
    long long ans = 0;
    v[pos]--;
    ans += make(pos + 1, del + 1);
    v[pos]++;
    ans += make(pos + 1, del);
    return ans;
  }

  void build_from_input(int pos = 0) {
    if (pos >= D) {
      int x;
      cin >> x;
      a[get(v)] = make() + x;
      return;
    }
    for (v[pos] = 1; v[pos] <= n[pos]; v[pos]++) {
      build_from_input(pos + 1);
    }
  }

  long long query(vector<int>& l, vector<int>& r, int pos = 0, int del = 0) {
    if (pos >= D) {
      return a[get(r)] * (del & 1 ? -1 : 1);
    }
    long long ans = 0;
    int tmp = r[pos];
    r[pos] = l[pos];
    ans += query(l, r, pos + 1, del + 1);
    r[pos] = tmp;
    ans += query(l, r, pos + 1, del);
    return ans;
  }
};

