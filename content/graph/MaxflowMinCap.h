/**
 * Author: Dean Zhu
 * Date: 2018-11-15
 * License: CC0
 * Source: UPC
 * Description: Normal maxflow but with minimum capacity in each edge.
 * Usage: Need to copy maxflow, pass source sink adj matrix, Edge matrix and choose scaling if needed
 * Time: O(V^2 * E) for general graphs. For unit capacities O(min(V^(2/3), E^(1/2)) * E)
 * Status: tested on https://codeforces.com/gym/101252/problem/I
 */

#include "FastMaxFlow.h"
struct Edge { int u, v; ll cap[2], mincap, flow; };

void addEdge(int x, int y, ll c, ll m, vector<vi>& adj, vector<Edge>& E) {
    Edge e; e.u = x; e.v = y;
    e.cap[0] = c - m; e.cap[1] = 0; e.mincap = m;
    adj[x].push_back(E.size()); adj[y].push_back(E.size());
    E.push_back(e);
}

ll mincap(int s, int t, vector<vi>& adj, vector<Edge>& E, int F = 0) {
    int n = adj.size();
    int m = E.size();
    vector<ll> C(n, 0);
    for (int i = 0; i < m; ++i) {
        C[E[i].u] -= E[i].mincap;
        C[E[i].v] += E[i].mincap;
    }
    adj.push_back(vi(0));
    adj.push_back(vi(0));
    ll flowsat = 0;
    for (int i = 0; i < n; ++i) {
        if (C[i] > 0) {
            addEdge(n, i, C[i], 0, adj, E);
            flowsat += C[i];
        }
        else if (C[i] < 0) addEdge(i, n + 1, -C[i], 0, adj, E);
    }
    addEdge(t, s, oo, 0, adj, E);
    for (int i = 0; i < (int)E.size(); ++i) E[i].flow = 0;
    if (flowsat != maxflow(n, n + 1, adj, E, F)) return -1;
    maxflow(s, t, adj, E, F);
    while ((int)E.size() > m) E.pop_back();
    adj.pop_back();
    adj.pop_back();
    for (int i = 0; i < n; ++i) {
        int j = (int)adj[i].size() - 1;
        while (j >= 0 and adj[i][j] >= m) {
            --j;
            adj[i].pop_back();
        }
    }
    ll flow = 0;
    for (int i = 0; i < m; ++i) {
        E[i].flow += E[i].mincap;
        if (E[i].u == s) flow += E[i].flow;
        else if (E[i].v == s) flow -= E[i].flow;
    }
    return flow;
}
