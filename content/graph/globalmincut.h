/**
 * Author: Dean
 * License: CC0
 * Description: Given an nxn matrix, returns the global min cut S-T, and returns S
 * Time: O(V^3)
 * Status: Tested https://codeforces.com/gym/101504/ K
 */
#pragma once

struct mfset {
  vi par;
  mfset(int n) : par(n,-1) {}
  int find(int x) {
    return par[x] == -1? x : par[x] = find(par[x]);
  }
  void merge(int x, int y) {
    par[find(x)] = find(y);
  }
};

pair<ll, vi> StoerWagner(vector<vi>& g, int n) {
	int n1 = n;
  mfset P(n);
  vi v(n), a(n), w(n,0);
  iota(v.begin(), v.end(), 0);
	ll best = 10000000;
	vi cut;
	while (n > 1) {
		a[v[0]] = 1;
	  FOR(i, 1, n) {
			a[v[i]] = 0;
			w[i] = g[v[0]][v[i]];
		}
		int prev = v[0];
		FOR(i, 1, n) {
			int zj = -1;
      FOR(j, 1, n) if (!a[v[j]] && (zj < 0 || w[j] > w[zj])) zj = j;
			a[v[zj]] = 1;
			if (i == n - 1) {
				if (best > w[zj]){
					best = w[zj];
					cut.clear();
          FOR(k, 0, n1) if (P.find(k) == P.find(v[zj])) cut.push_back(k);
				}
				P.merge(prev, v[zj]);
        FOR(j, 0, n) g[v[j]][prev] = g[prev][v[j]] += g[v[zj]][v[j]];
				v[zj] = v[--n];
				break;
			}
			prev = v[zj];
      FOR(j, 1, n) if (!a[v[j]]) w[j] += g[v[zj]][v[j]];
		}
	}
	return {best, cut};
}
