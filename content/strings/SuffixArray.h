/* Suffix Array + LCP
 lcp (x,y) = min(lcp(x,x+1),lcp(x+1,x+2)...lcp(y-1,y)) to answer queries with RMQ O(1)
 Complexity:
 	- Time:
		Build O(nlogn)
		LCP O(logn)
	- Memory
		Build O(nlogn) (Can be optimised as in B you only use the previous row to compute one row. But then you cannot do lcp
Source: PDF UPC
Tested on https://www.codechef.com/problems/TASTR

NOTE: It is not necessary to use raddixsort if the O(nlog^2 n) fits the time limit, one can just use stl sort
*/

struct SF {
  pair<ll, ll> ord;
  ll id;
  bool operator<(const SF& s) const { return ord < s.ord; }
};
 
 
 
ll lcp(ll x, ll y, vector < vector < ll > > &B, ll N, ll step) {
  if (x == y) return N - x;
  ll res = 0;
  for (ll i = step - 1; i >= 0 and x < N and y < N; --i)
    if (B[i][x] == B[i][y]) { x += 1<<i; y += 1<<i; res += 1<<i; }
  return res;
}

 
 
 
void raddixSort(vector < SF > & A, vector < vector <ll > > & B, vector < ll > &times, vector < ll > & pos, vector < SF > & L2, ll N) {
  ll k = max(N, 256LL);
  for (ll i = 0; i < k + 2; ++i) times[i] = 0;
  for (ll i = 0; i < N; ++i)
    times[A[i].ord.second + 1]++;
  pos[0] = 0;
  for (ll i = 1; i < k + 2; ++i)
    pos[i] = pos[i - 1] + times[i - 1];
  for (ll i = 0; i < N; ++i)
    L2[pos[A[i].ord.second + 1]++] = A[i];
 
  for (ll i = 0; i < k + 2; ++i)
    times[i] = 0;
  for (ll i = 0; i < N; ++i)
    times[L2[i].ord.first + 1]++;
  pos[0] = 0;
  for (ll i = 1; i < k + 2; ++i)
    pos[i] = pos[i - 1] + times[i - 1];
  for (ll i = 0; i < N; ++i)
    A[pos[L2[i].ord.first + 1]++] = L2[i];
}
 
 
 
void compute_suffix_array(vector < SF > & A, vector<vector<ll> > & B, ll N, string & S, ll &step) {
	ll MAXN = 3000005; //millor posar numero gran que algo en funcio de N pq peta
	vector < SF > L2(MAXN);
	vector < ll > pos(MAXN + 2,0), times(MAXN + 2,0);
	A.resize(N); B.resize(1); B[0].resize(N);
	for (ll i = 0; i < N; ++i) B[0][i] = S[i];
	step = 1;
	for (ll b = 0, pw = 1; b < N; ++step, pw<<=1) {
		for (ll i = 0; i < N; ++i) {
			A[i].ord.first = B[step - 1][i];
			A[i].ord.second = i + pw < N ? B[step - 1][i + pw] : -1;
			A[i].id = i;
		}
		raddixSort(A, B, times, pos, L2, N); //sort(A.begin(), A.end());
		B.resize(step + 1); B[step].resize(N);
		b = B[step][A[0].id] = 1;
		for (ll i = 1; i < N; ++i) {
			if (A[i - 1] < A[i]) ++b;
			B[step][A[i].id] = b;
		}
	}
}
