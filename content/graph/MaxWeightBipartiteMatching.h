/**
 * Author: FAU
 * License: ???
 * Description: finds a max weight bipartite matching. hungarian() returns the value of the max weight matching. xy contains for each vertex on the left the corresponding node right, yx the other way around.
 * Time: O(N^3)
 * Status: FAU tested
 * Usage: initialize cost matrix (profit of matching on of the N left vertexes with one of the N right vertexes)
 */
#pragma once

int cost[N][N];
int xy[N], yx[N];
int lx[N], ly[N];
bool tree[N];
int slack[N], pred[N];

void init_matching() {
	fill_n(xy, N, -1);
	fill_n(yx, N, -1);
	fill_n(lx, N, 0);
	fill_n(ly, N, 0);
	FOR(x, 0, N) FOR(y, 0, N) lx[x] = max(lx[x], cost[x][y]);
}

void init_tree() {
	fill_n(tree, N, false);
	fill_n(pred, N, -1);
	FOR(x, 0, N) {
		if (xy[x] != -1) continue;
		tree[x] = true;
		FOR(y, 0, N) slack[y] = lx[x] + ly[y] - cost[x][y];
		break;
	}
}

bool augment() {
	bool found = true;
	while (found) {
		found = false;
		FOR(y, 0, N) {
			if (pred[y] != -1 || slack[y]) continue;
			found = true;
			FOR(x, 0, N) if (tree[x] && cost[x][y] == lx[x] + ly[y]) pred[y] = x;
			if (yx[y] == -1) {
				while (y != -1) {
					yx[y] = pred[y];
					swap(y, xy[pred[y]]);
				}
				return true;
			} else if (!tree[yx[y]]) {
				tree[yx[y]] = true;
				FOR(yy, 0, N) {
					int v = lx[yx[y]] + ly[yy] - cost[yx[y]][yy];
					slack[yy] = min(slack[yy], v);
				}
			}
		}
	}
	return false;
}

void update_labels() {
	int delta = INT_MAX;
	FOR(y, 0, N) if (pred[y] == -1) delta = min(delta, slack[y]);
	FOR(x, 0, N) if (tree[x]) lx[x] -= delta;
	FOR(y, 0, N) if (pred[y] != -1) ly[y] += delta; else slack[y] -= delta;
}

int hungarian() {
	init_matching();
	FOR(i, 0, N) {
		init_tree();
		while (!augment()) update_labels();
	}
	int res = 0;
	FOR(x, 0, N) res += cost[x][xy[x]];
	return res;
}
