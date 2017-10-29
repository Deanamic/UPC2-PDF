/**
 * Author: Dean
 * License: CC0
 * Description: returns de eulerian cycle/tour starting at u, cycle is in reverse order. If its a tour it must start at a vertex with odd degree. It is common to add edges between odd vertex to find a pseudo euler tour.
 * Time: O(E)
 * Status: Undirected version is tested
 * Usage: Call find cycle with a vertex where a eulerian tour/cycle is possible, when adding edges make sure that two vertex have the same edge iff it is undirected.
 */
#pragma once

typedef vector<int> vi;
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
	vi nxt (adj.size(),0);
	vi Euler;
	Eulerdfs(u, nxt, Euler, E, adj);
	reverse(Euler.begin(), Euler.end());
	return Euler;
}
