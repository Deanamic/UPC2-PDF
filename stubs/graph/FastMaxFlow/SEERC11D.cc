/*
 * Problem: SEERC 2011 Problem D, http://codeforces.com/gym/101464
 * Maxflow of a unit graph, note that if we use the scaling method we get a TLE
 * Benchmark 900ms
 * You should provide a method with addEdge() which creates an edge from u to v and specifies its cap, and maxflow which returns the max flow of the graph. The graph is represented in adj matrix G, and edge matrix arestes
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

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  freopen("D.in", "r", stdin);
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  int t = 0;
  while (cin >> n >> m and n != 0) {
    ++t;
    map<string, int> key;
    vector<int> np(n);
    for (int i = 0; i < n; ++i) {
      string s;
      int p;
      cin >> s >> p;
      key[s] = i;
      np[i] = p;
    }
    cin.ignore();
    vector< vector<int> > prob(m);
    for (int i = 0; i < m; ++i) {
      string s;
      getline(cin, s);
      stringstream ss(s);
      while (ss >> s) {
        prob[i].push_back(key[s]);
      }
    }
    int inf=0, sup=n+1;
    while (inf+1 != sup) {
      int mig=(inf+sup)/2;
      bool pot = false;
      for (int i = (1 << n) - 1; i >= 0 and not pot; --i) {
        int nc = 0;
        for (int j = 0; j < n; ++j) {
          if (i&(1 << j)) ++nc;
        }
        if (nc==mig) {
          vector<Edge> arestes;
          vector< vector<int> > G(n + m + 2);
          for (int j = 0; j < m; ++j) {
            for (int k = 0; k < prob[j].size(); ++k) {
              if (i&(1 << prob[j][k])) {
                addEdge(prob[j][k]+1, n+1+j, 1, G, arestes);
              }
            }
            addEdge(n+1+j,n+m+1,1,G,arestes);
          }
          int sum = 0;
          for (int j = 0; j < n; ++j) {
            if (i&(1 << j)) {
              sum += np[j];
              addEdge(0,j+1,np[j],G,arestes);
            }
          }
          if (sum == maxflow(0, n + m + 1, G, arestes)) pot = true;
        }
      }
      if (pot) {
        inf=mig;
      }
      else
        sup=mig;
    }
    cout << "Case #" << t << ": " << inf << endl;
  }
}
