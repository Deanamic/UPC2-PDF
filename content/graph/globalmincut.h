/**
 * Author: Eric
 * License: CC0
 * Description: Given an adjacency matrix returns the global mincut and the vertices of one of the cuts.
 * Time: O(V^3)
 * Status: ???
 * Usage:
 */
#pragma once


/*
 * If you dont need the cut you can eliminate every thing with this coment "// **********"
 *Explanation of algorithm:
 *  -getting the mincut value: it does n-1 iterations. In each iteration it starts by a vertex (random) as set A.
 *  then it iterates until only two vertices are left by adding to set A the most tightly connected vertex to A (vertex not in A).
 *  it insert this vertex to A. When only two vertices are left, the mincut between those two is the weight W of the edges between
 *  the last vertex and A. mincut = min(mincut, W)
 *  We then merge the two last vertices and start again.
 *
 *  -getting the cut: basically when we merge two nodes we merge them with mfset. When we obtain a new best mincut value, a cut
 *  is represented buy the nodes in the same component as the last node;
 */

// Maximum number of vertices in the graph
#define NN 256
// Maximum edge weight (MAXW * NN * NN must fit into an int)
#define MAXW 1000
// Adjacency matrix and some internal arrays
int v[NN], w[NN];
bool a[NN];



int pare[NN]; // **********
int par (int b){ // **********
	if (pare[b] == b) return b;
	pare[b] = par(pare[b]);
	return pare[b];
}

inline void merge (int b, int c){ // **********
	pare[par(b)] = par(c);
}

pair < int, vi > minCut(vvi& g, int n) {
	int n1 = n;
	// init the remaining vertex set
	for (int i = 0; i < n; i++){
		v[i] = i;
		pare[i] = i; // **********
	}
	// run Stoer-Wagner
	int best = MAXW * n * n;
	vi cut; // **********
	while (n > 1) {
		// initialize the set A and vertex weights
		a[v[0]] = true;
		for (int i = 1; i < n; i++) {
			a[v[i]] = false;
			w[i] = g[v[0]][v[i]];
		}
		// add the other vertices
		int prev = v[0];
		for (int i = 1; i < n; i++) {
			// find the most tightly connected non-A vertex
			int zj = -1;
			for (int j = 1; j < n; j++)
				if (!a[v[j]] && (zj < 0 || w[j] > w[zj])) zj = j;
			// add it to A
			a[v[zj]] = true;
			// last vertex?
			if (i == n - 1) {
				// remember the cut weight
				if (best > w[zj]){
					best = w[zj];
					cut.clear(); // ********
					for (int ko = 0; ko < n1; ko++) if (par(ko) == par(v[zj])) cut.push_back(ko); // ********
				}

				// merge prev and v[zj]
				merge(prev, v[zj]); // *************
				for (int j = 0; j < n; j++)
					g[v[j]][prev] = g[prev][v[j]] += g[v[zj]][v[j]];
				v[zj] = v[--n];
				break;
			}
			prev = v[zj];
			// update the weights of its neighbours
			for (int j = 1; j < n; j++)
				if (!a[v[j]]) w[j] += g[v[zj]][v[j]];
		}
	}
	return {best, cut};
}
