/**
 * Author: jz33 & Michael
 * Date: ???
 * License: ???
 * Source: https://github.com/jz33/LeetCodeSolutions/blob/master/308%20Range%20Sum%20Query%202D%20-%20Mutable.java
 * Description: Computes sums a[i,j] for all i<I, j<J, and increases single elements a[i,j].
 * Status: tested on http://www.spoj.com/problems/MATSUM/
 * Time: $O(\log^2 N)$.
 */
#pragma once

struct FT2 {
    ll R, C;
    vector<vector<ll>> tree;

	// note r+1 & c+1
    NumMatrix(ll r, ll c) : R(r), C(c), tree(r+1, vector<ll>(c+1)) { }

    void update(int row, int col, int diff) {
        for(int i = row+1;i<=R;i += (i & -i))
            for(int j = col+1;j<=C;j += (j & -j))
                tree[i][j] += diff;
    }

    int sum(int row, int col) {
        int r = 0;
        // Not i >= 0
        for(int i = row;i > 0;i -= (i & -i))
            for(int j = col;j > 0;j -= (j & -j))
                r += tree[i][j];
        return r;
    }
};
