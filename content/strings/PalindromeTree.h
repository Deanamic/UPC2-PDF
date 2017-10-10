/**
 * Author: Michael Sammler
 * License: CC0
 * Description: Palindrome Tree for string s
 * Time: O(sz(s)) for building
 * Status: Tested on Codeforeces, CERC10 problem C
 * Usage:
 */
#pragma once

const int maxN = 1000010; // at least sz(s) + 3
struct Node {
	int suffix;
	int len;
	map<char, int> children;

	// not needed for construction, add if needed
	char c;
	int parent;
	vector<int> suffixof;
};

int nodeid;
Node tree[maxN]; // 0: -1 root, 1: empty string
int pos2node[maxN]; // not needed for construction

int add(int parent, char c) {
	if(has(tree[parent].children, c)) {
		return tree[parent].children[c];
	}
	int newid = nodeid++;
	tree[newid].suffix = -1;
	tree[newid].len = tree[parent].len + 2;
	tree[newid].parent = parent;
	tree[newid].c = c;
	tree[parent].children[c] = newid;
	return newid;
}

void build(string& s) {
	nodeid = 2;
	tree[0].parent = -1;
	tree[0].len = -1;
	tree[1].parent = -1;
	tree[0].suffixof.push_back(1);
	int cur = 0;
	FOR(i, 0, s.size()) {
		int newn = -1;
		while(1) {
			int curlen = tree[cur].len;
			if(i-1-curlen >= 0 && s[i-1-curlen] == s[i]) {
				newn = add(cur, s[i]);
				break;
			}
			cur = tree[cur].suffix;
		}
		pos2node[i] = newn;
		if(tree[newn].suffix != -1) {
			cur = newn;
			continue;
		}
		if(cur == 0) {
			tree[newn].suffix = 1;
		} else {
			do {
				cur = tree[cur].suffix;
			} while(i-1-tree[cur].len < 0
					|| s[i-1-tree[cur].len] != s[i]);
			tree[newn].suffix = tree[cur].children[s[i]];
		}
		tree[tree[newn].suffix].suffixof.push_back(newn);
		cur = newn;
	}
}
