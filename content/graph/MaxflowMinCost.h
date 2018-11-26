/**
 * Author: Dean
 * Date: 24/11/18
 * License: CC0
 * Source: http://www.voidcn.com/article/p-fmuiuclg-vs.html
 * Description: Computes mincost maxflow using spfa algorithm, can change to BF with negative edges or dijkstra if only positive. Init takes the number of vertes, addedge ads a directed edge. MincostMaxflow returns a pair (flow,cost)
 * Time: O(|V||E|F) where F is the flow
 * Status: Tested. http://www.spoj.com/problems/GREED/
 */

struct MCMF
{
  typedef int Fval;
  const int INF = 0x7f7f7f7f;
  struct edge {
    int from,to;
    Fval cap,flow,cost;
    edge(int u,int v, Fval c, Fval f, Fval co):from(u),to(v),cap(c),flow(f),cost(co){}
  };
  int n,m;
  vector<edge>edges;
  vector<vi> g;
  vi inq, d, p, a;
  void init(int n){
    this->n=n;
    g = vector<vi>(n);
    a = p = vi(n);
    edges.clear();
  }
  void addEdge(int from,int to,int cap,int cost){
    g[from].push_back(sz(edges));
    edges.push_back(edge(from,to,cap,0,cost));
    g[to].push_back(sz(edges));
    edges.push_back(edge(to,from,0,0,-cost));
  }
  bool spfa(int s,int t,int &flow,int &cost){
    d = vi(n,INF);
    inq = vi(n,0);
    d[s]=0;inq[s]=1;p[s]=0;a[s]=INF;
    deque<int> q; //can use queue instead of deque
    q.push_front(s);
    while(!q.empty()){
      int u=q.front();q.pop_front();
      inq[u]=0;
      for(int i=0;i<g[u].size();i++){
        edge &e=edges[g[u][i]];
        if(e.cap>e.flow&&d[e.to]>d[u]+e.cost){
          d[e.to]=d[u]+e.cost;
          p[e.to]=g[u][i];
          a[e.to]=min(a[u],e.cap-e.flow);
          if(!inq[e.to]){
            if(q.size() && d[e.to] < d[q.front()]) q.push_front(e.to);
            else q.push_back(e.to);
          }
          inq[e.to]=1;
        }
      }
    }
    if(d[t]==INF)return 0;
    flow+=a[t];
    cost+=d[t]*a[t];
    for(int u=t;u!=s;u=edges[p[u]].from){
      edges[p[u]].flow+=a[t];
      edges[p[u]^1].flow-=a[t];
    }
    return 1;
  }
  pair<Fval,Fval> MincostMaxflow(int s,int t){
    Fval flow=0, cost=0;
    while(spfa(s,t,flow,cost));
    return {flow,cost};
  }
};
