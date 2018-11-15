/*
  Problem:https://codeforces.com/gym/101480 Problem F
  Multiply takes 2 vectors (polynomials) and returns their product Modulus 1e6 + 3.
  Benchmark: 1107ms, current fft has to use split or long double for AC
*/

include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll oo = 0x3f3f3f3f3f3f3f3fLL;

#define FOR(i, a, b) for(int i = (a); i < int(b); i++)
#define FORD(i, a, b) for(int i = (b)-1; i >= int(a); i--)
#define has(c, e) ((c).find(e) != (c).end())
#define sz(c) int((c).size())
#define all(c) c.begin(), c.end()

const int M = 1e6 + 3;

template<typename T>
vector<T> PolyMul(const vector<T> & a, const vector<T> & b, ll mod) {
}


ll fact[400010];
ll invfact[400010];

ll mod_pow(ll n, ll e) {
    ll res = 1;
    ll cur = n;
    while(e) {
        if(e&1) res = (res * cur) % M;
        cur = (cur * cur) % M;
        e >>= 1;
    }
    return res;
}

int main() {
    ll n, a, b, c;
    cin >> n >> a >> b >> c;
    ll res = 0;
    fact[0] = 1;
    invfact[0] = 1;
    FOR(i, 1, 2*n+2) {
        fact[i] = (fact[i-1] * i) % M;
        invfact[i] = mod_pow(fact[i], M-2);
    }

    FOR(i, 1, n+1) {
        ll l; cin >> l;
        if(i == 1) continue;
        ll add = l;
        add = (add * fact[2*n-i-2]) % M;
        add = (add * invfact[n-i]) % M;
        add = (add * invfact[n-2]) % M;
        add = (add * mod_pow(b, n-i)) % M;
        add = (add * mod_pow(a, n-1)) % M;
        res = (res + add) % M;
    }
    FOR(i, 1, n+1) {
        ll t; cin >> t;
        if(i == 1) continue;
        ll add = t;
        add = (add * fact[2*n-i-2]) % M;
        add = (add * invfact[n-i]) % M;
        add = (add * invfact[n-2]) % M;
        add = (add * mod_pow(a, n-i)) % M;
        add = (add * mod_pow(b, n-1)) % M;
        res = (res + add) % M;
    }
    vector<ll> va(n+1,0), vb(n+1,0);
    FOR(i, 2, n+1) {
        va[i] = (mod_pow(a, n-i) * invfact[n-i]) % M;
        vb[i] = (mod_pow(b, n-i) * invfact[n-i]) % M;
    }
    auto con = PolyMul(va, vb, M, true);
    FOR(k, 4, 2*n+1) {
        ll add = 0;
        add = (add + (con[k])) % M;
        add *= (c * fact[2*n-k]) % M;
        add %= M;
        res = (res + add) % M;
    }
    cout << res << endl;
}
