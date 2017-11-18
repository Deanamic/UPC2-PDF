/**
 * Author: FAU
 * License: ???
 * Description: findMatch finds a stable matching where the first groups is prefered given the preference lists of two groups of persons
 * Time: O(N^2)
 * Status: tested on https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1838
 * Usage: pr1[i] = preference list of person i (from 1. list) (format A), pr2[i][j] = position in the preference list of person j (from 1. list), in preference list of i (from 2. list) (format B)
 */
#pragma once

const int MAXN = 4 * 1024;

int pr1[MAXN][MAXN],pr2[MAXN][MAXN];
int match[MAXN]; // match[i]=partner of person i out of group 2
int res[MAXN];   // res[i]=partner of person i out of group 1
int id[MAXN];
int N;
void findMatch() {
	fill_n(match, N, -1);
	fill_n(id, N, 0);
	FOR(m,0,N) {
		int cur = m;
		while (true) {
			int ot = pr1[cur][id[cur]];
			if (match[ot] == -1) {
				match[ot] = cur;
				break;
			}
			if (pr2[ot][cur] < pr2[ot][match[ot]]) swap(match[ot],cur);
			id[cur]++;
		}
	}
	FOR(i,0,N) res[match[i]] = i;
}
// convert preference list of format A to format B and in reverse
int ranks[MAXN][MAXN]; // values to convert
int reranks[MAXN][MAXN]; // converted values
void convertRanklist() { FOR(i,0,N) FOR(j,0,N) reranks[i][ranks[i][j]] = j; }
