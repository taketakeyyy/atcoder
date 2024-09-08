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
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll H, W, Q; cin >> H >> W >> Q;
    vector<ll> R(Q), C(Q);
    vector<set<ll>> RWall(H);
    for(ll i=0; i<H; i++) {
        for(ll j=0; j<W; j++) RWall[i].insert(j);
    }
    vector<set<ll>> CWall(W);
    for(ll w=0; w<W; w++) {
        for(ll h=0; h<H; h++) CWall[w].insert(h);
    }

    ll ans = H*W;
    for(ll q=0; q<Q; q++) {
        ll r, c; cin >> r >> c;
        r--; c--;

        if (RWall[r].contains(c)) {
            // (r,c)のみの1マス爆破
            ans--;
            RWall[r].erase(c);
            CWall[c].erase(r);
        }
        else {
            // 上下左右に見て爆破
            {// 左右
                auto it = RWall[r].lower_bound(c);
                ll rrm = -1;
                ll lrm = -1;
                if (it != RWall[r].end()) {
                    // 右爆破準備
                    ans--;
                    rrm = *it;
                }
                if (it != RWall[r].begin()) {
                    // 左爆破準備
                    ans--;
                    it--;
                    lrm = *it;
                }

                if (rrm != -1) {
                    // 右爆破
                    RWall[r].erase(rrm);
                    CWall[rrm].erase(r);
                }
                if (lrm != -1) {
                    // 左爆破
                    RWall[r].erase(lrm);
                    CWall[lrm].erase(r);
                }
            }
            {// 上下
                auto it = CWall[c].lower_bound(r);
                ll rrm = -1;
                ll lrm = -1;
                if (it != CWall[c].end()) {
                    // 下爆破準備
                    ans--;
                    rrm = *it;
                }
                if (it != CWall[c].begin()) {
                    // 上爆破準備
                    ans--;
                    it--;
                    lrm = *it;
                }

                if (rrm != -1) {
                    // 下爆破
                    CWall[c].erase(rrm);
                    RWall[rrm].erase(c);
                }
                if (lrm != -1) {
                    // 上爆破
                    CWall[c].erase(lrm);
                    RWall[lrm].erase(c);
                }

            }
        }
    }
    cout << ans << endl;

}


int main() {
    solve();
    return 0;
}