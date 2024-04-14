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
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll M; cin >> M;
    vector<string> S(3);
    for(ll i=0; i<3; i++) cin >> S[i];

    // 各Sの、数字numがあるインデックス
    vector SNumIndex(3, vector<vector<ll>>(10));
    for(ll s=0; s<3; s++) {
        for(ll i=0; i<M; i++) {
            ll n = S[s][i]-'0';
            SNumIndex[s][n].push_back(i);
        }
    }

    // 数字numを揃えられる最短時間を求める
    ll ans = INF;
    for(ll num=0; num<=9; num++) {
        // どのリールから止めるか？を全探索
        vector<ll> order; // リールの止める順番
        for(ll i=0; i<3; i++) order.push_back(i);
        sort(order.begin(), order.end());
        do {
            ll total = -1;
            ll now_idx = -1;
            for(ll o: order) {
                now_idx++;
                total++;
                auto it = lower_bound(SNumIndex[o][num].begin(), SNumIndex[o][num].end(), now_idx);
                if (it == SNumIndex[o][num].end()) {
                    total += M - now_idx;
                    auto it2 = lower_bound(SNumIndex[o][num].begin(), SNumIndex[o][num].end(), 0);
                    if (it2 == SNumIndex[o][num].end()) {
                        // numという数字が存在しない
                        total = INF;
                        break;
                    }
                    total += (*it2);//+1
                    now_idx = (*it2);
                }
                else {
                    total += (*it) - now_idx;
                    now_idx = (*it);
                }
            }
            ans = min(ans, total);
        } while(next_permutation(order.begin(), order.end()));
    }

    // 答え
    if (ans == INF) {
        cout << -1 << endl;
    }
    else {
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}