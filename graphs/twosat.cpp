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
        k += 1;
      }      
    }                     
  }
  int operator[] (int v) {
    return id[v];
  }
  int size() {                   
    return k;
  }
};

struct Two_sat {
  int n;
  std::vector<bool> ans;
  std::vector<std::vector<int>> e;

  Two_sat() : n(0), ans(0), e(0) {}
  Two_sat(int s) : n(s), ans(s), e(s * 2) {}

  void add_disjunction(int i, bool f, int j, bool g) {
    assert(0 <= std::min(i, j) && std::max(i, j) < n);
    int u = 2 * i + f;
    int v = 2 * j + g;
    e[u ^ 1].push_back(v);
    e[v ^ 1].push_back(u);
  }

  bool solve() {
    SCC scc(e);
    for (int i = 0; i < n; i++) {
      if (scc[2 * i] == scc[2 * i + 1]) return false;
      ans[i] = scc[2 * i] < scc[2 * i + 1];
    }
    return true;
  }

  int operator[] (int v) {
    return ans[v];
  }
};
