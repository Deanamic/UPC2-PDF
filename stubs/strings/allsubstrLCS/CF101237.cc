/* Author: Cesc
 * Date: 27/11/18
 * Description: Calculates the LCS of s and t[i..j]
 * Status:
 * Time: O(|S|^2)
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

vector<vi> allSubstringLCS(string& s, string& t) {
  int n = sz(s), m = sz(t);
  vector<vi> M(2, vi(m));
  iota(all(M[1]), 0);
  FOR(i, 0, n) {
    int k = -1;
    FOR(j, 0, m) {
      if (s[i] == t[j]) {
        M[i&1][j] = k;
        k = M[(i+1)&1][j];
      } else {
        M[i&1][j] = max(M[(i+1)&1][j],k);
        k = min(M[(i+1)&1][j],k);
      }
    }
  }
  vector<vi> ans(m, vi(m));
  FOR(i, 0, m) {
    int cur = 0;
    FOR(j, i, m) {
      if (M[(n+1)&1][j] < i) ++cur;
      ans[i][j] = cur;
    }
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  string s, t;
  cin >> s >> t;
  auto ans = allSubstringLCS(s,t);
  int m = sz(t);
  FOR(i, 0, m) {
    FOR(j, i, m) {
      cout << ans[i][j] << ' ';
    }
    cout << endl;
  }
}

