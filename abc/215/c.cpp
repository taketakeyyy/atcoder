#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/b)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    string S; cin >> S;
    ll K; cin >> K;

    sort(S.begin(), S.end());

    vector<string> Ss;
    do {
        Ss.push_back(S);
    }while(next_permutation(S.begin(), S.end()));

    sort(Ss.begin(), Ss.end());

    cout << Ss[K-1] << endl;
}


int main() {
    solve();
    return 0;
}