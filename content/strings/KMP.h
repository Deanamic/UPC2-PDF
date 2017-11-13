/**
 * Author: ???
 * Source: PDF UPC
 * License: ???
 * Description: string matching
 * Time: $O(P + T)$ where $P$ is the length of the pattern, $T$ is length of the text
 * Status: Tested
 */
string s, p; cin >> s >> p;
vector<int> pi(p.size() + 1, 0);
int k = 0;
for (int i = 2; i <= p.size(); ++i) {
	while (k > 0 and p[i - 1] != p[k]) k = pi[k];
	if (p[i - 1] == p[k]) ++k;
	pi[i] = k;
}
k = 0;
for (int i = 0; i < s.size(); ++i) {
	while (k > 0 and s[i] != p[k]) k = pi[k];
	if (p[k] == s[i]) ++k;
	if (k == p.size()) k = pi[k]; //Matching
}
