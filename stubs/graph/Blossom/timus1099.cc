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
struct Blossom{
	int n,m,h,t,W,tot;
  vector<int> fir,la,ne,F,mat,pre,tp,q,vs;
	Blossom (int x,int y){
    n = x; m = y; W = tot = 0;
    fir = F = mat = pre = tp = q = vs = vector<int> (x+1,0);
    la = ne = vector<int> (2*y + 10,0);
  }
	void add(int x, int y){
	  ins(x,y), ins(y,x);
	}
	void ins(int x,int y){ la[++tot] = y; ne[tot] = fir[x]; fir[x] = tot;}
	int fd(int x){ return F[x] ? F[x] = fd(F[x]) : x;}
	int lca(int u,int v){
		for(++W;; u = pre[mat[u]], swap(u,v))
			if(vs[u = fd(u)] == W)return u;
			else vs[u] = u ? W : 0;
	}
	void aug(int u,int v){
		for (int w; u; v = pre[u=w]) w = mat[v], mat[mat[u]=v] = u;
	}
	void blo(int u,int v,int f){
		for (int w;fd(u)^f;u = pre[v=w]) {
      pre[u]=v;
      if(!(F[u])) F[u] = f;
      if(!(F[w=mat[u]])) F[w] = f;
      if(!(tp[w]^1)) tp[q[++t]=w] = -1;
    }
	}
	int bfs(int u){
		int x,E,i;
	  FOR(i, 1, n+1) tp[i] = F[i] = 0;
		for(--tp[q[h=t=1]=u]; h <= t ;u = q[++h])
		for(i = fir[u]; i; i = ne[i]) if(!tp[E = la[i]]){
			if(!mat[E]) return aug(E,u),1;
			pre[E] = u, ++tp[E], --tp[q[++t]=mat[E]];
      } else if ((tp[E]^1)&&(fd(u)^fd(E))) blo(u, E, x = lca(u,E)), blo(E,u,x);
		return 0;
	}
	int solve(){
		int i, an=0;
	  FOR(i, 1, n+1) if(!mat[i]) an += bfs(i);
		return an;
	}
	void out(){
    FOR(i, 1, n+1) if(mat[i] && i < mat[i]) cout << i << ' ' << mat[i] << endl;
	}
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n;
  cin >> n;
  Blossom B(n, 1e5+10);
  int x, y;
  while(cin >> x >> y) {
    B.add(x,y);
  }
  cout << B.solve() << endl;
  B.out();
return 0;
}
