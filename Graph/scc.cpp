
#include <vector>
#include <iostream>
#include <algorithm>

struct SCC {
  std::vector<int> id;
  std::vector<std::vector<int>> comps;
  std::vector<int> order;
  std::vector<bool> used;
  void dfs1(std::vector<std::vector<int>>& E, int v) {
    used[v] = 1;
    for (int u : E[v]) {
      if (!used[u]) {
        dfs1(E, u);
      }
    }
    order.push_back(v);
  }  
  void dfs2(std::vector<std::vector<int>>& E, int v) {
    used[v] = 1;
    comps.back().push_back(v);
    for (int u : E[v]) {
      if (!used[u]) {
        dfs2(E, u);
      }
    }
  }  
  SCC() {}
  SCC(std::vector<std::vector<int>>& E) {
    int n = E.size();
    used = std::vector<bool> (n);
    order.reserve(n); 
    for (int i = 0; i < n; i++) {
      if (!used[i]) {
        dfs1(E, i);
      }
    }
    std::reverse(order.begin(), order.end());    
    std::vector<std::vector<int>> rev(n);
    for (int i = 0; i < n; i++) {
      for (int u : E[i]) {
        rev[u].push_back(i);
      }
    }
    id = std::vector<int> (n);
    used = std::vector<bool> (n);
    int k = 0;
    for (int i : order) {
      if (!used[i]) {
        comps.emplace_back();
        dfs2(rev, i);
        for (int v : comps.back()) {
          id[v] = k;
        }
        k++;
      }
    }
    used.clear();
    used.shrink_to_fit();
    order.clear();
    order.shrink_to_fit();
  }
  int operator[] (int v) {
    return id[v];
  }
  int size(int k = -1) {
    if (k == -1) return (int) comps.size();
    return (int) comps[k].size();
  }
};

using namespace std;

int main() {

  return 0;
}
 