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


// イベントソート
void solve() {
    ll N, Q; cin >> N >> Q;
    vector<tuple<ll,ll,ll>> events; // イベント配列
    multiset<ll> stop; // 現時点で通行止めの座標
    for(ll i=0; i<N; i++) {
        ll s, t, x; cin >> s >> t >> x;
        events.push_back({s-x, 1, x}); // 追加イベント
        events.push_back({t-x, -1, x}); // 削除イベント
    }
    sort(events.begin(), events.end());

    // クエリ処理
    vector<ll> ans;
    ll i = 0;
    for(ll q=0; q<Q; q++) {
        ll d; cin >> d;

        // イベントを処理する
        while(1) {
            if (i == events.size()) break;

            auto[t, kind, x] = events[i];

            if (t <= d) {
                if (kind == 1) {
                    // 追加イベント
                    stop.insert(x);
                }
                else {
                    // 削除イベント
                    auto it = stop.lower_bound(x);
                    stop.erase(it);
                }
                i++;
                continue;
            }
            break;
        }

        if (stop.size() == 0) ans.push_back(-1);
        else ans.push_back(*stop.begin());
    }

    // 出力
    for(ll q=0; q<Q; q++) {
        cout << ans[q] << endl;
    }
}

// イベントソート
// クエリイベントも作るバージョン
void solve2() {
    ll N, Q; cin >> N >> Q;
    vector<tuple<ll,ll,ll>> events; // イベント配列
    for(ll i=0; i<N; i++) {
        ll s, t, x; cin >> s >> t >> x;
        events.push_back({s-x, 1, x}); // 追加イベント
        events.push_back({t-x, -1, x}); // 削除イベント
    }

    // クエリ処理
    const ll NIL = -1;
    for(ll q=0; q<Q; q++) {
        ll d; cin >> d;
        events.push_back({d, 2, NIL}); // クエリイベント
    }
    sort(events.begin(), events.end());

    // イベントを処理していく
    vector<ll> ans;
    multiset<ll> stop; // 現時点で通行止めの座標
    for(ll i=0; i<(ll)events.size(); i++) {
        auto[t, kind, x] = events[i];
        if (kind == 1) {
            // 追加イベント
            stop.insert(x);
        }
        else if (kind == -1) {
            // 削除イベント
            auto it = stop.lower_bound(x);
            stop.erase(it);
        }
        else {
            // クエリイベント
            if (stop.empty()) ans.push_back(-1);
            else ans.push_back(*stop.begin());
        }
    }

    // 出力
    for(ll q=0; q<Q; q++) {
        cout << ans[q] << endl;
    }
}

int main() {
    // solve();
    solve2();
    return 0;
}