
#include <bits/stdc++.h>
                      

/// IMPLEMEMNTATION 01

template <typename Cap> struct Dinic {
  struct edge {
    int to, rev;
    Cap cap;
    edge(int to_, int rev_, Cap cap_) : to(to_), rev(rev_), cap(cap_) {
    }
  };
  int N;
  Cap inf;
  std::vector<std::vector<edge>> E;
  Dinic() : inf(1e9) {
  }
  Dinic(int n_, Cap inf_) : N(n_), inf(inf_), E(N) {
  }
  void add_edge(int from, int to, Cap cap) {
    E[from].emplace_back(to, E[to].size(), cap);
    E[to].emplace_back(from, E[from].size() - 1, 0);
  }
  Cap dfs(std::vector<int>& d, std::vector<int>& ptr, int v, int t, Cap flow) {
    if (v == t) {
      return flow; 
    }
    while (ptr[v] < (int) E[v].size()) {
      int u = E[v][ptr[v]].to;
      if (E[v][ptr[v]].cap > 0 && d[v] < d[u]) {
        Cap flow_now = dfs(d, ptr, u, t, std::min(flow, E[v][ptr[v]].cap));
        if (flow_now > 0) {
          E[v][ptr[v]].cap -= flow_now;
          E[u][E[v][ptr[v]].rev].cap += flow_now;
          return flow_now;
        }
      }
      ptr[v]++;
    }
    return 0;
  }
  void bfs(std::vector<int>& d, int s, int t) {
    d.assign(N, -1);
    d[s] = 0;
    std::vector<int> que;
    que.reserve(N);
    que.push_back(s);
    for (int i = 0; i < (int) que.size(); i++) {
      if (d[t] != -1) {
        break;
      }
      int v = que[i];
      for (auto &e : E[v]) {
        int u = e.to;
        if (e.cap > 0 && d[u] == -1) {
          d[u] = d[v] + 1;
          que.push_back(u);
        }
      }
    }
  }
  Cap max_flow(int s, int t) {
    Cap flow = 0;
    while (true) {
      std::vector<int> d;
      bfs(d, s, t);
      if (d[t] == -1) {
        break;
      }
      std::vector<int> ptr(N, 0);
      while (true) {
        Cap flow_now = dfs(d, ptr, s, t, inf);
        if (flow_now == 0) {
          break;
        }
        flow += flow_now;
      }
    }
    return flow;
  }
};
 

/// IMPLEMEMNTATION 02

template <typename T> struct Dinic {
  struct Edge {
    int to;
    T cap;
    Edge(int v = 0, T c = 0) : to(v), cap(c) {}
  };
  int n;
  T inf;
  std::vector<Edge> edges;
  std::vector<std::vector<int>> E;
  std::vector<int> ptr, dist;
  Dinic() {
  }
  Dinic(int n_, T inf_) : n(n_), inf(inf_), E(n) {
  }
  void add_edge(int u, int v, T c) {
    E[u].push_back(edges.size());
    edges.emplace_back(v, c);
    E[v].push_back(edges.size());
    edges.emplace_back(u, 0);
  }
  bool bfs(int s, int t) {
    dist.assign(n, -1);
    std::vector<int> que;
    que.reserve(n);
    que.push_back(s);
    dist[s] = 0;
    for (int i = 0; i < (int) que.size(); i++) {
      int v = que[i];
      for (int j : E[v]) {
        auto [u, c] = edges[j];
        if (c > 0 && dist[u] == -1) {
          dist[u] = dist[v] + 1;
          que.push_back(u);
        }
      }
    }
    return dist[t] != -1;
  }
  T dfs(int v, int t, T flow) {
    if (v == t) {
      return flow;
    }
    for (int& i = ptr[v]; i < (int) E[v].size(); i++) {
      int j = E[v][i];
      auto [u, c] = edges[j];
      if (c > 0 && dist[u] == dist[v] + 1) {
        T now = dfs(u, t, std::min(flow, c));
        if (now > 0) {
          edges[j].cap -= now;
          edges[j ^ 1].cap += now;
          return now;
        }
      }
    }
    return 0;
  }
  T max_flow(int s, int t) {
    T flow = 0;
    while (bfs(s, t)) {
      ptr.assign(n, 0);
      while (true) {
        T now = dfs(s, t, inf);
        if (now == 0) break;
        flow += now;
      }
    }
    return flow;
  }
};

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
  
  }
  return 0;
}
 