/**
 * Author: Michael Sammler
 * Date: 2017-11-06
 * License: CC0
 * Source: folklore
 * Description: Some useful functions for segment trees
 * Time: $O(\log N)$
 */
#pragma once

const ll tot = (1 << 19); // bigger than N
ll N = 1; // ...
ll minv[tot * 2];
ll lazy[tot * 2];

void init(ll x, ll l, ll r) {
	if(l >= N) return;
	if(r - l <= 1) {
		minv[x] = 1; // ...
		lazy[x] = 0;
		return;
	}
	init(2*x, l, (l+r)/2);
	init(2*x+1, (l+r)/2, r);
	minv[x] = min(minv[2*x], minv[2*x+1]);
	lazy[x] = 0;
}

// propagates lazy, msut be called before recursing
void prop(ll x, ll l, ll r) {
	if(r - l <= 1) return;
	minv[2*x] += lazy[x];
	lazy[2*x] += lazy[x];
	minv[2*x+1] += lazy[x];
	lazy[2*x+1] += lazy[x];
	lazy[x] = 0;
}

// add v to [a, b)
void sadd(ll x, ll l, ll r, ll a, ll b, ll v) {
	if(b <= l || r <= a) return;
	if(a <= l && r <= b) {
		minv[x] += v;
		lazy[x] += v;
		return;
	}
	prop(x, l, r);
	sadd(2*x, l, (l+r)/2, a, b, v);
	sadd(2*x+1, (l+r)/2, r, a, b, v);
	minv[x] = min(minv[2*x], minv[2*x+1]);
}

// finds the lowest value res, such that all values
// in [res, end) are >= 2 (condition can be adjusted)
ll squery(ll x, ll l, ll r, ll end) {
	if(end <= l) return end;
	if(minv[x] >= 2) return l; // ...
	if(r - l <= 1) {
		return r;
	}
	prop(x, l, r);
	if(minv[2*x+1] >= 2) { // ...
		return squery(2*x, l, (l+r)/2, end);
	}
	ll rend = squery(2*x+1, (l+r)/2, r, end);
	if(rend > (l+r)/2) return rend;
	return squery(2*x, l, (l+r)/2, end);
}

void example() {
	ll a = 0, b = 1;
	init(1, 0, tot);
	sadd(1, 0, tot, a, b, -2);
	ll res = squery(1, 0, tot, a);
}

struct SegmentTree {
  
}
