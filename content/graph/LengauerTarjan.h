/**
 * Author: FAU
 * Date: ???
 * License: ???
 * Source: FAU templates
 * Description: Computes dominator tree of a directed graph from a root. Vertex A dominates B, if all possible paths from root to B go through A. Dominator tree contrains exactly one path root -> A -> B. initialize adjancy lists, call dominator\_tree(r) with root r. Afterwards dom[i] is the parent of i in the dominator tree.
 * Time: O((E + V) \cdot \log V)
 * Status: FAU tested
 */
#pragma once

vi adj[N], rev[N];
int dom[N], semi[N], par[N], node[N], anc[N], label[N];
stack<int> bucket[N];

void dfs(int n, int &cnt) {
	node[cnt] = n;
	semi[n] = cnt++;
	for (const auto &to : adj[n]) {
		if (semi[to] == -1) { par[to] = n; dfs(to, cnt); }
		rev[to].pb(n);
	}
}

void compress(int n) {
	if (anc[anc[n]] != anc[n]) {
		compress(anc[n]);
		if (semi[label[anc[n]]] < semi[label[n]]) label[n] = label[anc[n]];
		anc[n] = anc[anc[n]];
	}
}
int eval(int n) {
	if (anc[n] == n) return n;
	compress(n);
	return label[n];
}
void dominator_tree(int r) {
	FOR(i, 0, N) dom[i] = semi[i] = -1;
	int cnt = 0;
	dfs(r, cnt);
	FOR(i, 0, N) anc[i] = label[i] = i;
	FORD(i, 1, cnt) {
		int n = node[i];
		FOR(i, 0, sz(rev[n])) semi[n] = min(semi[n], semi[eval(rev[n][i])]);
		bucket[node[semi[n]]].push(n);
		anc[n] = par[n];
		while (!bucket[par[n]].empty()) {
			int m = bucket[par[n]].top();
			bucket[par[n]].pop();
			int u = eval(m);
			dom[m] = (semi[u] < semi[m]) ? u : par[n];
		}
	}
	FOR(i, 1, cnt) {
		int n = node[i];
		if (dom[n] != node[semi[n]]) dom[n] = dom[dom[n]];
	}
	FOR(i, 0, N) rev[i].clear();
}
