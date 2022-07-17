 
#include <array>
#include <vector>
#include <cassert>
#include <iostream>

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
  int l, r;
  cin >> l >> r;
  vector<int> a(r - l + 1);
  Prefix_tree trie(17);
  for (int i = 0; i <= r - l; i++) {
    cin >> a[i];
    trie.insert(a[i]);
  }
  int ans = -1;
  
  return 0;
}
 