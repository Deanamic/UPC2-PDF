/**
 * Author: Dean
 * Date: 2017-11-12
 * License: CC0
 * Source: ???
 * Description: Range minimum query
 * Usage: Call function build and then use query to return the smallest value, ST stores the index to the value.
 * Time: $<O(N\log N), O(1)>$
 * Status: Tested?
 */

struct SparseTable {
    vector<vector<int> > ST;
    vector<int> P;
    vector<int> v;
    int N;
    int MAXLOG = 0;

    void build(int n, const vector<int>& V){
        N = n;
        v = V;
        while ((1 << MAXLOG) <= N) ++MAXLOG;
        ST = vector<vector<int> > (N, vector<int> (MAXLOG));
        P = vector<int> (N+1);
        int LOG = 0;
        for(int i = 1; i < N + 1; ++i){
            P[i] = ((1<<LOG) > i ?  LOG-1 : ++LOG-1);
        }

        for(int i = 0; i < N; ++i) ST[i][0] = i;
        for (int j = 1; j < MAXLOG; ++j) {
            for (int i = 0; i + (1 << j) - 1 < N; ++i) {
                if (V[ST[i][j - 1]] < V[ST[i + (1 << (j - 1))][j - 1]])
                     ST[i][j] = ST[i][j - 1];
                else
                     ST[i][j] = ST[i + (1 << (j - 1))][j - 1];
            }
        }
    }

    int query(int l, int r){
        int LOG = P[r-l+1];
        return min(v[ST[l][LOG]], v[ST[r - (1 << LOG) + 1][LOG]]);
    }
};
