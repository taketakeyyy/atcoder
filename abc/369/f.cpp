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


class LIS {
    /** 最長増加部分列(LIS)
     * Args:
     *  vector<ll> A: 配列
     *
     * Notes:
     *  計算量はO(NlogN)
     *  LISを求めるのにはdp1のみでよいが、dp2も構築しといたほうが便利なのでこうしている。
     **/
    public:
        ll answer;  // LISの長さ
        vector<pair<ll,ll>> dp1;  // dp1[i] := 長さがi+1であるような、(増加部分列における最終要素の最小値,頂点番号)
        vector<ll> prev; // prev[u] := LISを作るために、頂点uはその前にどの頂点から来たか
        LIS(const vector<pair<ll,ll>> &A) {
            ll N = (ll)A.size();
            dp1.assign(N, {INF,INF});
            prev.assign(N, -1);

            for(ll i=0; i<N; i++) {
                // auto it = lower_bound(dp1.begin(), dp1.end(), A.at(i));
                auto it = upper_bound(dp1.begin(), dp1.end(), A.at(i));
                *it = A.at(i);
                if (it != dp1.begin()) {
                    prev[i] = (*(it-1)).second;
                }
                else {
                    prev[i] = -1;
                }
            }

            answer = lower_bound(dp1.begin(), dp1.end(), make_pair(INF,INF)) - dp1.begin();
        }
};

void solve() {
    ll H, W, N; cin >> H >> W >> N;
    vector<pair<ll,ll>> coin(N);
    for(ll i=0; i<N; i++) {
        ll r, c; cin >> r >> c;
        r--; c--;
        coin[i] = {c, r}; // (x,y)
    }
    sort(coin.begin(), coin.end());

    // 平面捜査 + LIS
    // coinをxで昇順、yで昇順ソートしたら、あとはyに対して最長増加部分列（LIS）をする
    vector<pair<ll,ll>> Y(N); //(y座標, 頂点番号)
    for(ll i=0; i<N; i++) {
        auto[c, r] = coin[i];
        Y[i] = {r, i};
    }
    LIS lis(Y);

    // DP復元（経路復元）
    vector<ll> ans; // たどる頂点番号のリスト
    {
        auto[_, u] = lis.dp1[lis.answer-1];
        ans.push_back(u);
        while(lis.prev[u] != -1) {
            ans.push_back(lis.prev[u]);
            u = lis.prev[u];
        }
    }
    reverse(ans.begin(), ans.end());

    {// 答え
        cout << lis.answer << endl;
        ll x = 0, y = 0;
        for(ll i=0; i<(ll)ans.size(); i++) {
            auto[gx, gy] = coin[ans[i]];
            // cout << gx << " " << gy << endl;

            while(1) {
                if (x != gx) {
                    cout << 'R';
                    x++;
                    continue;
                }
                if (y != gy) {
                    cout << 'D';
                    y++;
                    continue;
                }
                break;
            }
        }
        // 右下へ行く
        while(1) {
            if (x != W-1) {
                cout << 'R';
                x++;
                continue;
            }
            if (y != H-1) {
                cout << 'D';
                y++;
                continue;
            }
            break;
        }
    }
}


int main() {
    solve();
    return 0;
}