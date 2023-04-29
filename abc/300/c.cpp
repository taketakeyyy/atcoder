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
    vector<string> C(H);
    for(ll h=0; h<H; h++) cin >> C[h];

    auto is_inside = [&](ll h, ll w) {
        return (0<=h && h<H && 0<=w && w<W);
    };

    auto f = [&](ll h, ll w) {
        // 左上方向探索
        ll d1 = 0;
        {
            ll nh = h-1;
            ll nw = w-1;
            ll d = 1;
            while(1) {
                if (!is_inside(nh,nw)) break;
                if (C[nh][nw] == '#') {
                    nh--; nw--;
                    d1 = d++;
                    continue;
                }
                break;
            }
        }
        // 左下方向探索
        ll d2 = 0;
        {
            ll nh = h+1;
            ll nw = w-1;
            ll d = 1;
            while(1) {
                if (!is_inside(nh,nw)) break;
                if (C[nh][nw] == '#') {
                    nh++; nw--;
                    d2 = d++;
                    continue;
                }
                break;
            }
        }
        // 右上方向探索
        ll d3 = 0;
        {
            ll nh = h-1;
            ll nw = w+1;
            ll d = 1;
            while(1) {
                if (!is_inside(nh,nw)) break;
                if (C[nh][nw] == '#') {
                    nh--; nw++;
                    d3 = d++;
                    continue;
                }
                break;
            }
        }
        // 右下方向探索
        ll d4 = 0;
        {
            ll nh = h+1;
            ll nw = w+1;
            ll d = 1;
            while(1) {
                if (!is_inside(nh,nw)) break;
                if (C[nh][nw] == '#') {
                    nh++; nw++;
                    d4 = d++;
                    continue;
                }
                break;
            }
        }
        return min(d1, min(d2, min(d3, d4)));
    };

    // O(NHW)の全探索でOK
    ll N = min(H,W);
    vector<ll> S(N+1);
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            if (C[h][w] == '.') continue;
            ll d = f(h,w);
            S[d]++;
        }
    }

    // 出力
    for(ll i=1; i<=N; i++) {
        cout << S[i] << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}