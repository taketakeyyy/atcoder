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


void __solve() {
    // TLE lol
    string X; cin >> X;
    const ll MAX_ANS = 500010;
    vector<ll> ans(MAX_ANS);

    while(X.size()!=0) {  // 最大 MAX_ANS 回
        string tmpX = X;
        ll i = 0;
        while(tmpX.size()!=0) {  // 平均 (MAX_ANS+1)/2 回
            ans[i] += tmpX[tmpX.size()-1] - '0';
            if (ans[i] >= 10) {
                ans[i+1] += ans[i]/10;
                ans[i] = ans[i] % 10;
            }
            tmpX = tmpX.substr(0, tmpX.size()-1);
            i++;
        }
        X = X.substr(0, X.size()-1);
    }
    for(ll i=0; i<MAX_ANS; i++) {
        if (ans[i] >= 10) {
            ans[i+1] += ans[i]/10;
            ans[i] = ans[i] % 10;
        }
    }


    // 出力
    bool is_still_zero = true;
    for(ll i=MAX_ANS-1; i>=0; i--) {
        if (is_still_zero && ans[i]==0) continue;
        if (ans[i] != 0) is_still_zero = false;
        printf("%lld", ans[i]);
    }
    printf("\n");
}


void solve() {
    string X; cin >> X;
    const ll MAX_ANS = 500010;
    vector<ll> ans(MAX_ANS);

    // 累積和作成
    vector<ll> r(X.size()+1, 0);
    for(ll i=X.size()-1; i>=0; i--) {
        r[i] = r[i+1] + (X[X.size()-1-i]-'0');
    }

    // ans作成
    for(ll i=0; i<X.size(); i++) {
        ans[i] += r[i];

        ans[i+1] += ans[i]/10;
        ans[i] = ans[i]%10;
    }

    // 出力
    bool is_first_zero = true;
    for(ll i=MAX_ANS; i>=0; i--) {
        if (ans[i]==0 && is_first_zero) continue;
        if (ans[i]!=0) is_first_zero = false;
        if (!is_first_zero) {
            printf("%lld", ans[i]);
        }
    }
    printf("\n");
}

int main() {
    solve();
    return 0;
}