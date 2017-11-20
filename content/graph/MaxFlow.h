/**
 * Author: Eric
 * License: CC0
 * Description: Returns maximum flow.
 * Time: O(V^2 * E) for general graphs. For unit capacities O(min(V^(2/3), E^(1/2)) * E). For maximum matching O(E*sqrt(V)))(bipartite unit weighted graf). It is generally very fast.
 * Status: Tested
 * Usage: To obtain a cut in the mincut problem one must bfs from the source. All the vertices reached from it using only edges with capacity > 0 are in the same cut
 */

typedef long long ll;
typedef vector<int> VI;
typedef vector<VI> VVI;
const ll INF = 1000000000000000000LL;

#define VEI(w,e) ((E[e].u == w) ? E[e].v : E[e].u)
#define CAP(w,e) ((E[e].u == w) ? E[e].cap[0] - E[e].flow : E[e].cap[1] + E[e].flow)
#define ADD(w,e,f) E[e].flow += ((E[e].u == w) ? (f) : (-(f)))

struct Edge { int u, v; ll cap[2], flow; };

VI d, act;

bool bfs(int s, int t, VVI& adj, vector<Edge>& E) {
  queue<int> Q;
  d = VI(adj.size(), -1);
  d[t] = 0;
  Q.push(t);
  while (not Q.empty()) {
    int u = Q.front(); Q.pop();
    for (int i = 0; i < int(adj[u].size()); ++i) {
      int e = adj[u][i], v = VEI(u, e);
      if (CAP(v, e) > 0 and d[v] == -1) {
        d[v] = d[u] + 1;
        Q.push(v);
      }
    }
  }
  return d[s] >= 0;
}

ll dfs(int u,int t,ll bot,VVI& adj,vector<Edge>& E) {
  if (u == t) return bot;
  for (; act[u] < int(adj[u].size()); ++act[u]) {
    int e = adj[u][act[u]];
    if (CAP(u, e) > 0 and d[u] == d[VEI(u, e)] + 1) {
      ll inc=dfs(VEI(u,e),t,min(bot,CAP(u,e)),adj,E);
      if (inc) {
        ADD(u, e, inc);
        return inc;
      }
    }
  }
  return 0;
}

ll maxflow(int s, int t, VVI& adj, vector<Edge>& E) {
  for (int i=0; i<int(E.size()); ++i) E[i].flow = 0;
  ll flow = 0, bot;
  while (bfs(s, t, adj, E)) {
    act = VI(adj.size(), 0);
    while ((bot = dfs(s,t,INF, adj, E))) flow += bot;
  }
  return flow;
}

void addEdge(int u, int v, VVI& adj, vector<Edge>& E, ll cap){
	Edge e;
	e.u = u;
	e.v = v;
	e.cap[0] = cap;
	e.cap[1] = 0;
	e.flow = 0;
	adj[u].push_back(E.size());
	adj[v].push_back(E.size());
	E.push_back(e);
}
