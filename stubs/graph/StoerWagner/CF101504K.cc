#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;

#define FOR(i, a, b) for(int i = (a); i < int(b); i++)
#define FORD(i, a, b) for(int i = (b)-1; i >= int(a); i--)
#define trav(i, v) for(auto &i : v)
#define has(c, e) ((c).find(e) != (c).end())
#define sz(c) int((c).size())
#define all(c) c.begin(), c.end()
#define debug(x) cerr << #x << ": " << x << endl;


struct mfset {
  vi par;
  mfset(int n) : par(n,-1) {}
  int find(int x) {
    return par[x] == -1? x : par[x] = find(par[x]);
  }
  void merge(int x, int y) {
    par[find(x)] = find(y);
  }
};

pair<ll, vi> StoerWagner(vector<vi>& g, int n) {
	int n1 = n;
  mfset P(n);
  vi v(n), a(n), w(n,0);
  iota(v.begin(), v.end(), 0);
	ll best = 10000000;
	vi cut;
	while (n > 1) {
		a[v[0]] = 1;
	  FOR(i, 1, n) {
			a[v[i]] = 0;
			w[i] = g[v[0]][v[i]];
		}
		int prev = v[0];
		FOR(i, 1, n) {
			int zj = -1;
      FOR(j, 1, n) if (!a[v[j]] && (zj < 0 || w[j] > w[zj])) zj = j;
			a[v[zj]] = 1;
			if (i == n - 1) {
				if (best > w[zj]){
					best = w[zj];
					cut.clear();
          FOR(k, 0, n1) if (P.find(k) == P.find(v[zj])) cut.push_back(k);
				}
				P.merge(prev, v[zj]);
        FOR(j, 0, n) g[v[j]][prev] = g[prev][v[j]] += g[v[zj]][v[j]];
				v[zj] = v[--n];
				break;
			}
			prev = v[zj];
      FOR(j, 1, n) if (!a[v[j]]) w[j] += g[v[zj]][v[j]];
		}
	}
	return {best, cut};
}

int main(){
    int n,m;
    cin >> n >> m;
    vector < vi > mat (n, vi (n,0));
    vector < vi > num (n, vi (n,0));
    int idx = 1;
    for (int i = 0; i < m; i++){
        int a,b,w; cin >> a >> b >> w;
        a--; b--;
        mat[a][b] = w;
        mat[b][a] = w;
        num[a][b] = num[b][a] = idx++;
    }
    pair < int, vi > p1;
    p1.first = 2e9;
    vector<int> ans;
    int pos;
    for (int i = 0; i < n; i++){
        vector < vi > mat2(n-1, vi (n-1, 0));
        vector < vi > num2(n-1, vi (n-1, 0));
        for (int j = 0, cont = 0; j < n; j++, cont++){
            if (j == i) {
                cont--;
                continue;
            }
            for (int k = 0, cont2 = 0; k < n; k++, cont2++){
                if (k == i) {
                    cont2--;
                    continue;
                }
                mat2[cont][cont2] = mat[j][k];
                num2[cont][cont2] = num[j][k];
            }
        }
        pair <int, vi> p = StoerWagner(mat2, n-1);
        if (p.first < p1.first) {
            vector<int> f(n-1,0);
            vector<int> curans;
            for (int i : p.second) f[i] = 1;
            for (int i : p.second){
                for(int j = 0; j < n-1; ++j) {
                    if(f[j] == 0 and num2[i][j] != 0) {
                        curans.push_back(num2[i][j]);
                    }
                }
            }
            swap(ans, curans);
            pos = i;
            p1 = p;
        }
    }
    cout << p1.first << endl;
    cout << ans.size() << endl;
    sort(ans.begin(), ans.end());
    for(int x : ans) cout << x << ' ';
    cout << endl;
}
