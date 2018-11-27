/**
 * Author: Dean
 * License: CC0
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Time: O(E + V)
 * Status: Tested
 * Usage: Use addedge to add edges in a directed graph, after calling Kosaraju comp will save the component number of each vertex ordered by topological order.
 */
#pragma once

struct SCC {
  vi comp, m;
  vector<vi> adj[2];
  stack<int> st;
  int c;
  int n;
  SCC(int n) : comp(n), m(n,0), c(0), n(n) {
    adj[0] = adj[1] = vector<vi>(n);
  }

  void addEdge(int u, int v) {
    adj[0][u].push_back(v);
    adj[1][v].push_back(u);
  }

  void dfs(int u, int t) {
    m[u] = 1;
    for(int v : adj[t][u]) if(!m[v]) dfs(v,t);
    if(t) comp[u] = c;
    else st.push(u);
  }

  void kosaraju() {
    for(int i = 0; i < n; ++i) if(!m[i]) dfs(i,0);
    m = vi(n,0);
    for(;st.size();st.pop()) if(!m[st.top()]) dfs(st.top(),1), c++;
  }
};
