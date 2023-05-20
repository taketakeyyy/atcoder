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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0, -1, -1, 1, 1};
vector<ll> vx = { 0, 1, 0, -1, -1, 1, -1, 1};


void solve() {
    ll H, W; cin >> H >> W;
    vector<string> S(H);
    for(ll i=0; i<H; i++) cin >> S[i];

    auto is_inside = [&](ll h, ll w) {
        return (h>=0 && h<H && w>=0 && w<W);
    };

    auto search = [&](ll h, ll w) -> vector<pair<ll,ll>>{
        const string snuke = "snuke";
        for(ll vi=0; vi<8; vi++) {
            ll nh = h + vy[vi];
            ll nw = w + vx[vi];

            bool is_found = true;
            vector<pair<ll,ll>> ans;
            ans.push_back({h,w});
            for(ll i=1; i<5; i++) {
                if (!is_inside(nh, nw)) {
                    is_found = false;
                    break;
                }
                if (S[nh][nw] == snuke[i]) {
                    ans.push_back({nh,nw});
                    nh += vy[vi];
                    nw += vx[vi];
                    continue;
                }
                is_found = false;
                break;
            }

            if (is_found) {
                return ans;
            }
        }
        vector<pair<ll,ll>> ans;
        return ans;
    };

    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            if (S[h][w] == 's') {
                auto ans = search(h, w);
                if (ans.size() != 0) {
                    // 出力
                    for(ll i=0; i<5; i++) {
                        auto[ansh, answ] = ans[i];
                        cout << ansh+1 << " " << answ+1 << endl;
                    }
                    return;
                }
            }
        }
    }
}


int main() {
    solve();
    return 0;
}