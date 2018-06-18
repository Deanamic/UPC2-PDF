/**
 * Author: Dean
 * Date: 18-06-18
 * License: CC0
 * Source: KACTL
 * Description: Number theoretic transform. Can be used for convolutions modulo specific nice primes
 * of the form $2^a \times b+1$, where the convolution result has size at most $2^a$.
 * For other primes/integers, use two different primes and combine with CRT.
 * May return negative values. Consider Bruteforcing for small N, 10times slower than FFT
 * Time: O(N \log N)
 * Status: Tested
 */

#pragma once

#include "ModPow.h"

const ll mod[] = {(119<<23)+1, (5<<25)+1, 7<<26|1, 479<<21|1, 483<<21|1};
const ll root[] = {3,3,3,3,5};

template<typename T>
void ntt(T* x, T* temp, T* roots, int N, int skip, ll mod) {
	if (N == 1) return;
	int n2 = N>>1;
	ntt(x     , temp, roots, n2, skip<<1, mod);
	ntt(x+skip, temp, roots, n2, skip<<1, mod);
	FOR(i,0,N) temp[i] = x[i*skip];
	FOR(i,0,n2) {
		ll s = temp[i<<1], t = temp[i<<1|1] * roots[skip*i];
		x[skip*i] = (s + t) % mod; x[skip*(i+n2)] = ((s - t) % mod + mod) %mod;
	}
}

template<typename T>
void ntt(vector<T>& x, ll mod, ll root,  bool inv = false) {
	ll e = modpow(root, (mod-1) / sz(x), mod);
	if (inv) e = modpow(e, mod-2, mod);
	vector<T> roots(sz(x), 1), temp = roots;
	FOR(i,1,sz(x)) roots[i] = roots[i-1] * e % mod;
	ntt(&x[0], &temp[0], &roots[0], sz(x), 1, mod);
}

template<typename T>
vector<T> conv(vector<T> a, vector<T> b, ll mod, ll root) {
	int s = sz(a) + sz(b) - 1; if (s <= 0) return {};
	int L = s > 1 ? 32 - __builtin_clz(s - 1) : 0, n = 1 << L;
	a.resize(n); ntt(a, mod, root);
	b.resize(n); ntt(b, mod, root);
	vector<T> c(n); ll d =  modpow(n, mod-2, mod);
	FOR(i,0,n) c[i] = a[i] * b[i] % mod * d % mod;
	ntt(c, mod, root, true); c.resize(s); return c;
}

template<typename T>
vector<T> PolyMul(const vector<T>&  a,const vector<T>& b) {
  vector<T> ans1 = conv(a, b, mod[1], root[1]);
  vector<T> ans2 = conv(a, b, mod[2], root[2]);
  for(int i = 0; i < sz(ans1); ++i) ans1[i] = (chinese(ans1[i], mod[1], ans2[i], mod[2]));
  return ans1;
}
