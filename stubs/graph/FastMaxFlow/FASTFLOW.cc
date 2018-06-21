/*
 * Problem: SPOJ FASTFLOW: https://vn.spoj.com/submit/FFLOW/ https://www.spoj.com/problems/FASTFLOW/
 * Maxflow of a undirected graph, note that the capacities go both ways
 * Note that for some reason the cases in the normal spoj server are weaker. (You should get TL with a normal DINICS implementation for the vietnamese case.
 * Benchmark 0.13ms
 * You should provide a method with addEdge() which creates an undirected edge from u to v and specifies its cap, and maxflow which returns the max flow of the graph. The graph is represented in adj matrix G, and edge matrix arestes
 */
#include<bits/stdc++.h>
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

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
  int n,m;
  cin >> n >> m;
  int s = 0, t = n-1;
  vector<vi> adj(n);
  vector<Edge> E;
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    --a, --b;
    addEdge(a,b,c,adj,E);
  }
  cout << maxflow(0,n-1,adj,E) << endl;
  return 0;
}
