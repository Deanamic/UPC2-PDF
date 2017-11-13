/**
 * Author: FAU
 * License: ???
 * Description: call with String str of length n, returns: r[0..2*n-2],r[i] radius of longest palindrome with center i/2 in str
 * Time: O(n)
 * Status:
 * Usage:
 */
#pragma once

void manacher(int n, char *str, int *r) {
	r[0] = 0;
	int p = 0;
	FOR(i, 1, 2*n-1) {
		r[i] = (p/2 + r[p] >= (i+1)/2) ? min(r[2*p - i], p/2 + r[p] - i/2) : 0;
		while (i/2 + r[i] + 1 < n && (i+1)/2 - r[i] - 1 >= 0
		&& str[i/2 + r[i] + 1] == str[(i+1)/2 - r[i] - 1]) r[i]++;
		if (i/2 + r[i] > p/2 + r[p]) p = i;
	}
	// FOR(i,0,2*n-1) r[i] = r[i]*2 + !(i&1); // change radius to diameter
}
