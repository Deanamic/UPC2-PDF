/**
 * Author: Simon Lindholm
 * Date: 2015-02-11
 * License: CC0
 * Source: Wikipedia
 * Description: Fast integration using an adaptive Simpson's rule.
 * Status: tested on https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4146
 * Usage:
	double z, y;
	double h(double x) { return x*x + y*y + z*z <= 1; }
	double g(double y) { ::y = y; return quad(h, -1, 1); }
	double f(double z) { ::z = z; return quad(g, -1, 1); }
	double sphereVol = quad(f, -1, 1), pi = sphereVol*3/4;
 */
#pragma once

typedef double d;
template<typename F>
d simpson(F f, d a, d b) {
	d c = (a+b) / 2;
	return (f(a) + 4*f(c) + f(b)) * (b-a) / 6;
}
template<typename F>
d rec(F f, d a, d b, d eps, d S) {
	d c = (a+b) / 2;
	d S1 = simpson(f, a, c);
	d S2 = simpson(f, c, b), T = S1 + S2;
	if (abs (T - S) <= 15*eps || b-a < 1e-10)
		return T + (T - S) / 15;
	return rec(f, a, c, eps/2, S1) + rec(f, c, b, eps/2, S2);
}
template<typename F>
d quad(F f, d a, d b, d eps = 1e-8) {
    return rec(f, a, b, eps, simpson(f, a, b));
}
