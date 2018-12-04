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

struct SegTreeAp {
  struct Node {
    int sum, lazy, lazyAp;
    Node() {sum = 0; lazy = 0; lazyAp = 0;}
    Node(int val) {
      sum = val; lazy = 0; lazyAp = 0;
    }
    Node operator +(const Node& n) {
      Node ans;
      ans.sum = sum + n.sum;
      ans.lazy = ans.lazyAp = 0;
      return ans;
    }
  };
  vector<Node> S;
  SegTreeAp(int n) : S(4*n) {}

  void update(int id, int l, int r) {
    if(S[id].lazy) {
      S[id].sum += (r - l) * S[id].lazy;
      if(l + 1 != r) {
        S[id<<1].lazy += S[id].lazy;
        S[id<<1|1].lazy += S[id].lazy;
      }
      S[id].lazy = 0;
    }
    if(S[id].lazyAp) {
      int m = (l + r)>>1;
      S[id].sum += ((r - l) * (r - l + 1) / 2) * S[id].lazyAp;
      if(l + 1 != r) {
        S[id<<1].lazyAp += S[id].lazyAp;
        S[id<<1|1].lazyAp += S[id].lazyAp;
        S[id<<1|1].lazy += S[id].lazyAp * (m - l);
      }
      S[id].lazyAp = 0;
    }
  }

  void build(int id, int l, int r, vi& v) {
    if(l + 1 == r) {
      S[id] = Node(v[l]);
      return;
    }
    int m = (l + r)>>1;
    build(id<<1, l, m, v);
    build(id<<1|1, m, r, v);
    S[id] = S[id<<1] + S[id<<1|1];
  }

  void update(int id, int l, int r, int x, int y, int val, int prog) {
    update(id, l, r);
    if(l >= y || r <= x) return;
    if(l >= x && r <= y) {
      S[id].lazy += val + (l - x - 1)*prog;
      S[id].lazyAp += prog;
      update(id, l, r);
      return;
    }
    int m = (l + r)>>1;
    update(id<<1, l, m, x, y, val, prog);
    update(id<<1|1, m, r, x, y, val, prog);
    S[id] = S[id<<1] + S[id<<1|1];
  }

  Node query(int id, int l, int r, int x, int y) {
    update(id, l, r);
    if(l >= y || r <= x) return Node();
    if(l >= x && r <= y) return S[id];
    int m = (l + r)>>1;
    return query(id<<1, l, m, x, y) + query(id<<1|1, m, r, x, y);
  }
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n = 300;
  SegTreeAp S(n);
  vector<int> v(n,0);
  S.build(1, 0, n, v);
  int itMAX = 500;
  FOR(I, 0, itMAX) {
    int x = rand()%n;
    int y = rand()%n;
    int l = min(x,y);
    int r = max(x,y) + 1;
    int val = rand()%10000;
    int p = rand()%10000;
    S.update(1,0,n,l,r,val,p);
    FOR(i, l, r) {
      v[i] += val; val += p;
    }
    FOR(j, 0, itMAX) {
      int a = rand()%n;
      int b = rand()%n;
      int ql = min(a,b), qr = max(a,b) + 1;
      int sum = S.query(1, 0, n, ql, qr).sum;
      FOR(i, ql, qr) {
        sum -= v[i];
      }
      assert(sum == 0);
    }
  }
  cout << "WORKS" << endl;
	return 0;
}

