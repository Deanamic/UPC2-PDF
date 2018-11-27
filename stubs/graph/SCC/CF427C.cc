
/**
 * Author: Dean
 * License: CC0
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Time: O(E + V)
 * Status: Tested in a 2Sat Problem
 * Usage: Use addedge to add edges in a directed graph(will also add reverse edges), after calling Kosaraju comp will save the component number of each vertex ordered by topological order.
 */
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

struct SCC {
  vi comp, m;
  vector<vector<int>> adj[2];
  stack<int> st;
  int c;
  int n;
  SCC(int n) : comp(n), m(n,0), c(0), n(n) {
    adj[0] = adj[1] = vector<vector<int>>(n);
  }

  void addEdge(int u, int v) {
    adj[0][u].push_back(v);
    adj[1][v].push_back(u);
  }

  void dfs(int u, int t) {
    m[u] = 1;
    for(int v : adj[t][u]) if(!m[v]) dfs(v,t);
    if(t) comp[u] = c;
    else st.push(u);
  }

  void kosaraju() {
    for(int i = 0; i < n; ++i) if(!m[i]) dfs(i,0);
    m = vi(n,0);
    for(;st.size();st.pop()) if(!m[st.top()]) dfs(st.top(),1), c++;
  }
};
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n;
  cin >> n;
  vector<ll> cost(n);
  FOR(i, 0, n) cin >> cost[i];
  int m;
  cin >> m;
  SCC G(n);
  FOR(i, 0, m) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    G.addEdge(x,y);
  }
  G.kosaraju();
  vector<ll> ans(G.c,oo);
  FOR(i, 0, n) ans[G.comp[i]] = min(ans[G.comp[i]], cost[i]);
  ll sum = 0;
  FOR(i, 0, G.c) sum += ans[i];
  ll ways = 1;
  vi cnt(G.c,0);
  FOR(i, 0, n) cnt[G.comp[i]] += (cost[i] == ans[G.comp[i]]);
  FOR(i, 0, G.c) ways = (ways*cnt[i])%(1000000007);
  cout << sum << ' ' << ways << endl;
}

