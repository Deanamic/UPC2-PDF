/**
 * Author: Dean
 * License: CC0
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Time: O(E + V)
 * Status: Tested in a 2Sat Problem
 * Usage: Use addedge to add edges in a directed graph(will also add reverse edges), after calling Kosaraju comp will save the component number of each vertex ordered by topological order.
 */
#pragma once

const int MAXN = 100010;
stack<int> st;
int m[MAXN], comp[MAXN];
vector<int> adj[2][MAXN];
int c = 0;

void addedge(vector<vector<int>> &adj, int u, int v) {
    adj[0][u].push_back(v);
    adj[1][v].push_back(u);
}

void dfs(int u, int t, vector<int>& m) {
    m[u] = 1;
    for(int v : adj[t][u]) if(!m[v]) dfs(v,t);
    if(t) comp[u] = c;
    else st.push(u);
}

void kosaraju(int n) {
    vector<int> m(n,0);
    for(int i = 0; i < n; ++i) if(!m[i]) dfs(i,0,m);
    m = vector<int>(n,0);
    for(;st.size();st.pop()) if(!m[st.top()]) dfs(st.top(),1), c++;
}
