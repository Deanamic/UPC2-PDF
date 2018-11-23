/**
 * Author: Dean
 * Source: Dean
 * License: CC0
 * Description: returns a 1 indexed array containing the length of the suffix which matches the prefix.
 * Time: $O(|S|)$
 * Status: Tested
 */

void KMP(vi& kmp, string& s) {
  kmp.assign(sz(s) + 1, -1);
  for (int i = st; i < s.size(); i++){
    int j = kmp[i];
    while(j >= 0 && s[i] != s[j]) j = kmp[j];
    kmp[i+1] = j + 1;
  }
}
