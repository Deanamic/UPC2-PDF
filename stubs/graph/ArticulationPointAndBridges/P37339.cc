/*
 * Problem: Jutge.org P37339
  * Find bridges in a graph
  * Benchmark: Unknown
  * You should provide a method void dominators(vvi adj, vector<edge> E, vi art, vi bridges) which returns to vectors by reference signaling that the i-th vertex is a articulation point, or the ith edge a bridge.
  */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll oo = 0x3f3f3f3f3f3f3f3fLL;

#define FOR(i, a, b) for(int i = (a); i < int(b); i++)
#define FORD(i, a, b) for(int i = (b)-1; i >= int(a); i--)
#define has(c, e) ((c).find(e) != (c).end())
#define sz(c) int((c).size())
#define all(c) c.begin(), c.end()

struct Edge{
  int u, v;
};

void ArticulationPointandBridges(vector<vi>& adj, vector<Edge> E, vi& articulation, vi& bridges) {
}

void solve(int n, int m) {
  vector<vi> adj(n);
  vector<Edge> E;
  FOR(i, 0, m) {
    int u, v;
    cin >> u >> v;
    if(u > v) swap(u,v);
    adj[u].push_back(sz(E));
    adj[v].push_back(sz(E));
    E.push_back({u,v});
  }
  vi a, b;
  ArticulationPointandBridges(adj,E,a,b);
  vector<Edge> ans;
  FOR(i, 0, m) if(b[i]) ans.push_back(E[i]);
  sort(ans.begin(), ans.end(), [](Edge a, Edge b) {
      return (a.u == b.u ? a.v < b.v : a.u < b.u);
    });
  cout << sz(ans) << '\n';
  FOR(i, 0, sz(ans)) cout << ans[i].u << ' ' << ans[i].v << (i+1 == sz(ans) ? "" : "  ");
  cout << '\n';
  FOR(i, 0, 10) cout << '-';
  cout << '\n';
}
int main() {
  int n, m;
  while(cin >> n >> m) solve(n, m);
}
