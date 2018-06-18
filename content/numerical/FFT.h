/**
 * Author: Dean
 * Date: 18-06-18
 * Source: Erichto Codeforces submission.
 * Description: Fast Fourier transform to multiply polynomials. Can be modified to multiply modulus x. Error around max_ans/1e15 or max_ans/2.5e18 for double/long double.
 * Time: O(N \log N)
 * Status: Tested
 */

using LL = long long;
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
using LD = double;
struct C {
  LD x,y;
  C operator *(const C& c) const { return C{x*c.x-y*c.y, x*c.y+y*c.x}; }
  void operator +=(const C& c) { x+=c.x, y+=c.y;}
};

void FFT(vector<C> & a, int rev) {
	const int N = a.size();
	for(int i = 1, k = 0; i < N; ++i) {
		for(int bit = N / 2; (k ^= bit) < bit; bit /= 2);
		if(i < k) swap(a[i], a[k]);
	}
	for(int len = 1, who = 0; len < N; len *= 2, ++who) {
		static vector<C> t[30];
		vector<C> & om = t[who];
		if(om.empty()) {
			om.resize(len);
			const LD ang = 2 * acosl(0) / len;
			FOR(i, 0, len) om[i] = i%2 || !who ?
        C{cos(i*ang), sin(i*ang)} : t[who-1][i/2];
		}
		for(int i = 0; i < N; i += 2 * len)
			FOR(k, 0, len) {
        const C x = a[i+k], y = a[i+k+len]
          * C{om[k].x, om[k].y * rev};
				a[i+k] += y;
				a[i+k+len] = C{x.x - y.x, x.y - y.y};
			}
	}
	if(rev == -1) FOR(i, 0, N) a[i].x /= N;
}

template<typename T> //add ll mod to header
vector<T> PolyMul(const vector<T> & a, const vector<T> & b, bool split = false) {
	if(a.empty() || b.empty()) return {};
	int n = a.size() + b.size();
	vector<T> ans(n - 1);
	n = 1 << (32 - __builtin_clz(int(a.size() + b.size() - 1)));
	auto speed = [&](const vector<C> & w, int i, int k) {
		int j = i ? n - i : 0, r = k ? -1 : 1;
		return C{w[i].x + w[j].x * r, w[i].y
				- w[j].y * r} * (k ? C{0, -0.5} : C{0.5, 0});
	};
	if(!split) {
		vector<C> in(n), done(n);
		FOR(i, 0, a.size()) in[i].x = a[i];
		FOR(i, 0, b.size()) in[i].y = b[i];
		FFT(in,  1);
		FOR(i, 0, n) done[i] = speed(in, i, 0) * speed(in, i, 1);
		FFT(done, -1);
		FOR(i, 0, ans.size()) ans[i] = is_integral<T>::value ?
      llround(done[i].x) : done[i].x; //ans  %= mod;
	//FOR(i,0,ans.size())err=max(err,abs(done[i].x-ans[i]));
	}
	else { // Split big INTEGERS into pairs a1*M+a2,
		const T M = 1<<10; // where M = sqrt(max_absvalue).
		vector<C> t[2]; // This version is 2.2-2.5 times slower.
		FOR(x, 0, 2) {
			t[x].resize(n);
			auto & in = x ? b : a; // below use (in[i]-big) if normalized
			FOR(i, 0, in.size()) t[x][i]=C{LD(in[i]%M), LD(in[i]/M)};
			FFT(t[x], 1);
		}
		T mul = 1;
		for(int s = 0; s < 3; ++s, mul *= M) { //mul %= mod;
			vector<C> prod(n);
			FOR(x, 0, 2) FOR(y, 0, 2) if(x + y == s) FOR(i, 0, n)
				prod[i] += speed(t[0], i, x) * speed(t[1], i, y);
			FFT(prod, -1);
			FOR(i, 0, ans.size()) ans[i] += llround(prod[i].x)*mul;
                          //ans[i] += (llround(prod[i].x)%mod)*mul, ans[i] %= mod;
		}
	}
	return ans;
}
