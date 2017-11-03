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
