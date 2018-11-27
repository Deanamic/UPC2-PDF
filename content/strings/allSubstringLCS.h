/**
 * Author: Cesc
 * Date: 2018-11-27
 * Description: Calculates the LCS of s and t[i..j]
 * Status: Tested
 * Time: O(|S|^2)
 */

vector<vi> allSubstringLCS(string& s, string& t) {
  int n = sz(s), m = sz(t);
  vector<vi> M(2, vi(m));
  iota(all(M[1]), 0);
  FOR(i, 0, n) {
    int k = -1;
    FOR(j, 0, m) {
      if (s[i] == t[j]) {
        M[i&1][j] = k; k = M[(i+1)&1][j];
      } else {
        M[i&1][j] = max(M[(i+1)&1][j],k); k = min(M[(i+1)&1][j],k);
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
