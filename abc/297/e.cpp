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


// 解説AC
void solve() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i];
    }

    // ダイクストラっぽく解く
    set<ll> Q; // 最も安い金額の候補
    for(ll i=0; i<N; i++) Q.insert(A[i]);
    vector<ll> ans(K+1, 0); // ans[k] := 安い方からk番目の値
    ans[0] = 0;
    ll k = 1; // k番目に安い金額を求めていく
    while(k <= K) {
        // 最も安い金額uを取り出す
        auto it = Q.begin();
        ll u = *it;
        Q.erase(it);

        // 金額uがk-1番目と重複している場合、スキップ
        if (ans[k-1] == u) continue;
        ans[k] = u; // k番目に安いやつはuで確定

        // 最も安い金額u + A[i] を、次の安い金額の候補に入れる
        for(ll i=0; i<N; i++) Q.insert(u+A[i]);
        k++;
    }
    cout << ans[K] << endl;
}


// 二分探索解法。DFSで探索。REする。
void solve2() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i];
    }
    sort(A.begin(), A.end());

    // f(x) := 安い方からK番目の値はx以下か？
    auto f = [&](auto f, ll x, ll now, set<ll> &visited) {
        if ((ll)visited.size() >= K) return true;

        for(ll i=0; i<N; i++) {
            ll nx = now + A[i];
            if (nx <= x) {
                if (visited.count(nx)) continue; // 既に探索済み（メモ化と同じ効果）
                visited.insert(nx);
                bool res = f(f, x, nx, visited);
                if (res) return true;
                continue;
            }
            break;
        }

        if ((ll)visited.size() >= K) return true;
        else return false;
    };

    // 二分探索
    ll l = 1, r = 2e14+100;
    while(r-l != 1) {
        ll mid = (l+r)/2;
        set<ll> visited;
        if (f(f, mid, 0, visited)) r = mid;
        else l = mid;
    }
    set<ll> visited;
    if (f(f, l, 0, visited)) {
        cout << l << endl;
    }
    else {
        cout << r << endl;
    }
}


// 二分探索解法。BFSで探索。TLE
void solve3() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i];
    }
    sort(A.begin(), A.end());

    // f(x) := 安い方からK番目の値はx以下か？
    auto f = [&](ll x) -> bool {
        deque<ll> dq;
        dq.push_back(0);
        unordered_set<ll> visited;
        while(!dq.empty()) {
            if ((ll)visited.size() >= K) return true;
            ll u = dq.front(); dq.pop_front();

            for(ll a: A) {
                ll v = u + a;
                if (visited.count(v)) continue;
                if (v > x) break;
                visited.insert(v);
                dq.push_back(v);
            }
        }

        if ((ll)visited.size() >= K) return true;
        else return false;
    };

    // 二分探索
    ll l = 1, r = 2e14+100;
    while(r-l != 1) {
        ll mid = (l+r)/2;
        if (f(mid)) r = mid;
        else l = mid;
    }
    if (f(l)) {
        cout << l << endl;
    }
    else {
        cout << r << endl;
    }
}

// 二分探索解法。BFSの定数倍を高速化で探索。AC
// setの代わりにunordered_setを使わないとTLEする
void solve4() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i];
    }
    sort(A.begin(), A.end());

    // f(x) := 安い方からK番目の値はx以下か？
    auto f = [&](ll x) -> bool {
        vector<ll> vec;
        vec.push_back(0);
        // set<ll> visited;
        unordered_set<ll> visited; // setより速い
        while(!vec.empty()) {
            if ((ll)visited.size() >= K) return true;
            ll u = vec.back(); vec.pop_back();

            for(ll a: A) {
                ll v = u + a;
                if (visited.count(v)) continue;
                if (v > x) break;
                visited.emplace(v); // insertより速い
                vec.push_back(v);
            }
        }

        if ((ll)visited.size() >= K) return true;
        else return false;
    };

    // 二分探索
    // ll l = 1, r = 2e14+100;
    ll l = 1, r = A.back()*K;
    while(r-l != 1) {
        ll mid = (l+r)/2;
        if (f(mid)) r = mid;
        else l = mid;
    }
    if (f(l)) {
        cout << l << endl;
    }
    else {
        cout << r << endl;
    }
}

// 二分探索解法。BFSの速度検証用。
// * BFSのデータ管理
//   - vec と deque -> 変わらず
// * setとunordered_setの違い
//   - unordered_setのほうが速い。setだとTLE!
// * unordered_setの、insertとemplaceの違い
//   - emplaceのほうが速いらしいが、大して変わらず
void solve_test() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i];
    }
    sort(A.begin(), A.end());

    // f(x) := 安い方からK番目の値はx以下か？
    auto f = [&](ll x) -> bool {
        deque<ll> deq;
        deq.push_back(0);
        // set<ll> visited;
        unordered_set<ll> visited;
        while(!deq.empty()) {
            if ((ll)visited.size() >= K) return true;
            ll u = deq.front(); deq.pop_front();

            for(ll a: A) {
                ll v = u + a;
                if (visited.count(v)) continue;
                if (v > x) break;
                visited.emplace(v);
                // visited.insert(v);
                deq.push_back(v);
            }
        }

        if ((ll)visited.size() >= K) return true;
        else return false;
    };

    // 二分探索
    ll l = 1, r = 2e14+100;
    // ll l = 1, r = A.back()*K;
    while(r-l != 1) {
        ll mid = (l+r)/2;
        if (f(mid)) r = mid;
        else l = mid;
    }
    if (f(l)) {
        cout << l << endl;
    }
    else {
        cout << r << endl;
    }
}


int main() {
    solve();
    // solve2();
    // solve3();
    // solve4();
    // solve_test();
    return 0;
}