#include <bits/stdc++.h>
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

#define VEI(w,e) (E[e].u ^ E[e].v ^ w)
#define CAP(w,e) ((E[e].u == w) ? E[e].cap[0] - E[e].flow : E[e].cap[1] + E[e].flow)
#define ADD(w,e,f) E[e].flow += ((E[e].u == w) ? (f) : (-(f)))

struct Edge{ int u, v; ll cap[2], flow; };
vi d, act;

bool bfs(int s, int t, vector<vi>& adj, vector<Edge>& E, ll lim = 1) {
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
      ll inc = dfs(VEI(u,e),t,min(bot,CAP(u,e)),adj,E);
      if (inc) {
        ADD(u, e, inc);
        return inc;
      }
    }
  }
  return 0;
}

ll maxflow(int s, int t, vector<vi>& adj, vector<Edge>& E, int F = 0) {
  trav(e, E) e.flow = 0;
  ll flow = 0, bot;
  for(int lim = (1<<F); lim >= 1;lim>>=1) {
    while(bfs(s,t,adj,E,lim)) {
      act = vi(adj.size(), 0);
      while ((bot = dfs(s, t, oo, adj, E))) flow += bot;
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

ll anss = 0;
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

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vi> adj(n);
  vector<Edge> E;
  FOR(i, 0, m) {
    int a,b,c;
    cin >> a >> b >> c;
    --a, --b;
    addEdge(a,b,adj,E,c,c);
  }
  vi par;
  vector<vector<ll>> d;
  gomory_hu(adj, E, par, d);
  cout << anss << endl;

 	int best = 0;
	vi res(n);
	for (int i = 0; i < n; ++i) {
		res[i] = i;
	}
	for (int i = 0; i < 1; ++i) {
		vi order;
		order.push_back(i);
		vi used(n, 0);
		used[i] = true;
		int score = 0;
		while (sz(order) != n) {
			int best = -1, index = -1;
			for (int j = 0; j < n; ++j) {
				if (!used[j] && d[order.back()][j] > best) {
					best = d[order.back()][j];
					index = j;
				}
			}
			score += best;
			order.push_back(index);
			used[index] = true;
		}

		if (score > best) {
			best = score;
			res = order;
		}
	}
	for (int i = 0; i < res.size(); ++i) {
		printf("%d ", res[i] + 1);
	}
	printf("\n");
}

