/**
 * Author: Stjepan Glavina
 * Source: https://github.com/stjepang/snippets/blob/master/min_rotation.cpp
 * Description: Finds the lexicographically smallest rotation of a string.
 * Time: O(N)
 * Status: Tested. http://www.spoj.com/status/ns=20639111
 * Usage:
 *  rotate(v.begin(), v.begin()+min_rotation(v), v.end());
 */
#pragma once

int min_rotation(string s) {
	int a=0, N=sz(s); s += s;
	FOR(b,0,N) FOR(i,0,N) {
		if (a+i == b || s[a+i] < s[b+i]) {b += max(0, i-1); break;}
		if (s[a+i] > s[b+i]) { a = b; break; }
	}
	return a;
}
