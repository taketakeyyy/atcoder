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
    ll N, M; cin >> N >> M;

    // イベントソート...と思ったけど単なるシミュレーションだな
    vector<tuple<ll,ll,ll>> events;
    {
        // クエリ処理
        for(ll i=0; i<M; i++) {
            ll t, w, s; cin >> t >> w >> s;
            events.push_back({t, w, s});
        }
    }
    sort(events.begin(), events.end());

    vector<ll> ans(N);
    {//イベント処理
        set<ll> st; // 並んでる人
        for(ll i=0; i<N; i++) st.insert(i);

        priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;  // 復活待ちの(時刻, 人)
        for(auto[t, w, s]: events) {
            // 人を復活させる処理
            while(!pq.empty()) {
                auto[rt, i] = pq.top();
                if (rt <= t) {
                    st.insert(i);
                    pq.pop();
                    continue;
                }
                break;
            }

            // そうめん食う処理
            if (st.size() >= 1) {
                auto it = st.begin();
                ans[(*it)] += w;
                // 復活待ちに入れる
                pq.push({t+s, (*it)});
                // 人を列から削除
                st.erase(it);
            }
        }
    }

    // 答え
    for(ll i=0; i<N; i++) {
        cout << ans[i] << endl;
    }
}


int main() {
    solve();
    return 0;
}