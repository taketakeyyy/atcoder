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
    ll H, W; cin >> H >> W;
    vector<string> S(H);
    for(ll i=0; i<H; i++) cin >> S[i];

    auto is_inside = [&](ll h, ll w) -> bool {
        return (h>=0 && h<H && w>=0 && w<W);
    };

    // 01-BFS
    vector visited(H, vector<bool>(W, false));
    vector punched(H, vector<bool>(W, false)); // パンチの起点にした堀か？
    visited[0][0] = true;
    deque<tuple<ll,ll,ll>> deq;
    deq.push_back({0,0,0});
    while(!deq.empty()) {
        auto[h, w, cost] = deq.front(); deq.pop_front();
        if (h==H-1 && w==W-1) {
            cout << cost << endl;
            return;
        }

        for(ll vi=0; vi<4; vi++) {
            ll nh = h + vy[vi];
            ll nw = w + vx[vi];
            if (!is_inside(nh, nw)) continue;

            if (S[nh][nw] == '.') {
                // 道の場合
                if (visited[nh][nw]) continue;
                visited[nh][nw] = true;
                // コスト0移動する
                deq.push_front({nh,nw,cost});
            }
            else {
                // 堀の場合
                if (punched[nh][nw]) continue;
                punched[nh][nw] = true;
                // 堀をパンチするとそこを起点に4マス堀を破壊する
                // 破壊は4パターンすべて試し、新規に破壊した堀へコスト+1移動する
                for(ll i=-1; i<=1; i++) {
                    for(ll j=-1; j<=1; j++) {
                        ll nnh = nh + i;
                        ll nnw = nw + j;
                        if (!is_inside(nnh, nnw)) continue;
                        if (visited[nnh][nnw]) continue;
                        if (S[nnh][nnw] == '.') continue;
                        visited[nnh][nnw] = true;
                        deq.push_back({nnh,nnw,cost+1});
                    }
                }
            }
        }
    }
}


int main() {
    solve();
    return 0;
}