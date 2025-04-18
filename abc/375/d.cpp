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
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;


void solve() {
    string S; cin >> S;
    ll N = S.size();

    // 各文字の累積和
    vector sumCnt(26, vector(N+1, 0LL));
    for(ll i=1; i<=N; i++) {
        for(ll a=0; a<26; a++) {
            if (S[i-1]-'A' == a) {
                sumCnt[a][i] = sumCnt[a][i-1] + 1;
            }
            else {
                sumCnt[a][i] = sumCnt[a][i-1] + 0;
            }
        }
    }

    // 真ん中に着目する
    ll ans = 0;
    for(ll i=1; i<N-1; i++) {
        for(ll a=0; a<26; a++) {
            ll left = sumCnt[a][i]; // [0,i-1]
            ll right = sumCnt[a][N] - sumCnt[a][i+1]; // [i+1, N-1]
            ans += left*right;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}