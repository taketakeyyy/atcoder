#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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
    vector<string> Ss;
    Ss.push_back(S);

    string s1 = S;
    for(int i=0; i<S.size()-1; i++) {
        string s2;
        s2 = s1.substr(1);
        s2 += s1[0];
        Ss.push_back(s2);
        s1 = s2;
    }

    sort(Ss.begin(), Ss.end());

    // 出力
    cout << Ss[0] << endl;
    cout << Ss.back() << endl;
}


int main() {
    solve();
    return 0;
}