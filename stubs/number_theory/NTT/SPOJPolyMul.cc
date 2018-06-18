/*
  Problem: https://www.spoj.com/problems/POLYMUL/
  Multiply takes 2 vectors (polynomials) and returns their product.
  The output doesn't exceed 1e18.
  Benchmark: 0.49
*/

#include "bits/stdc++.h"
using namespace std;

template<typename T>
vector<T> PolyMul(const vector<T>&  a,const vector<T>& b) {

}

int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<long long> a[2];
    for(int i = 0; i < 2; ++i) {
      for(int j = 0; j < n+1; ++j) {
        int x;
        cin >> x;
        a[i].push_back(x);
      }
    }
    auto ans = PolyMul(a[0],a[1]);
    for(int i = 0; i < 2*n+1; ++i) cout << ans[i] << ' ';
    cout << endl;
  }
}
