#define main XXX
#include "../content/contest/template.cpp"
#undef main
#include "../content/strings/PalindromeTree.h"

const int MAXLEN = 1000;

void find_palins(int node, vector<string>& ret) {
	if(node <= 1) {return;}
	assert(count(tree[tree[node].suffix].suffixof.begin(), tree[tree[node].suffix].suffixof.end(), node) == 1);
	find_palins(tree[node].suffix, ret);
	// cout << "at " << node << ", suffix " << tree[node].suffix << endl;
	string p;
	while(node > 1) {
		p += tree[node].c;
		assert(tree[tree[node].parent].children[tree[node].c] == node);
		node = tree[node].parent;
	}
	string rev(p);
	if(node == 0) {rev.pop_back();}
	reverse(rev.begin(), rev.end());
	p = p + rev;
	ret.push_back(p);
}

int main(int argc, char**argv) {
	if(argc > 1) {
		srand(atoi(argv[1]));
	}

	int strlen = rand() % MAXLEN;
	string s;
	FOR(i, 0, strlen) {
		if(rand() % 100 == 1) {
			string s2(s);
			reverse(s2.begin(), s2.end());
			s += s2;
			i += s2.size();
		} else {
			s.push_back('a' + (rand() % 26));
		}
	}
	build(s);
	FOR(i, 0, s.size()) {
		vector<string> palins;
		find_palins(pos2node[i], palins);
		vector<string> palins_naive;
		FOR(l, 1, i+2) {
			bool ok = true;
			FOR(m, 0, l/2) {
				if(s[i-l+1 + m] != s[i-m]) {
					ok = false;
					break;
				}
			}
			if(!ok) {continue;}
			string p;
			FOR(m, i-l+1, i+1) {
				p.push_back(s[m]);
			}
			palins_naive.push_back(p);
		}
		// cout << palins.size() << " - " << palins_naive.size() << endl;
		// FOR(j, 0, palins.size()) {
			// cout << palins[j] << endl;
		// }
		// cout << "---" << endl;
		// FOR(j, 0, palins_naive.size()) {
			// cout << palins_naive[j] << endl;
		// }
		assert(palins.size() == palins_naive.size());
		FOR(j, 0, palins.size()) {
			assert(palins[j] == palins_naive[j]);
		}
	}
	// cout << s << endl;

	return 0;
}
