/**
 * Author: Dean
 * Date: 24/11/18
 * License: CC0
 * Source: Folklore
 * Description: Computes minimum distance in presence of negative edges, to detect negative cycles use a stack and put every element in the stack if an element appears N times it has a cycle. (if we put T(n+m) elements in the queue there is a big chance we have a neg cycle.
 * Time: O(VE), although it is faster in most cases
 * Status:
 */

ll spfa(int s, int t, vector<pair<int,ll>>& adj){
  int n = sz(adj);
  vector<ll> d(n, oo);
  vi inq(n,0);
  d[s]=0; inq[s]=1;
  deque<int> q; //can use queue or stack instead of deque
  q.push_front(s);
  while(!q.empty()){
    int u = q.front(); q.pop_front();
    inq[u]=0;
    FOR(i, 0, adj[u]){
      ll w = adj[u][i].second;
      int v = adj[u][i].first;
      if(d[v] > d[u] + w){
        d[v]=d[u] + w;
        if(!inq[v]){
          if(q.size() && d[e.to] < d[q.front()]) q.push_front(e.to);
          else q.push_back(e.to);
        }
        inq[v]=1;
      }
    }
  }
  return d[t];
}
