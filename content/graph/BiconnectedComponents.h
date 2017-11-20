/**
 * Author: Simon Lindholm
 * Date: 2017-04-17
 * License: CC0
 * Source: folklore
 * Description: Finds all biconnected components in an undirected
 * graph. In a biconnected component there are at least two distinct
 * paths between any two nodes. A node can be in serveral or none
 * components. if(true) at (*) creates pseudo bridge components. With
 * these each node has at least one component and a node is an
 * articulation point iff it has > 1 components. A bridge is not part
 * of any cycle. To find biconnected components, which contain
 * articulation points (see windmill graph), run without (*) and join
 * all components of nodes, which are in more than one component,
 * using union find and create new component for nodes without
 * components. Then the components form a tree.
 * Time: O(E + V)
 * Status: tested during MIPT ICPC Workshop 2017 and on Worlds 11 H (solution see http://www.csc.kth.se/~austrin/icpc/finals2011solutions.pdf) and on http://codeforces.com/contest/652/problem/E
 */
#pragma once

vi num, st;
// TODO: resize and fill adj
vector<vi> adj, comps; // comps[i]: Components of node i
ll Time, C; // C: number of components
ll dfs(ll at, ll par) {
	ll me = num[at] = ++Time, top = me;
	st.push_back(at);
	bool first = true; // for detecting multi edges
	for(auto y: adj[at]) {
		if(y == par && first) { first = false; continue; }
		if (num[y]) {
			top = min(top, num[y]);
		} else {
			ll si = sz(st);
			ll up = dfs(y, at);
			top = min(top, up);
			if (up >= me) {
				if(up == me) { // (*) if(true) for bridge components
					FOR(p, si, sz(st)) comps[st[p]].push_back(C);
					comps[at].push_back(C++);
				}
				st.resize(si);
			}
			if(up > me) { /*e is a bridge*/ }
		}
	}
	return top;
}

void bicomps() {
	num.assign(sz(adj), 0); C = 0;
	comps.clear(); comps.resize(sz(adj));
	FOR(i,0,sz(adj)) if (!num[i]) dfs(i, -1);
}
