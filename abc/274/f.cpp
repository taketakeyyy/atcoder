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
    ll N, A; cin >> N >> A;
    vector<ll> W(N), X(N), V(N);
    for(ll i=0; i<N; i++) {
        cin >> W[i] >> X[i] >> V[i];
    }

    // 網を魚iの左端に置いたときを全探索
    ll ans = 0;
    for(ll i=0; i<N; i++) {
        // 時刻0のときの重さの合計
        ll total = 0;
        for(ll j=0; j<N; j++) {
            if (X[i]<=X[j] and X[j]<=X[i]+A) {
                total +=W [j];
            }
        }
        chmax(ans, total);

        // イベント作成
        priority_queue<tuple<double,ll,ll>, vector<tuple<double,ll,ll>>, greater<tuple<double,ll,ll>>> pq;  // 小さい順を維持する優先度付きキュー // (時刻,イベント種別,魚id)
        for(ll j=0; j<N; j++) {
            if (i == j) continue;
            if (V[i] == V[j]) continue;
            if (V[i] > V[j]) { // 魚iのほうが速いとき
                ll v = V[i]-V[j]; // 相対速度
                if (X[i]+A < X[j]) {
                    // 魚jは、時刻0に網の右端より右にいるとき
                    ll d = X[j] - (X[i]+A); // 距離
                    double t_in = (double)d/v;
                    pq.push({t_in,0,j}); // (時刻tに、魚jが網に入る)

                    // 網から出るとき
                    double t_out = (double)(X[j]-X[i])/v;
                    pq.push({t_out,1,j});
                }
                else if (X[i]<=X[j] and X[j]<=X[i]+A) {
                    // 魚jは、時刻0に網の中にいるとき
                    ll d = X[j] - X[i];
                    double t_out = (double)d/v;
                    pq.push({t_out,1,j});
                }
            }
            else { // 魚jのほうが速いとき
                ll v = V[j] - V[i];
                if (X[j] < X[i]) {
                    // 魚jは、時刻0に網の左端より左にいるとき
                    ll d = X[i] - X[j];
                    double t_in = (double)d/v;
                    pq.push({t_in,0,j});

                    // 網から出るとき
                    double t_out = (double)(X[i]+A-X[j])/v;
                    pq.push({t_out,1,j});
                }
                else if (X[i]<=X[j] and X[j]<=X[i]+A) {
                    // 魚jは、時刻0に網の中にいるとき
                    ll d = X[i]+A-X[j];
                    double t_out = (double)d/v;
                    pq.push({t_out,1,j});
                }
            }
        }

        while(!pq.empty()) {
            auto[t,type,id] = pq.top(); pq.pop();
            if (type == 0) { // 魚が網に入る
                total += W[id];
            }
            else { // 魚が網から出る
                total -= W[id];
            }
            chmax(ans, total);
        }
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}