/*
  Problem: https://codeforces.com/contest/993/problem/E
  Multiply takes 2 vectors (polynomials) and returns their product.
  The output doesn't exceed 1e18.
  Benchmark: 202ms
*/

#include "bits/stdc++.h"
using namespace std;

vector<long long> PolyMul(const vector<long long>& a, const vector<long long>& b) {
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
  int n, x;
  cin >> n >> x;
  vector<long long>a(n+1,0);
  a[0] = 1;
  int val = 0;
  long long curans = 0;
  long long cnt = 0;
  for(int i = 0; i < n; ++i) {
    int y;
    cin >> y;
    if(y < x) {
      val++;
      curans += (cnt*(cnt+1))/2;
      cnt = 0;
    }
    else {
      cnt++;
    }
    a[val]++;
  }
  curans += (cnt*(cnt+1))/2;
  auto b = a;
  reverse(b.begin(), b.end());
  auto ans = PolyMul(a, b);
  cout << curans;
  for(int i = 1; i <= n; ++i) {
    cout << ' ' << ans[i+n];
  }
  cout << endl;
}
