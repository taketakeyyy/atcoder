#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve(){
    // イメージ的には、左上、右上、左下、右下の4箇所に同じ文字がくる必要がある。
    // ただし、H(W)が奇数のとき、最後は2箇所が同じ文字になる必要がある。
    // 全文字数を数えて、4文字ずつ消費していって、全部使い切れたらOK
    ll H, W; cin >> H >> W;
    vector<string>A(H);
    map<char,ll> mp;
    rep(i,H) {
        cin >> A[i];
        for(char c: A[i]) {
            mp[c]++;
        }
    }

    ll h, w;
    h = H/2;
    w = W/2;
    ll num = h*w;
    for (auto& [key, val]: mp) {
        if (num==0) {
            break;
        }
        if (val>=4) {
            num -= val/4;
            val %= 4;
        }
    }
    if (num != 0) {
        cout << "No" << endl;
        return;
    }

    num = 0;
    if (H&1) {
        num += (W/2);
    }
    if (W&1) {
        num += (H/2);
    }

    for (auto& [key, val]: mp) {
        if (num==0) {
            break;
        }
        if (val>=2) {
            num -= val/2;
            val %= 2;
        }
    }
    if (num!=0) {
        cout << "No" << endl;
        return;
    }

    cout << "Yes" << endl;
    return;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}