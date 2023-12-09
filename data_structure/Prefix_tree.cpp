 
#include <array>
#include <vector>
#include <cassert>
#include <iostream>

template <const int A> struct Prefix_tree {
  std::vector<std::array<int, A>> to;
  std::vector<long long> cnt;
  int unit = -1;
   
  Prefix_tree() {
    add_node();
  }

  int add_node() {
    int k = (int) to.size();
    to.emplace_back();
    cnt.push_back(0);
    for (int i = 0; i < A; i++) {
      to[k][i] = unit;
    }
    return k;                    
  }

  void add(const std::vector<int>& a) {
    int i = 0;
    for (int c : a) {
      if (to[i][c] == unit) {
        to[i][c] = add_node();
      }
      cnt[i] += 1;
      i = to[i][c];
    }
    cnt[i] += 1;
  }

  long long get(const std::vector<int>& a) const {
    long long ans = 0;     
    int i = 0;
    for (int c : a) {    
      if (to[i][c] == unit) {
        break;
      }
      i = to[i][c];
      ans += cnt[i];
    }
    return ans;
  }
};

// for adding number as the bits.
// some xor stuff
struct Prefix_tree {
  int bits;
  std::vector<std::array<int, 2>> childs;  
  Prefix_tree(int b = 31) : bits(b) {
    add_node();
  }
  int add_node() {
    childs.push_back({-1, -1});
    return childs.size() - 1;
  }
  void insert(int b) {
    int i = 0;
    for (int j = bits; j >= 0; j--) {
      int c = b >> j & 1;
      if (childs[i][c] == -1) {
        childs[i][c] = add_node();
      }
      i = childs[i][c];
    }
  }
  /*
  int min_query(int b) {
    int res = 0;
    int i = 0;
    for (int j = bits; j >= 0; j--) {
      int c = b >> j & 1;
      if (childs[i][c] != -1) {
        i = childs[i][c];
      }
      else {
        res |= 1 << j;
        i = childs[i][c ^ 1];
      }
    }
    return res;
  }
  int max_query(int b) {
    int res = 0;
    int i = 0;
    for (int j = bits; j >= 0; j--) {
      int c = b >> j & 1;
      if (childs[i][c ^ 1] != -1) {
        res |= 1 << j;
        i = childs[i][c ^ 1];
      }
      else {
        i = childs[i][c];
      }
    }
    return res;
  }
  */
};

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  return 0;
}
 