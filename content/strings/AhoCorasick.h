#include <bits/stdc++.h>
using namespace std;

struct Trie{
  const int Alpha = 26;
  const int first = 'a';
  const int MaxN = 200000;
  int lst = 0;
  struct node{
    int nxt[Alpha] = {}, p = -1;
    char c;
    vector<string> end;
    int SuffixLink;
  };
  vector<node> V(MaxN);

  static inline int getval(char c) {
    return c - first;
  }

  void CreateSuffixLink() {
    queue<int> q;
    for(q.push(0); q.size(); q.pop()) {
      int pos = q.front();
      int val = getval(V[pos].c);
      if(!pos) V[pos].SuffixLink = -1;
      else {
        int j = V[V[pos].pare].SuffixLink;
        while(j > -1 && !V[j].nxt[val]) j = V[j].SuffixLink;
        if(j == -1) V[pos].SuffixLink = 0;
        else V[pos].SuffixLink = V[j].nxt[val];
      }
    }
  }

  void init(vector<string> &v) {
    for(auto &s : v) {
      int pos = 0;
      for(char &c : s) {
        int val = getval(c);
        if(!V[pos].nxt[val]) {
          V[pos].nxt[val] = lst++;
          V[lst].p = pos;
          V[lst].c = c;
        }
        pos = V[pos].nxt[val];
      }
      V[pos].end.push_back(s);
    }
    CreateSuffixLink();
  }
}
int main() {


}
