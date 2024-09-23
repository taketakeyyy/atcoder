#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N; cin >> N;
    vector<ll> H(N);
    for(ll i=0; i<N; i++) cin >> H[i];

    // 後ろから見ていく
    vector<ll> ans; ans.push_back(0);
    stack<ll> stk;
    for(ll i=N-2; i>=0; i--) {
        // 今回のビルの高さより、スタックの先頭から取り出したビルの高さが低ければ、スタックから取り除く
        while(!stk.empty()) {
            if (H[i+1] > stk.top()) {
                stk.pop();
                continue;
            }
            break;
        }
        stk.push(H[i+1]);
        ans.push_back(stk.size());
    }

    // 答え
    reverse(ans.begin(), ans.end());
    for(ll i=0; i<N; i++) cout << ans[i] << " ";
    cout << endl;
}


int main() {
    solve();
    return 0;
}