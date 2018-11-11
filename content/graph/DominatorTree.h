/**
 * Author: Dean
 * Date: 11/11/18
 * License: CC0
 * Source: Codeforces Submission
 * Description: Computes dominator tree of a directed graph from a root. Vertex A dominates B, if all possible paths from root to B go through A. Dominator tree contrains exactly one path root -> A -> B. initialize adjancy lists, call dominator\_tree(r) with root r. Afterwards dom[i] is the parent of i in the dominator tree.
 * Time: O((E + V) \cdot \log V)
 * Status: Tested on https://codeforces.com/gym/101741 Problem L
 */
#pragma once

vi dominators(const vector<vi> &adj, int r) {
	int n = adj.size();
	vi ord, rank(n, n), prev(n, n), anc(n, n), idom(n, n), semi(n), low(n);
	vector<vi> adj_rev(n), dom(n);
	function<void(int)> domdfs =
    [&](int u) {
      rank[u] = sz(ord);
      ord.emplace_back(u);
      for (int v : adj[u]){
        adj_rev[v].emplace_back(u);
        if (rank[v] < n) continue;
        prev[v] = u;
        domdfs(v);
      }
    };
	domdfs(r);
	for (int i = 0; i < n; ++i) semi[i] = low[i] = i;
  function<int(int)> eval =
    [&](int v) {
      if (anc[v] < n && anc[anc[v]] < n)
        {
          int x = eval(anc[v]);
          if (rank[semi[low[v]]] > rank[semi[x]]) low[v] = x;
          anc[v] = anc[anc[v]];
        }
      return low[v];
    };
  FORD(i, 1, ord.size()) {
		int w = ord[i];
		for (int v : adj_rev[w]) {
			int u = eval(v);
      if (rank[semi[w]] > rank[semi[u]]) semi[w] = semi[u];
		}
		dom[semi[w]].emplace_back(w);
		anc[w] = prev[w];
		for (int v : dom[prev[w]]) {
			int u = eval(v);
			idom[v] = (rank[prev[w]] > rank[semi[u]] ? u : prev[w]);
		}
		dom[prev[w]].clear();
	}
  FOR(i, 1, ord.size()) {
		int w = ord[i];
		if (idom[w] != semi[w]) idom[w] = idom[idom[w]];
	}
  FOR(u, 0, n) if (idom[u] >= n) idom[u] = -1;
	return idom;
}
