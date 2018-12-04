/**
 * Author: Dean
 * Date: 2018-11-28
 * Source: Adamant codeforces blog
 * Description: Creates a Heavy Light Decomposition which also allows subtree updates. Subtree of v is [in[v], out[v]). [in[nxt[v]],in[v]] is the heavy path of v
 * Status: Tested
 * Time: O(V+E)
 */

struct HLD {
  vi sz, in, out, rin, nxt;
  int t;
  HLD(int n) : sz(n), in(n,0), out(n), rin(n), nxt(n), t(0){}

  void dfs_sz(int v = 0, vector<vi>& adj) {
    sz[v] = 1;
    for(auto &u: adj[v]) {
      dfs_sz(u); sz[v] += sz[u];
      if(sz[u] > sz[adj[v][0]]) swap(u, adj[v][0]);
    }
  }

  void dfs_hld(int v = 0, vector<vi>& adj) {
    in[v] = t++; rin[in[v]] = v;
    for(auto u: adj[v]) {
      nxt[u] = (u == adj[v][0] ? nxt[v] : u);
      dfs_hld(u);
    }
    out[v] = t;
  }
};
