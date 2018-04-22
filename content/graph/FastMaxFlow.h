/**
 * Author: Dean
 * License: CC0
 * Description: Returns maximum flow, not necessary for unit graphs.
 * Time: O(V * E * log(f)) where f is the maxflow for general graphs. It is generally very fast.
 * Status: Tested on  http://codeforces.com/gym/101464 D, Seerc 2011
 * Usage: F should be log(f). Set cap[1] to c if it is undirected. To obtain a cut in the mincut problem one must bfs from the source. All the vertices reached from it using only edges with CAP > 0 are in the same cut. To use without scaling change >= lim to > 0, remove the lim parameter, make dfs a ll function and use the indications in the code.
 */

const ll oo = 100000000000000LL;
#define VEI(w,e) ((E[e].u == w) ? E[e].v : E[e].u)
#define CAP(w,e) ((E[e].u == w) ? E[e].cap[0] - E[e].flow : E[e].cap[1] + E[e].flow)
#define ADD(w,e,f) E[e].flow += ((E[e].u == w) ? (f) : (-(f)))

struct Edge{ int u, v; ll cap[2], flow; };
vector<int> d, act;

bool bfs(int s, int t, vector<vector<int>>& adj, vector<Edge>& E, int lim) {
  queue<int> Q;
  d = vector<int>(adj.size(), -1);
  d[t] = 0; Q.push(t);
  while (Q.size() and d[s] == -1) {
    int u = Q.front(); Q.pop();
    for (int i = 0; i < int(adj[u].size()); ++i) {
      int e = adj[u][i], v = VEI(u, e);
      if (CAP(v, e) >= lim and d[v] == -1) {
        d[v] = d[u] + 1;
        Q.push(v);
      }
    }
  }
  return d[s] >= 0;
}

bool dfs(int u, int t, int bot, vector<vector<int>>& adj,vector<Edge>& E, int lim) {
  if (bot == 0) return false; //return 0
  if (u == t) return true; //return bot
  for (; act[u] < int(adj[u].size()); ++act[u]) {
    int e = adj[u][act[u]];
    if (CAP(u, e) >= lim and d[u] == d[VEI(u, e)] + 1) {
      bool inc=dfs(VEI(u,e),t,min(bot,CAP(u,e)),adj,E,lim);
      if (inc) {
        ADD(u, e, lim); //ADD(u, e, inc)
        return true; //return inc
      }
    }
  }
  return false; //return 0
}

ll maxflow(int s, int t, int F, vector<vector<int>>& adj, vector<Edge>& E) {
  for (int i=0; i<int(E.size()); ++i) E[i].flow = 0;
  ll flow = 0;
  for(int lim = (1<<F); lim >= 1;) { //while(bfs(s,t,adj,E)
    if(!bfs(s,t,adj,E, lim)) { //remove
      lim >>= 1;
      continue;
    }
    act = vector<int>(adj.size(), 0);
    while (dfs(s, t, oo, adj, E, lim)) flow += lim; //bot = dfs..  flow += bot
  }
  return flow;
}

void addEdge(int x, int y, ll c, vector<vector<int>>& adj, vector < Edge > & E){
  Edge e;
  e.u = x; e.v = y;
  e.cap[0] = c; e.cap[1] = 0;
  adj[x].push_back(E.size());
  adj[y].push_back(E.size());
  E.push_back(e);
}
