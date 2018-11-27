/**
 * Author: Emil Lenngren, Simon Lindholm
 * Date: 2011-11-29
 * Source:
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem, so that an expression of the type $(a\|\|b)\&\&(!a\|\|c)\&\&(d\|\|!b)\&\&...$ becomes true, or reports that it is unsatisfiable.
 * Negated variables are represented by bit-inversions (\texttt{\tilde{}x}).
 * Usage:
 *  TwoSat ts(number of boolean variables);
 *  ts.either(0, \tilde3); // Var 0 is true or var 3 is false
 *  ts.set_value(2); // Var 2 is true
 *  ts.at_most_one({0,\tilde1,2}); // <= 1 of vars 0, \tilde1 and 2 are true
 *  ts.solve(); // Returns true iff it is solvable
 *  ts.values[0..N-1] holds the assigned values to the vars
 * Time: O(N+E), where N is the number of boolean variables, and E is the number of clauses.
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

struct TwoSat {
	int N;
	vector<vi> gr;
	vi values; // 0 = false, 1 = true

	TwoSat(int n = 0) : N(n), gr(2*n) {}

	int add_var() { // (optional)
		gr.emplace_back();
		gr.emplace_back();
		return N++;
	}

	void either(int f, int j) {
		f = max(2*f, -1-2*f);
		j = max(2*j, -1-2*j);
		gr[f^1].push_back(j);
		gr[j^1].push_back(f);
	}
	void set_value(int x) { either(x, x); }

	void at_most_one(const vi& li) { // (optional)
		if (sz(li) <= 1) return;
		int cur = ~li[0];
		FOR(i,2,sz(li)) {
			int next = add_var();
			either(cur, ~li[i]);
			either(cur, next);
			either(~li[i], next);
			cur = ~next;
		}
		either(cur, ~li[1]);
	}

	vi val, comp, z; int time = 0;
	int dfs(int i) {
		int low = val[i] = ++time, x; z.push_back(i);
		trav(e, gr[i]) if (!comp[e])
			low = min(low, val[e] ?: dfs(e));
		++time;
		if (low == val[i]) do {
			x = z.back(); z.pop_back();
			comp[x] = time;
			if (values[x>>1] == -1)
				values[x>>1] = !(x&1);
		} while (x != i);
		return val[i] = low;
	}

	bool solve() {
		values.assign(N, -1);
		val.assign(2*N, 0); comp = val;
		FOR(i,0,2*N) if (!comp[i]) dfs(i);
		FOR(i,0,N) if (comp[2*i] == comp[2*i+1]) return 0;
		return 1;
	}
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  //freopen("SPO.IN", "r", stdin);
  //freopen("SPO.OUT", "w", stdout);
  int n, m;
  cin >> n >> m;
  TwoSat T(n);
  FOR(i, 0, m) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    int xx = x/2;
    int yy = y/2;
    if((x&1) == 0) xx = ~xx;
    if((y&1) == 0) yy = ~yy;
    //cout << xx << ' ' << yy << endl;
    T.either(xx, yy);
  }
  if(!T.solve()) cout << "NIE" << endl;
  else {
    FOR(i, 0, sz(T.values)) cout << (2*i) + (1-T.values[i]) + 1 << '\n';
  }
}

