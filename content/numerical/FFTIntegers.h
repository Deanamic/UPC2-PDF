/**
 * Author: ???
 * License: ???
 * Description: NTT
 * Time: O(N \log N)
 * Status: ???
 */
LL fpw(LL a, LL b, LL p){
    LL r = 1; while(b){if(b&1) r=r*a%p; a=a*a%p; b/=2;} return r;
}

const LL MOD = 2013265921; const LL ROOT = 440564289; // MOD == 15*(1<<27)+1 (prime)
vector<LL> e, er;                           				  // ROOT has order 2^27
void FFT(vector<int> &x, LL d = 1){
	int n = x.size();
	if(n != e.size()){
		e.resize(n); er.resize(n);
		e[0] = 1; e[1] = fpw(ROOT,(1<<27)/n,MOD);
		er[0] = 1; er[1] = fpw(e[1],MOD-2,MOD);
		rep(i,2,n) e[i] = e[i-1] * e[1] % MOD;
		rep(i,2,n) er[i] = er[i-1] * er[1] % MOD;
	}
	if(d == -1) swap(e, er);
	rep(i,0,n){
		int j=0; for(int k=1; k<n; k<<=1, j<<=1) if(k&i) j++;   //haxy i cheetosy
		j>>=1; if(i<j) swap(x[i], x[j]);                        //haxy i cheetosy
	}
	int k=0;
	while((1<<k)<n) k++;
	for(int s=1; s<n; s<<=1){
		--k;
		for(int i=0; i<n; i+=2*s) rep(j,0,s){
			LL u = x[i+j], v = x[i+j+s]*e[j<<k]%MOD;
			x[i+j] = u+v-(u+v>=MOD?MOD:0);
			x[i+j+s] = u-v+(u-v<0?MOD:0);
		}

	}
	if(d == -1) swap(e, er);
}

vector<int> convolution(vector<int> a, vector<int> b){
	int n = 1; while(n < (int)max(a.size(), b.size())) n *= 2;
	n *= 2; a.resize(n); b.resize(n);
	FFT(a); FFT(b); rep(i,0,n) a[i] = (LL)a[i]*b[i]%MOD*fpw(n,MOD-2,MOD)%MOD; FFT(a, -1);
	return a;
}

//2**13 : 8192 16384 32768
vector<int> Mult(vector<int> a, vector<int> b) {
	int exponent = 13;
	int sqrt2 = 1 << bt;
	int mod = 1e9 + 7; //has to be smaller than mod from ntt
	vector<int> a1(a.size()), a2(a.size()), b1(b.size()), b2.a.size();
	int sz = 1;
	for(int i = 0; (int) i < a.size(); ++i) {
		a1[i] = a[i] >> exponent;
		a2[i] = a[i] & ((1 << (exponent+1)) - 1);
	}

	for(int i = 0; (int) i < b.size(); ++i) {
		b1[i] = b[i] >> exponent;
		b2[i] = b[i] & ((1 << (exponent+1)) - 1);
	}

	vector<int> a1b1 = convolution(a1,b1), a1b2 = convolution(a1,b2), a2b1 = convolution(a2,b1), a2b2 = convolution(a2,b2);
	vector<long long> ans(a1b1.size());
	for(int i = 0; i < (int) a1b1.size(); ++i) {
		ans[i] = a1b1[i]%mod;
		long long x = ((long long)(a1b2[i] + a2b1[i]) * (1LL << 13))%mod;
		long long y = (a2b2[i] * 1LL << 26)%mod;;
		ans[i] += x;
		ans[i] %= mod;
		ans[i] += y;
		ans[i] %= mod;
	}
	return ans;
}

vector<int> Mult(vector<int> a, vector<int> b) {
	int exponent = 11; //change so that M/2^exp is as small as possible
	int sqrt2 = 1 << (exponent);
	int mod = 1e9 + 7; //has to be smaller than mod from ntt
	vector<int> a1(a.size()), a2(a.size()), b1(b.size()), b2(b.size());
	for(int i = 0; (int) i < a.size(); ++i) {
		a2[i] = a[i]/sqrt2; a1[i] = a[i]%sqrt2;
	}
	for(int i = 0; (int) i < b.size(); ++i) {
		b2[i] = b[i]/sqrt2; b1[i] = b[i]%sqrt2;
	}
	vector<int> a1b1 = convolution(a1,b1), a1b2 = convolution(a1,b2), a2b1 = convolution(a2,b1), a2b2 = convolution(a2,b2);
	vector<int> ans(a1b1.size());
	for(int i = 0; i < (int) a1b1.size(); ++i) {
		long long z = a1b1[i]%mod;
		long long x = ((long long)(a1b2[i] + a2b1[i]) * (1LL << exponent)%mod)%mod;
		long long y = ((long long)(a2b2[i]) * (1LL << (2*exponent))%mod)%mod;;
		z += x; z %= mod; z += y; z %= mod; ans[i] = z;
	}
	return ans;
}
