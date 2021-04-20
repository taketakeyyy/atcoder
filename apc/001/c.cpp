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
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

bool judge(string const& origin, string const& ret, ll& l, ll& mid, ll& r) {
    if (ret == "Vacant") {
        return true;
    }
    else if (origin!=ret) {
        if (mid%2==0) {
            // 右側に空席があって男女の順番がずれた
            r = mid; mid = (l+r)/2;
        }
        else {
            // 男女の順番はずれてない
            l = mid; mid = (l+r)/2;
        }
    }
    else {
        if (mid%2==0) {
            // 男女の順番はずれてない
            l = mid; mid = (l+r)/2;
        }
        else {
            // 男女の順番がずれた
            r = mid; mid = (l+r)/2;
        }
    }
    return false;
}

void solve() {
    ll N; cin >> N;
    cout << 0 << endl;
    string ret; cin >> ret;
    if (ret == "Vacant") {
        return;
    }
    string origin = ret;
    ll l=0; ll r=N-1;
    ll mid = (l+r)/2;
    while(r-l!=1) {
        cout << mid << endl;
        string ret; cin >> ret;
        if (judge(origin, ret, l, mid, r)) {
            return;
        }
    }
    // rかlのどちらかが答え
    cout << l << endl;
    cin >> ret;
    if (ret=="Vacant") {
        return;
    }
    cout << r << endl;
    cin >> ret;
}


int main() {
    solve();
    return 0;
}