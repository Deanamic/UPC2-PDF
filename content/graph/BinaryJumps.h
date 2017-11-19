/**
 * Author: Dean & Michael
 * License: CC0
 * Description: Computes lca with binaryjumps. Insert nodes in dfs preorder
 * Time: O(n \log n)
 * Status: Tested on http://codeforces.com/contest/757/problem/F
 */

const ll maxN = 201005; // TODO
const ll MAXLOG = 20; // TODO: (1 << MAXLOG) > maxN
struct BinaryLifting {
	ll BL[maxN][MAXLOG];
	ll D[maxN];

	void init(ll root) { D[root] = 1; }
	void insert(ll n, ll par) {
		D[n] = D[par] + 1;
		BL[n][0] = par;
		FOR(j, 1, MAXLOG) BL[n][j] = BL[BL[n][j-1]][j-1];
	}
	ll lift(ll node, ll h) {
		ll cnt = 0;
		while(h) {
			if(h&1) node = BL[node][cnt];
			cnt++; h >>= 1;
		}
		return node;
	}
	int lca(int a, int b) {
		if(D[a] > D[b]) swap(a, b);
		FORD(i, 0, MAXLOG) if(D[BL[b][i]] >= D[a]) b = BL[b][i];
		if(a == b) return a;
		FORD(i, 0, MAXLOG) if(BL[a][i] != BL[b][i])
			a = BL[a][i], b = BL[b][i];
		return BL[a][0];
	}
};
