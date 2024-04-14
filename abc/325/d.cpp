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


// WA 現在印字可能なものを管理してないからバグってる
void solve() {
    ll N; cin >> N;
    vector<ll> T(N), D(N);
    vector<ll> E(N); // 印字できる最終時刻
    vector<tuple<ll,ll,ll>> sche(N); // (終了時刻, 開始時刻, id)
    for(ll i=0; i<N; i++) {
        cin >> T[i] >> D[i];
        E[i] = T[i]+D[i];
        sche[i] = {E[i], T[i], i};
    }

    // 区間スケジュールで解く
    sort(sche.begin(), sche.end());
    ll now = -1; // 現在時刻
    ll ans = 0;
    for(ll i=0; i<N; i++) {
        auto [e, s, id] = sche[i];
        if (now < s) {
            ans++;
            now = s+1;
        }
        else if (s<=now && now<=e) {
            ans++;
            now++;
        }
        else {
            // 印字できない。無視
            ;
        }
    }
    cout << ans << endl;

}

// イベントソート
void solve2() {
    ll N; cin >> N;
    vector<ll> T(N), D(N);
    vector<ll> E(N); // 印字できる最終時刻
    map<ll, vector<pair<ll,ll>>> event; // event[イベント発生時刻] := (イベント種別, アイテムID)のリスト
    for(ll i=0; i<N; i++) {
        cin >> T[i] >> D[i];
        E[i] = T[i]+D[i];
        event[T[i]].push_back({1, i}); // 印字できるイベント
        event[E[i]+1].push_back({0, i}); // 印字できなくなったイベント
    }

    ll ans = 0;
    vector<bool> printable(N); // printable[i] := アイテムiが印字できるかどうか
    priority_queue<tuple<ll,ll,ll>, vector<tuple<ll,ll,ll>>, greater<tuple<ll,ll,ll>>> pq;  // 印字できるもの候補。(終了時刻,開始時刻)が早い順に格納する (終了時刻, 開始時刻, アイテムID)
    ll now_time = (*event.begin()).first; // 現在時刻
    while(1) {
        // 現在時刻はイベント発生時刻か？
        if (event.count(now_time)) {
            // イベント発生
            for(auto [kinds, id]: event[now_time]) {
                if (kinds == 0) {
                    printable[id] = false;
                }
                else {
                    printable[id] = true;
                    pq.push({E[id], T[id], id});
                }
            }
        }

        // 印字できるもの候補が空ならば、つぎのイベントまで時間を飛ばす
        if (pq.empty()) {
            auto it = event.upper_bound(now_time);
            if (it == event.end()) break; // シミュレーション終了
            now_time = it->first;
            continue;
        }

        // 印字できる候補から1つ印字する
        while(!pq.empty()) {
            auto[end_time, start_time, target_id] = pq.top(); pq.pop();
            if (!printable[target_id]) continue;
            // 印字できた
            ans++;
            if (now_time < start_time) now_time = start_time;
            now_time++;
            break;
        }
    }

    // 出力
    cout << ans << endl;
}

// 解説AC
void solve3() {
    ll N; cin >> N;
    vector<pair<ll,ll>> vec; // (開始時刻, 終了時刻)
    for(ll i=0; i<N; i++) {
        ll t, d; cin >> t >> d;
        vec.emplace_back(t, t+d);
    }
    sort(vec.begin(), vec.end());

    priority_queue<ll, vector<ll>, greater<ll>> pq; // 印字できるもの候補の終了時刻
    ll vi = 0;
    ll ans = 0;
    for(ll i=0; ; i++) {
        if (pq.empty()) {
            if (vi == N) break;
            i = vec[vi].first;
        }

        while(vi<N and vec[vi].first == i) {
            pq.push(vec[vi++].second);
        }
        while(!pq.empty() and pq.top()<i) pq.pop();
        if (!pq.empty()) {
            pq.pop();
            ans++;
        }
    }
    cout << ans << endl;
}

int main() {
    // solve2();
    solve3();
    return 0;
}