
#include <vector>
#include <iostream>

using namespace std;

template <typename T = long long> struct Ndimsum {
  int D, S;
  vector<int> n;
  vector<T> a;

  void init() {
    for (int i = 0; i < D; i++) {
      S *= n[i] + 1;
    }
    a.assign(S, 0);
  }

  // D_dimensions, each having N_length
  explicit Ndimsum(int D_, int N_) : D(D_), S(1), n(D, N_) { init(); }
  
  // Variable length dimentions, n_[i] being the i'th dimention's length
  explicit Ndimsum(vector<int> n_) : D(n_.size()), S(1), n(n_) { init(); }

  int get(const vector<int>& v) {
    int at = 0;
    for (int i = 0; i < D; i++) {
      at *= n[i];
      at += v[i];
    }
    return at;
  }

  T make(vector<int>& v, int pos = 0, int del = 0) {
    if (pos >= D) {
      if (del == 0) {
        return 0;
      }
      return del & 1 ? a[get(v)] : -a[get(v)];
    }
    T ans = 0;
    v[pos]--;
    ans += make(v, pos + 1, del + 1);
    v[pos]++;
    ans += make(v, pos + 1, del);
    return ans;
  }

  void build_from_input(vector<int>& v, int pos) {
    if (pos >= D) {
      T x;
      cin >> x;
      a[get(v)] = make(v) + x;
      return;
    }
    for (v[pos] = 1; v[pos] <= n[pos]; v[pos]++) {
      build_from_input(v, pos + 1);
    }
  }

  void build_from_input() {
    vector<int> v(D);
    build_from_input(v, 0);
  }

  T query(vector<int>& l, vector<int>& r, int pos = 0, int del = 0) {
    if (pos >= D) {
      return a[get(r)] * (del & 1 ? -1 : 1);
    }
    T ans = 0;
    int tmp = r[pos];
    r[pos] = l[pos];
    ans += query(l, r, pos + 1, del + 1);
    r[pos] = tmp;
    ans += query(l, r, pos + 1, del);
    return ans;
  }
};

