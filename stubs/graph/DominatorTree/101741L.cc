/*
 * Problem: Petrozavodsk winter 2017-2018 Problem L: https://codeforces.com/gym/101741
  * Find how many vertex an edge dominates in a graph
  * Benchmark 0.717s
  * You should provide a method with vi dominators(vvi g, int r) which calculates the dominator tree (i.e. the lowest dominator vertex for each vertex) where g is the adjacency matrix and r is the root
  */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll oo = 0x3f3f3f3f3f3f3f3fLL;
const int inf = 0x3f3f3f3f;

int X = 0;
#define FOR(i, a, b) for(int i = (a); i < int(b); i++)
#define FORD(i, a, b) for(int i = (b)-1; i >= int(a); i--)
#define has(c, e) ((c).find(e) != (c).end())
#define sz(c) int((c).size())
#define all(c) c.begin(), c.end()
#define N 400005

vi dominators(const vector<vi> &adj, int r) {
}

int sz[N];
struct edge {
  int id, u, v;
  ll w;
};

int dfsz(int u,int p, int n, vector<vector<int>>& adj) {
  sz[u] = (u < n ? 1 : 0);
  for(auto v : adj[u]) {
    sz[u] += dfsz(v, u, n, adj);
  }
  return sz[u];
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<edge> E;
  vector<vector<int>> adj(n);
  FOR(i, 0, m) {
    int u, v, w;
    cin >> u >> v >> w;
    --u, --v;
    adj[u].push_back(i);
    adj[v].push_back(i);
    E.push_back({i,u,v,w});
  }

  vector<ll> d(n,oo);
  d[0] = 0;
  priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
  for(pq.push({d[0],0}); pq.size();) {
    auto cur = pq.top();
    pq.pop();
    if(cur.first == d[cur.second]) {
      int u = cur.second;
      ll curw = d[u];
      for(int i : adj[u]) {
        int v = E[i].u ^ u ^ E[i].v;
        if(d[v] > curw + E[i].w) {
          d[v] = (curw + E[i].w);
          pq.push({d[v], v});
        }
      }
    }
  }
  vector<vector<int>> dadj(n+m);
  vector<int> ans(m,0);
  FOR(i, 0, m) {
    edge e = E[i];
    if(d[e.u] + e.w == d[e.v]) {
      dadj[e.u].push_back(n+e.id);
      dadj[n+e.id].push_back(e.v);
    }
    if(d[e.v] + e.w == d[e.u]) {
      dadj[e.v].push_back(n+e.id);
      dadj[n+e.id].push_back(e.u);
    }
  }
  auto dom = dominators(dadj, 0);
  vector<vector<int>> dTree(n+m);
  FOR(i, 0, m+n) {
    //cout << dom[i] << endl;
    if(dom[i] != -1 && dom[i] != n + m) {
      dTree[dom[i]].push_back(i);
    }
  }
  memset(sz, 0, sizeof(sz));
  dfsz(0,0,n,dTree);
  FOR(i, n, n+m) cout << sz[i] << ' ';
  cout << endl;
	return 0;
}
