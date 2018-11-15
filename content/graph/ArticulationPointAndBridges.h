/**
 * Author: Dean Zhu
 * Date: 2018-11-15
 * License: CC0
 * Description: Finds all articulation points and bridges of a undirected graph.
 * Time: O(E + V)
 * Status: Tested on: Bridges tested on https://jutge.org/problems/P37339_en
 */

void ArticulationPointandBridges(vector<vi>& adj, vector<Edge> E, vi& articulation, vi& bridges) {
  int n = sz(adj), m = sz(E);
  articulation = vi(n, -1);
  bridges = vi(m, -1);
  vi dfs_low(n, -1), dfs_num(n ,-1), parent(n, -1);
  articulation = vi(n, 0);
  bridges = vi(m, 0);
  int dfsroot, rootc, cnt = 0;
  function<void(int)> ABdfs =
    [&](int u) {
    dfs_num[u] = dfs_low[u] = cnt++;
    for(int t : adj[u]){
      int v = E[t].u ^ E[t].v  ^ u;
      if(dfs_num[v] == -1){
        if(u == dfsroot) rootc++;
        parent[v] = t;
        ABdfs(v);
        dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        if(dfs_low[v] >= dfs_num[u])articulation[u] = 1;
        if(dfs_low[v] > dfs_num[u]) bridges[t] = 1;
      }
      else if (t != parent[u]){
        dfs_low[u] = min(dfs_low[u], dfs_num[v]);
      }
    }
  };
  FOR(i, 0, n) {
    if(dfs_num[i] == -1) {
      rootc = 0, dfsroot = i;
      ABdfs(i);
    }
  }
}
