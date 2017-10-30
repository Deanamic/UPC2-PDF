#include <bits/stdc++.h>
using namespace std;

const int MaxN = 200005;

struct Trie{
  static const int Alpha = 26;
  static const int first = 'a';
  int lst = 1;
  struct node{
    int nxt[Alpha] = {}, p = -1;
    char c;
    int endidx = -1;
    int SuffixLink;
  };
  vector<node> V;

  inline int getval(char c) {
    return c - first;
  }

  void CreateSuffixLink() {
    queue<int> q;
    for(q.push(0); q.size(); q.pop()) {
      int pos = q.front();
      if(!pos) V[pos].SuffixLink = -1;
      else {
        int val = getval(V[pos].c);
        int j = V[V[pos].p].SuffixLink;
        while(j > -1 && !V[j].nxt[val]) j = V[j].SuffixLink;
        if(j == -1) V[pos].SuffixLink = 0;
        else V[pos].SuffixLink = V[j].nxt[val];
      }
      for(int i = 0; i < Alpha; ++i) if(V[pos].nxt[i]) q.push(V[pos].nxt[i]);
    }
  }

  void init(vector<string> &v) {
    V.resize(MaxN);
    int id = 0;
    for(auto &s : v) {
      int pos = 0;
      for(char &c : s) {
        int val = getval(c);
        if(!V[pos].nxt[val]) {
          V[lst].p = pos;
          V[lst].c = c;
          V[pos].nxt[val] = lst++;
        }
        pos = V[pos].nxt[val];
      }
      V[pos].endidx = id++;
    }
    CreateSuffixLink();
  }

  vector<int>  find(string& word) {
    int pos = 0;
    vector<int> ans;
    for(auto &c : word) {
      if(V[pos].endidx != -1) ans.emplace_back(V[pos].endidx);
      int val = getval(c);
      while(pos > -1 && !V[pos].nxt[val]) pos = V[pos].SuffixLink;
      if(pos == -1) pos = 0;
      else pos = V[pos].nxt[val];
    }
    return ans;
  }
};


int main() {
  int n;
  cin >> n;
  vector<string> v(n);
  for(int i = 0; i < n; ++i) cin >> v[i];
  Trie T;
  T.init(v);
  string s1;
  cin >> s1;
  auto ans = T.find(s1);
  for(auto &i : ans) cout << i << endl;

}
