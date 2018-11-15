/**
 * Author: Dean Zhu
 * Date: 2018-11-15
 * License: CC0
 * Source: UPC PDF
 * Description: Finds all biconnected components in an undirected
 * graph.
 * Time: O(E + V)
 * Status: tested during MIPT ICPC Workshop 2017 and on Worlds 11 H (solution see http://www.csc.kth.se/~austrin/icpc/finals2011solutions.pdf) and on http://codeforces.com/contest/652/problem/E
 */
#pragma once

struct Edge {
  int u, v; //Fill this
  int bicomp; //Index of the bic. comp. (don't fill)
};

VI bic_vertex; // Vertex repr for each bic. comp.
VI num, low; //Initialize to -1
int act, bicos; //Put this to zero for every testcase
stack<int> S;

void dfs(int u, VVI& adj, vector<Edge>& E, int p=-1){
  num[u] = low[u] = act++;
  for (int i = 0; i < adj[u].size(); ++i) {
    int v = E[adj[u][i]].v;
    if (v == u) v = E[adj[u][i]].u;
    if (num[v] == -1) {
      int size = S.size();
      S.push(adj[u][i]);
      dfs(v, adj, E, u);
      low[u] = min(low[u], low[v]);
      if (low[v] >= num[u]) {
        while (S.size() != size) {
          E[S.top()].bicomp = bicos;
          S.pop();
        }
        bic_vertex.push_back(u);
        ++bicos;
      }
    }
    else if (v != p and num[v] < num[u]) {
      S.push(adj[u][i]);
      low[u] = min(low[u], num[v]);
    }
  }
}
