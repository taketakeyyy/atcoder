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


// 尺取+貪欲法 AC
void solve() {
    ll N, M; cin >> N >> M;

    // クエリ先読み
    vector<ll> canA; // 缶切り不要な缶
    priority_queue<ll> canB; // 缶切り必要な缶
    priority_queue<ll> cut; // 缶切り
    for(ll i=0; i<N; i++) {
        ll t, x; cin >> t >> x;
        if (t == 0) {
            canA.push_back(x);
        }
        else if (t == 1) {
            canB.push(x);
        }
        else if (t == 2) {
            cut.push(x);
        }
    }
    sort(canA.begin(), canA.end());
    reverse(canA.begin(), canA.end());

    // まずは缶切り不要な缶で大きい方から選んでいく
    deque<ll> deqA; // 選んだ缶A
    {
        ll limit = min(M, (ll)canA.size());
        for(ll i=0; i<limit; i++) {
            deqA.push_back(canA[i]);
        }
    }

    // まだ持てるならできるだけcanBから選ぶ
    ll cut_n = 0; // 現在切れる回数
    ll have = (ll)deqA.size(); // 今選んだ品物の数
    deque<ll> deqB; // 選んだ缶B
    while(have < M) {
        // 切れる回数が0なら缶切りを選ぶ
        if (cut_n == 0) {
            if (cut.empty()) break;
            cut_n += cut.top(); cut.pop();
            have++;
        }
        if (have == M) break;

        // canBから選ぶ
        if (canB.empty()) break;
        deqB.push_back(canB.top()); canB.pop();
        have++; cut_n--;
    }

    // 現在の満足度を数える
    ll ans = 0;
    for(ll i=0; i<(ll)deqA.size(); i++) {
        ans += deqA[i];
    }
    for(ll i=0; i<(ll)deqB.size(); i++) {
        ans += deqB[i];
    }

    // 次に、尺取法でdeqAから引きつつcanBを選んでいき、最大値を更新していく
    ll total = ans;
    while(1) {
        if (cut_n == 0) {
            if (cut.empty()) break;
            cut_n += cut.top(); cut.pop();
            have++;
            if (have == M+1) {
                if (deqA.empty()) break;
                total -= deqA.back(); deqA.pop_back();
                have--;
            }
        }

        if (have == M) {
            // 持っている品物がM個なら
            if (deqA.empty()) break;
            if (canB.empty()) break;
            ll a = deqA.back();
            ll b = canB.top();
            if (b > a) {
                total -= a;
                total += b;
                deqA.pop_back();
                deqB.push_back(b);
                canB.pop();
                cut_n--;
                ans = max(ans, total);
            }
            else {
                break;
            }
        }
        else {
            // 持っている品物がM個より小さいなら、canBから選ぶだけ
            if (canB.empty()) break;
            ll b = canB.top();
            canB.pop();
            total += b;
            deqB.push_back(b);
            cut_n--;
            have++;
            ans = max(ans, total);
        }
    }

    // 出力
    cout << ans << endl;
}


// 解説AC 累積和+貪欲法
void solve2() {
    ll N, M; cin >> N >> M;
    vector<ll> canA, canB, cutter;
    for(ll i=0; i<N; i++) {
        ll t, x; cin >> t >> x;
        if (t == 0) {
            canA.push_back(x);
        }
        else if (t == 1) {
            canB.push_back(x);
        }
        else if (t == 2) {
            cutter.push_back(x);
        }
    }
    sort(canA.begin(), canA.end(), greater<>());
    sort(canB.begin(), canB.end());
    sort(cutter.begin(), cutter.end());

    // rA[i] := canAをi個選ぶと固定したときの累積和
    // rB[i] := canBをi個選ぶと固定したときの累積和
    vector<ll> rA(N+1, 0), rB(N+1, 0);

    // rAを埋める（大きい方から貪欲）
    for(ll i=0; i<N; i++) {
        if (i < (ll)canA.size()) rA[i+1] = rA[i] + canA[i];
        else rA[i+1] = rA[i];
    }

    // rBを埋める(大きい方から貪欲)
    ll cut_n = 0; // 切れる回数
    for(ll i=0; i<N; i++) {
        if (canB.empty()) {
            rB[i+1] = rB[i];
        }
        else if (cut_n == 0) {
            if (!cutter.empty()) {
                cut_n += cutter.back();
                cutter.pop_back();
            }
            rB[i+1] = rB[i];
        }
        else {
            cut_n--;
            rB[i+1] = rB[i] + canB.back();
            canB.pop_back();
        }
    }

    // canAをi個選ぶと固定したとき、canBはM-i個選ぶ。累積和を使って最大値を求める
    ll ans = 0;
    for(ll i=0; i<=M; i++) {
        ans = max(ans, rA[i]+rB[M-i]);
    }
    cout << ans << endl;
}


int main() {
    solve();
    // solve2();
    return 0;
}