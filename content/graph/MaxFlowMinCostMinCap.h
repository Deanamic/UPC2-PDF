


struct MCMFwithBound {
  struct edge {
    int to, cap, cost, rev;
    edge(int to, int cap, int cost, int rev): to(to), cap(cap), cost(cost), rev(rev) {}
  };
  vector<vector<edge>> G;
  vi inq;
  vector<ll> dis;
  vi preve, prevv;
  void addEdge(int u, int v, int cap, int cost) {
    G[u].push_back(edge(v, cap, cost, sz(G[v].size())));
    G[v].push_back(edge(u, 0, -cost, sz(G[u].size()) - 1));
  }
  ll minCostMaxFlow(int s, int t, int flow) {
    ll res = 0;
    while (flow > 0) {
      queue<int> q;
      memset(dis, oo, sizeof dis);
      memset(inq, 0, sizeof inq);
      dis[s] = 0, inq[s] = true;
      q.push(s);
      while (!q.empty()) {
        int cur = q.front(); q.pop();
        inq[cur] = false;
        for (int i = 0; i < (int)G[cur].size(); ++i) {
          edge &e = G[cur][i];
          if (e.cap && dis[cur] + e.cost < dis[e.to]) {
            dis[e.to] = dis[cur] + e.cost;
            preve[e.to] = i;
            prevv[e.to] = cur;
            if (!inq[e.to]) {inq[e.to] = true; q.push(e.to);}
          }
        }
      }
      if (dis[t] == INF) return -1;
      int d = flow;
      for (int cur = t; cur != s; cur = prevv[cur])
        d = min(d, G[prevv[cur]][preve[cur]].cap);
      flow -= d;
      res += dis[t] * d;
      for (int cur = t; cur != s; cur = prevv[cur]) {
        edge &e = G[prevv[cur]][preve[cur]];
        e.cap -= d;
        G[e.to][e.rev].cap += d;
      }
    }
    return res;
  }
  int S, T, allFlow;
  void init(int s, int t, int n) {
    G.resize(2*n+10);
    inq = prevv = prevv = vi(2*n + 10);
    dis = vector<ll> (2*n + 10)
    S = t + 1, T = S + 1;
    allFlow = 0;
  }
  void addEdge(int u, int v, int cost, int b, int c) {
    if (b) {
      addEdge(u, T, b, cost);
      addEdge(S, v, b, 0);
      addEdge(u, v, c - b, cost);
      allFlow += b;
    }else addEdge(u, v, c, cost);
  }
  ll minCostFlow(int s, int t) {
    addEdge(t, s, oo, 0);
    return minCostMaxFlow(S, T, allFlow);
  }
};
