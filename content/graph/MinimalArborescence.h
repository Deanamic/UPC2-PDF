/**
 * Author: FAU
 * License: ???
 * Description: Computes a minimal spanning tree in a directed graph from a root under the condition, that it exists. Set the values marked with TODO. Algo changes N and from!
 * Time: O(n \log n)
 * Status: FAU tested
 */
#pragma once

int N, R; // TODO number of nodes and number of root
vector<pii> from[2*MAXN]; // TODO for each node list of (predecessor, cost)
int pred[2*MAXN], label[2*MAXN];
bool del[2*MAXN];

bool cycle(int n, int p) {
	if (label[n] == 2) return false;
	if (label[n] == 1) {
		label[n] = -1;
		return true;
	}
	label[n] = 1;
	if (cycle(pred[n], n)) {
		if (label[n] == 1) {
			label[n] = -1;
		} else if (p != -1) {
			label[p] = 2;
		}
		return true;
	} else {
		label[n] = 2;
		return false;
	}
}
int rek() {
	int res = 0;
	pred[R] = -1;
	FOR(i, 0, N) {
		if (i == R || del[i]) continue;
		int m = oo;
		FOR(j, 0, sz(from[i])) m = min(m, from[i][j].second);
		res += m;
		FOR(j, 0, sz(from[i])) {
			from[i][j].second -= m;
			if (from[i][j].second == 0) pred[i] = from[i][j].first;
		}
	}
	FOR(i, 0, N) label[i] = 0;
	label[R] = 2;
	FOR(i, 0, N) {
		if (del[i] || label[i] == 2) continue;
		if (cycle(i, -1)) {
			FOR(j, 0, N) {
				if (del[j]) continue;
				if (label[j] == -1) {
					FOR(k, 0, sz(from[j])) if (label[from[j][k].first] != -1)
						from[N].pb(from[j][k]);
					from[j].clear();
					del[j] = true;
				} else {
					FOR(k, 0, sz(from[j])) if (label[from[j][k].first] == -1)
						from[j][k].first = N;
				}
			}
			del[N++] = false;
			return res + rek();
		}
	}
	return res;
}

int min_arbor() {
	FOR(i, 0, N) del[i] = false;
	return rek();
}
