/**
 * Author: Dean
 * License: CC0
 * Description: builds the gomory-hu maxflow tree, remember to reset edges at each maxflow call
 * Time: O(V) * O(MAXFLOW)
 * Status: Tested https://codeforces.com/contest/343/problem/E
 */

void gomory_hu(vector<vi>& adj, vector<Edge>& E, vi& parent, vector<vector<ll>>& ans) {
  int n = sz(adj);
  parent.assign(n,0);
  ans.assign(n, vector<ll>(n,oo));
  FOR(i,1,n) {
    ll f = maxflow(i, parent[i], adj, E);
    bfs(i, parent[i], adj, E);
    FOR(j, i+1, n) if (d[j] == -1 and parent[j] == parent[i]) parent[j] = i;
    ans[i][parent[i]] = ans[parent[i]][i] = f;
    FOR(j,0,i)  ans[i][j] = ans[j][i] = min(f, ans[parent[i]][j]);
  }
}

