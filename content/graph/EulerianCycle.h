/**
 * Author: Dean
 * License: CC0
 * Description: returns de eulerian cycle/tour starting at u, cycle is in reverse order. If its a tour it must start at a vertex with odd degree
 * Time: O(E)
 * Status: ???
 * Usage:
 */
#pragma once

//undirected graph
struct edge{
	int u, v;
	bool used;
};

vector<edge> E;
vector<vector<int> > adj; //adj stores the index in E
vector<int> nxt;
vector<int> cycle;
int p;

void find_cycle(int u){
	while(nxt[u] < adj[u].size()){
		int go = adj[u][nxt[u]++];
		if(!E[go].used){
			E[go].used = 1;
			int to = (E[go].u ^ E[go].v ^ u);
			find_cycle(to);
		}
	}
	cycle.push_back(u);
}

//directed graph
vector<int> next; //stores last visited vertex index
vector<vector<int>> adj;
vector<int> cycle;

void find_cycle(int u){
	while(next[u] < adj[u].size())
		find_cycle(adj[u][next[u]++]);
	cycle.push_back(u);
}
