/**
 * Author: FAU
 * Date: ???
 * License: ???
 * Source: cyberFAUbia Templates NWERC 2013
 * Description: returns number of possibilities to create "word" from "start" with "rules", rules: rules[A]=={(B,C),(D,E),...}: rules of the form A->BC, A->DE
 * Status: tested
 */
#pragma once

const int maxN = 1024;
map<int,ll> cyk[maxN][maxN];

ll CYK(const vi &word, const map<int, vector<pii>> &rules, int start) {
  int N = sz(word);
  FOR(left,0,N) FOR(right,left,N) cyk[left][right].clear();

  FOR(i,0,N) cyk[i][i][ word[i] ] = 1;

  FOR(len,1,N+1) FOR(left,0,N-len+1) FOR(split,1,len)
  for (const auto &rule : rules) {
    int a = rule.first;
    for (const auto &r : rule.second) {
      int b, c; tie(b, c) = r;
      auto &lpart = cyk[left][left+split-1];
      auto &rpart = cyk[left+split][left+len-1];
      if (!has(lpart, b) || !has(rpart,c)) continue;
      cyk[left][left+len-1][a] += lpart[b] * rpart[c];
    }
  }
  return cyk[0][N-1][start];
}
