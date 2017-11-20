/**
 * Author: ??
 * Date: ??
 * License: CC0
 * Source: UPC
 * Description: adj is and adjacency list, deg is the degree of the vertex. You shouldn't touch padre. w,cap are matrices, NOT LISTS!
 * Time:
 * Status: Not tested
 */

#define NN 200
#define pot(u,v) (pi[u]-pi[v])
int adj[NN][NN], deg[NN], padre[NN];
ll w[NN][NN], cap[NN][NN], pi[NN], d[NN], f[NN][NN], dist[NN];
int N;
ll flow, cost;
bool dijkstra(int s, int t) {
  memset(padre, -1, sizeof(padre));
  REP(i,N) d[i] = INF;
  d[s] = 0;
  priority_queue<PLI> Q;
  Q.push(PLI(0,s));
  while (not Q.empty()) {
    int u = Q.top().second;
    ll dist = -Q.top().first;
    Q.pop();
    if (dist != d[u]) continue;
    REP(i,deg[u]) {
      int v = adj[u][i];
      if (f[u][v] >= 0 and cap[u][v] - f[u][v] > 0 and
          d[v] > d[u] + pot(u,v) + w[u][v]) {
        d[v] = d[u] + pot(u,v) + w[u][v];
        Q.push(PLI(-d[v], v));
        padre[v] = u;
      }
      else if (f[u][v] < 0 and d[v] > d[u] + pot(u,v) - w[v][u]) {
        d[v] = d[u] + pot(u,v) - w[v][u];
        Q.push(PLI(-d[v], v));
        padre[v] = u;
      }
    }
  }
  REP(i,N) if (pi[i] < INF) pi[i] += d[i];
  return padre[t] >= 0;
}
void maxmin(int s, int t) {
  memset(f, 0, sizeof(f));
  memset(pi, 0, sizeof(pi));
  flow = cost = 0;
  while (dijkstra(s, t)) {
    ll bot = INF;
    for (int v = t, u = padre[v]; u != -1; v = u, u = padre[u]) {
      if (f[u][v] >= 0) bot = min(cap[u][v] - f[u][v], bot);
      else bot = min(f[v][u], bot);
    }
    for (int v = t, u = padre[v]; u != -1; v = u, u = padre[u]) {
      if (f[u][v] >= 0) cost += w[u][v]*bot;
      else cost -= w[v][u]*bot;
      f[u][v] += bot;
      f[v][u] -= bot;
    }
    flow += bot;
  }
}
void negative_edges(int s, int t) {
  for (int i = 0; i < N; ++i) dist[i] = INF;
  dist[s] = 0;
  for (int k = 0; k < N; ++k) {
    for (int x = 0; x < N; ++x) {
      for (int j = 0; j < deg[x]; ++j) {
        int y = adj[x][j];
        if (!cap[x][y]) continue;
        dist[y] = min(dist[x] + w[x][y], dist[y]);
      }}}
  for (int x = 0; x < N; ++x) {
    for (int j = 0; j < deg[x]; ++j) {
      int y = adj[x][j];
      if (!cap[x][y]) continue;
      w[x][y] += dist[x] - dist[y];
    }
  }
  maxmin(s, t);
  cost += flow*dist[t];
}
