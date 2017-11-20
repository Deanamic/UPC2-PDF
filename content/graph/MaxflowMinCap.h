/**
 * Author: ??
 * Date: ??
 * License: CC0
 * Source: UPC
 * Description: Normal maxflow but with minimum capacity in each edge
 * Time: O(V^2 * E) for general graphs. For unit capacities O(min(V^(2/3), E^(1/2)) * E)
 * Status: Not tested
 */
 
 
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
const ll INF = 1000000000000000000LL;

#define VEI(w,e) ((E[e].u == w) ? E[e].v : E[e].u)
#define CAP(w,e) ((E[e].u == w) ? E[e].cap[0] - E[e].flow : E[e].cap[1] + E[e].flow)
#define ADD(w,e,f) E[e].flow += ((E[e].u == w) ? (f) : (-(f)))

struct Edge { int u, v; ll cap[2], mincap, flow; };

vi d, act;

bool bfs(int s, int t, vvi& adj, vector<Edge>& E) {
  queue<int> Q;
  d = vi(adj.size(), -1);
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

ll dfs(int u,int t,ll bot,vvi& adj,vector<Edge>& E) {
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

ll maxflow(int s, int t, vvi& adj, vector<Edge>& E) {
  ll flow = 0, bot;
  while (bfs(s, t, adj, E)) {
    act = vi(adj.size(), 0);
    while ((bot = dfs(s,t,INF, adj, E))) flow += bot;
  }
  return flow;
}

void addEdge(int x,int y,ll c,ll m,vvi& adj,vector<Edge>& E) {
    Edge e;
    e.u = x;
    e.v = y;
    e.cap[0] = c - m;
    e.cap[1] = 0;
    e.mincap = m;
    adj[x].push_back(E.size());
    adj[y].push_back(E.size());
    E.push_back(e);
}

ll mincap(int s, int t, vvi& adj, vector<Edge>& E) {
    int n = adj.size();
    int m = E.size();
    vll C(n, 0);
    for (int i = 0; i < m; ++i) {
        C[E[i].u] -= E[i].mincap;
        C[E[i].v] += E[i].mincap;
    }
    adj.push_back(vi(0));
    adj.push_back(vi(0));
    ll flowsat = 0;
    for (int i = 0; i < n; ++i) {
        if (C[i] > 0) {
            addEdge(n, i, C[i], 0, adj, E);
            flowsat += C[i];
        }
        else if (C[i] < 0) addEdge(i, n + 1, -C[i], 0, adj, E);
    }
    addEdge(t, s, INF, 0, adj, E);
    for (int i = 0; i < (int)E.size(); ++i) E[i].flow = 0;
    if (flowsat != maxflow(n, n + 1, adj, E)) return -1;
    maxflow(s, t, adj, E);
    while ((int)E.size() > m) E.pop_back();
    adj.pop_back();
    adj.pop_back();
    for (int i = 0; i < n; ++i) {
        int j = (int)adj[i].size() - 1;
        while (j >= 0 and adj[i][j] >= m) {
            --j;
            adj[i].pop_back();
        }
    }
    ll flow = 0;
    for (int i = 0; i < m; ++i) {
        E[i].flow += E[i].mincap;
        if (E[i].u == s) flow += E[i].flow;
        else if (E[i].v == s) flow -= E[i].flow;
    }
    return flow;
}
