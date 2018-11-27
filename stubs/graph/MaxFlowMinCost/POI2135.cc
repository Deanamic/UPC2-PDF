#include<iostream>
#include <algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll oo = 0x3f3f3f3f3f3f3f3fLL;

#define FOR(i, a, b) for(int i = (a); i < int(b); i++)
#define FORD(i, a, b) for(int i = (b)-1; i >= int(a); i--)
#define trav(i, v) for(auto &i : v)
#define has(c, e) ((c).find(e) != (c).end())
#define sz(c) int((c).size())
#define all(c) c.begin(), c.end()
#define debug(x) cerr << #x << ": " << x << endl;

struct MCMFwithBound {
  struct edge {
    int to, rev; ll cap, cost;
    edge(int to, ll cap, ll cost, int rev): to(to), rev(rev), cap(cap), cost(cost) {}
  };
  int N;
  vector<vector<edge> > G;
  vi inq;
  vector<ll> dis;
  vi preve, prevv;
  void addEdge(int u, int v, ll cap, ll cost) {
    G[u].push_back({v, cap, cost, sz(G[v])});
    G[v].push_back({u, 0, -cost, sz(G[u]) - 1});
  }
  ll minCostMaxFlow(int s, int t, int flow) {
    ll res = 0;
    while (flow > 0) {
      queue<int> q;
      dis = vector<ll>(N, oo);
      inq = vi(N, 0);
      dis[s] = 0, inq[s] = 1;
      q.push(s);
      while (!q.empty()) {
        int cur = q.front(); q.pop();
        inq[cur] = 0;
        for (int i = 0; i < (int)G[cur].size(); ++i) {
          edge &e = G[cur][i];
          if (e.cap && dis[cur] + e.cost < dis[e.to]) {
            dis[e.to] = dis[cur] + e.cost;
            preve[e.to] = i;
            prevv[e.to] = cur;
            if (!inq[e.to]) {inq[e.to] = 1; q.push(e.to);}
          }
        }
      }
      if (dis[t] == oo) return -1;
      ll d = flow;
      for (int cur = t; cur != s; cur = prevv[cur]) {
        d = min(d, G[prevv[cur]][preve[cur]].cap);
      }
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
  void init(int n) {
    N = 2*n + 10;
    G.resize(N);
    prevv = preve = vi(N);
    S = n + 1, T = n + 2;
    allFlow = 0;
  }
  void addEdge(int u, int v, ll cap, ll cost, ll bound) {
    if (bound) {
      addEdge(u, T, bound, cost);
      addEdge(S, v, bound, 0);
      addEdge(u, v, cap - bound, cost);
      allFlow += bound;
    }else addEdge(u, v, cap, cost);
  }
  ll minCostFlow(int s, int t, ll flow = -1) {
    if(flow == -1) addEdge(t, s, oo, 0), flow = allFlow;
    return minCostMaxFlow(S, T, flow);
  }
};

int main()
{
  int m,n;
  MCMFwithBound mcmf;
  cin >> n >> m;
  int s = 0;
  int t = n+1;
  mcmf.init(n+2);
  while(m--){
    int u,v,w;
    cin >> u >> v >> w;
    mcmf.addEdge(u,v,1,w);
    mcmf.addEdge(v,u,1,w);
  }
  mcmf.addEdge(0,1,2,0,0);
  mcmf.addEdge(n,n+1,2,0,0);
  int ans = mcmf.minCostMaxFlow(s,t,-1);
  cout<< ans <<endl;
  return 0;
}
