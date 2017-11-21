/**
 * Author: Dean
 * License: CC0
 * Description: Builds an Ahocorasick Trie, with suffix links
 * Time: O(n + m + z)
 * Status: Tested http://www.spoj.com/problems/STRMATCH/
 * Usage: This is an offline Algorithm, Pass the vector of patterns to Trie.init(), find function returns the number of times each string appears, two patterns can be equal
 */

const int MaxM = 200005;

struct Trie{
    static const int Alpha = 26;
    static const int first = 'a';
    int lst = 1;
    struct node{
        int nxt[Alpha] = {}, p = -1;
        char c;
        vector<int> end;
        //bitset<MaxN> bitmask;
        int SuffixLink;
		int cnt = 0;
    };
    vector<node> V;
	int num;
	stack<int> reversebfs;
    inline int getval(char c) {
        return c - first;
    }

    void CreateSuffixLink() {
        queue<int> q;
        for(q.push(0); q.size(); q.pop()) {
            int pos = q.front();      
			reversebfs.push(pos);
			for(int i = 0; i < Alpha; ++i) {
				if(V[pos].nxt[i]) q.push(V[pos].nxt[i]);
				else if(!pos || !V[pos].p) {
					V[pos].SuffixLink = 0;
				    V[pos].nxt[i] = V[0].nxt[i];
				}
				else {
					int val = getval(V[pos].c);
					int j = V[V[pos].p].SuffixLink;
					V[pos].SuffixLink = V[j].nxt[val];
					V[pos].nxt[i] = V[V[pos].SuffixLink].nxt[i];
				}
            }
        }
    }

    void init(vector<string> &v) {
        V.resize(MaxM);
		num = v.size();
        int id = 0;
        for(auto &s : v) {
            int pos = 0;
            for(char &c : s) {
                int val = getval(c);
                if(!V[pos].nxt[val]) {
                    V[lst].p = pos; V[lst].c = c; V[pos].nxt[val] = lst++;
                }
                pos = V[pos].nxt[val];
            }
            V[pos].end.emplace_back(id++);
        }
        CreateSuffixLink();
    }

    vector<int> find(string& word) {
        int pos = 0;
        vector<int> ans(num, 0); 
        for(auto &c : word) {
            int val = getval(c);
            pos = V[pos].nxt[val];
			V[pos].cnt++; //We count the times we reach each node, and then do a reverse propagation
        }
		for(;reversebfs.size();reversebfs.pop()) { 
        	int	x = reversebfs.top(); //When we process x, we know we have been there V[x].cnt times;
        	for(int i : V[x].end) ans[i] += V[x].cnt;
        	if(V[x].SuffixLink != -1) V[V[x].SuffixLink].cnt += V[x].cnt; 
        }
        return ans;
    }
};
