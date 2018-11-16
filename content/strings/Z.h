/**
 * Author: Dean
 * Date: 2017-11-12
 * Source: ??
 * Description: Computes the longest prefix which ends at the i-th position
 * Status: tested
 */

vector<int> Z(string &s) {
    int n = s.size();
    int L, R;
    L = R = 0;
    vector<int> Z(n, 0);
    for (int i = 1; i < n; ++i){
        if (i < R) Z[i] = min(Z[i-L], R-i);
        else Z[i] = 0;
        while (Z[i] + i < n and s[Z[i]] == s[i+Z[i]]) ++Z[i];
        if (i+Z[i] > R){
            L = i;
            R = i + Z[i];
        }
    }
}
