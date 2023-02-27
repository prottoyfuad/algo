
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
    order.clear();
    used.shrink_to_fit();
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

// WITHOUT COMPS

struct SCC {
  int k;
  std::vector<int> id;                
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
    id[v] = k;
    for (int u : E[v]) {
      if (!used[u]) {
        dfs2(E, u);
      }
    }
  }  
  SCC() : k(0) {}
  SCC(std::vector<std::vector<int>>& E) : k(0) {
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
    for (int i : order) {
      if (!used[i]) {        
        dfs2(rev, i);   
      }
      k += 1;
    }                     
  }
  int operator[] (int v) {
    return id[v];
  }
  int size() {                   
    return k;
  }
};

//EXPERIMENTAL IMPLEMENTATION

struct strongly_connected_components {
  template <typename T> using digraph = std::vector<std::vector<T>>;
  char built;
  int M, N;
  std::vector<int> scc, scc_size;
  std::vector<std::vector<int>> components;

  void find_topsort(int v, const digraph<int>& G, std::vector<int>& order, std::vector<bool>& used) {
    used[v] = 1;
    for (int u : G[v]) {
      if (!used[u]) find_topsort(u, G, order, used);
    }
    order.emplace_back(v);
  }

  void find_scc(int v, const digraph<int>& G) {
    for (int u : G[v]) {
      if (scc[u] == -1) {
        scc[v] = scc[u];
        find_scc(u, G);
      }
    }
  }

  strongly_connected_components(digraph<int>& G) : built(0), M(0) {
    N = G.size();
    digraph<int> G_rev(N);
    for (int i = 0; i < N; i++) {
      for (int j : G[i]) {
        G_rev[j].emplace_back(i);
      }
    }
    std::vector<bool> was(N);
    std::vector<int> order;
    order.reserve(N);
    for (int i = 0; i < N; i++) {
      if (!was[i]) {
        find_topsort(i, G, order, was);
      }
    }
    scc = std::vector<int> (N, -1);
    for (int i = N - 1; i >= 0; i--) {
      int v = order[i];
      if (scc[v] == -1) {
        scc[v] = M++;
        find_scc(v, G_rev);
      }
    }
  }

  void build() {
    if (built) return;
    built = 1;
    scc_size = std::vector<int> (M);
    components = std::vector<std::vector<int>> (M);
    for (int u : scc) ++scc_size[u];
    for (int i = 0; i < M; i++) {
      components[i].reserve(scc_size[i]);
    }
    for (int i = 0; i < N; i++) {
      components[scc[i]].emplace_back(i);
    }
  }

  int operator [](int index) const { return scc[index]; } // this is an lvalue, read only
  std::size_t size() { return scc.size(); }
  
  digraph<int> get_condensed_graph(const digraph<int>& G) { // same digraph which scc *this is
    assert((int)G.size() == N);
    digraph<int> cgr(M);
    for (int v = 0; v < N; v++) {
      for (int u : G[v]) {
        if (scc[u] != scc[v]) {
          cgr[scc[v]].emplace_back(scc[u]);
        }
      }
    }
    return cgr;
  }
};


using namespace std;

int main() {

  return 0;
}
 