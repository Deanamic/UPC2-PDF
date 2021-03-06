/*
 * Problem: uoj262537 http://uoj.ac/problem/79
 * Find a maximum matching
 * Benchmark 0.138s n <= 500
 * output the size of the max matching and output for each vertex its matching, output 0 if unmatched. Input is n m and m lines of (u,v)
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll oo = 0x3f3f3f3f3f3f3f3fLL;

#define FOR(i, a, b) for(int i = (a); i < int(b); i++)
#define FORD(i, a, b) for(int i = (b)-1; i >= int(a); i--)
#define trav(i, v) for(auto &i : v)
#define has(c, e) ((c).find(e) != (c).end())
#define sz(c) int((c).size())
#define all(c) c.begin(), c.end()
#define debug(x) cerr << #x << ": " << x << endl;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
	return 0;
}
