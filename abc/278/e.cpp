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


void solve() {
    ll H, W, N, h, w; cin >> H >> W >> N >> h >> w;
    vector<vector<ll>> A(H, vector<ll>(W));
    map<ll,ll> mp;
    for(ll i=0; i<H; i++) {
        for(ll j=0; j<W; j++) {
            cin >> A[i][j];
            mp[A[i][j]]++;
        }
    }

    // 全走査
    map<ll,ll> erase_mp;
    for(ll k=0; k<=H-h; k++) {
        for(ll l=0; l<=W-w; l++) {
            if (l==0) {
                erase_mp = map<ll,ll>();
                for(ll i=k; i<k+h; i++) {
                    for(ll j=l; j<l+w; j++) {
                        erase_mp[A[i][j]]++;
                    }
                }
            }
            else {
                // 尺取法
                for(ll i=k; i<k+h; i++) {
                    erase_mp[A[i][l-1]]--;
                    erase_mp[A[i][l+w-1]]++;
                }
            }

            // 答えを出力
            ll ans = N;
            for(ll i=1; i<=N; i++) {
                if (mp[i]-erase_mp[i] == 0) ans--;
            }
            cout << ans << " ";
        }
        cout << endl;
    }
}


int main() {
    solve();
    return 0;
}