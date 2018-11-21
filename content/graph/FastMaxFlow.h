/**
 * Author: Dean
 * License: CC0
 * Description: Returns maximum flow.
 * Time: O(V * E * log(f)) where f is the maxflow for general graphs. It is generally very fast.
 * Status: Tested
 * Usage: F should be log(f). Set cap[1] to c if it is undirected. To obtain a cut in the mincut problem one must bfs from the source. All the vertices reached from it using only edges with CAP > 0 are in the same cut.
 * If maxflow is called without the last 2 parameters it will run a normal dinics in O(V^2*E)
 */

#define VEI(w,e) (E[e].u ^ E[e].v ^ w)
#define CAP(w,e) ((E[e].u == w) ? E[e].cap[0] - E[e].flow : E[e].cap[1] + E[e].flow)
#define ADD(w,e,f) E[e].flow += ((E[e].u == w) ? (f) : (-(f)))

struct Edge{ int u, v; ll cap[2], flow; };
vi d, act;

bool bfs(int s, int t, vector<vi>& adj, vector<Edge>& E, ll lim) {
  queue<int> Q;
  d = vi(adj.size(), -1);
  d[t] = 0; Q.push(t);
  for (Q.push(t); Q.size() and d[s] == -1; Q.pop()) {
    int u = Q.front();
    FOR(i, 0, adj[u].size()) {
      int e = adj[u][i], v = VEI(u, e);
      if (CAP(v, e) >= lim and d[v] == -1) {
        d[v] = d[u] + 1;
        Q.push(v);
      }
    }
  }
  return d[s] >= 0;
}

ll dfs(int u, int t, ll bot, vector<vi>& adj,vector<Edge>& E) {
  if (bot == 0) return 0;
  if (u == t) return bot;
  for (; act[u] < int(adj[u].size()); ++act[u]) {
    int e = adj[u][act[u]];
    if(d[u] == d[VEI(u, e)] + 1) {
      ll inc=dfs(VEI(u,e),t,min(bot,CAP(u,e)),adj,E);
      if (inc) {
        ADD(u, e, inc);
        return inc;
      }
    }
  }
  return 0;
}

ll maxflow(int s, int t, vector<vi>& adj, vector<Edge>& E, int F = 0) {
  //trav(e, E) e.flow = 0; reset
  ll flow = 0, bot;
  for(int lim = (1<<F); lim >= 1;lim>>=1) {
    while(bfs(s,t,adj,E,lim)) {
      act = vi(adj.size(), 0);
      while (bot = dfs(s, t, oo, adj, E)) flow += bot;
    }
  }
  return flow;
}

inline void addEdge(int x, int y, vector<vi>& adj, vector <Edge> & E, ll c, ll rc = 0){
  Edge e; e.u = x; e.v = y; e.flow = 0;
  e.cap[0] = c; e.cap[1] = rc;
  adj[x].push_back(sz(E)); adj[y].push_back(sz(E));
  E.push_back(e);
}
