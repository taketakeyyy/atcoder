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
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


// 尺取法
void solve() {
    string S, T; cin >> S >> T;

    // x=0文字のとき
    vector<bool> ans((ll)T.size()+1,false);
    string S2 = S.substr(S.size()-T.size(), T.size()); // S'
    ll same_num = 0;  // S'とTの文字が一致している数
    for(ll i=0; i<(ll)T.size(); i++) {
        if (S2[i]==T[i] || S2[i]=='?' || T[i]=='?') same_num++;
    }
    if (same_num == (ll)T.size()) ans[0] = true;
    else ans[0] = false;

    // 尺取法
    {
        ll i = 0;
        for(ll x=1; x<=(ll)T.size(); x++) {
            if (S2[i]==T[i] || S2[i]=='?' || T[i]=='?') same_num--;
            if (S[i]==T[i] || S[i]=='?' || T[i]=='?') same_num++;

            if (same_num == (ll)T.size()) ans[i+1] = true;
            else ans[i+1] = false;
            i++;
        }
    }

    // 出力
    for(ll i=0; i<=(ll)T.size(); i++) {
        cout << ((ans[i]) ? "Yes" : "No") << endl;
    }
}


int main() {
    solve();
    return 0;
}