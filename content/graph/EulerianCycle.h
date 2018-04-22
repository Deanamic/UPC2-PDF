/**
 * Author: Dean
 * License: CC0
 * Description: returns de eulerian cycle/tour starting at u. If its a tour it must start at a vertex with odd degree. It is common to add edges between odd vertex to find a pseudo euler tour.
 * Time: O(E)
 * Status: Undirected Tested, Directed tested: http://codeforces.com/contest/508/problem/D
 * Usage: adj should contain index of edge in the vector<edge>, if undirected add index to both rows of adj list. If directed make sure if it needs to be connected, difference between in/out edges. If it is a tour then u must be a vertex with odd degree, else it can be any edge.
 */
#pragma once

struct edge{
	int u, v;
	bool used;
};

void Eulerdfs(int u, vi &nxt, vi &Euler, vector<edge> &E, const vector<vi> &adj) {
	while(nxt[u] < adj[u].size()){
		int go = adj[u][nxt[u]++];
		if(!E[go].used){
			E[go].used = 1;
			int to = (E[go].u ^ E[go].v ^ u);
			Eulerdfs(to, nxt, Euler, E, adj);
		}
	}
	Euler.push_back(u);
}

vi Eulerian(int u, vector<edge> &E, const vector<vi> &adj) {
	vi nxt (adj.size(), 0); vi Euler;
	Eulerdfs(u, nxt, Euler, E, adj);
	reverse(Euler.begin(), Euler.end());
	return Euler;
}
