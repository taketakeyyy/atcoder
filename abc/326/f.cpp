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

// Xを作ることができるか？
pair<bool, string> check(vector<ll> &B, ll X) {
    // mp[座標] := その座標にするための移動履歴 を作る
    auto gen_map = [&](ll l, ll r) -> unordered_map<ll,string> {
        vector<ll> C;
        for(ll i=l; i<r; i++) C.push_back(B[i]);

        // bit全探索
        ll NC = C.size();
        unordered_map<ll,string> mp; // mapだとTLE
        for(ll bit=0; bit<(1<<NC); bit++) {
            ll x = 0;
            string history = "";
            for(ll d=0; d<NC; d++) {
                if (bit>>d&1) {
                    x += C[d];
                    history += "+";
                }
                else {
                    x -= C[d];
                    history += "-";
                }
            }
            mp[x] = history;
        }
        return mp;
    };

    ll N = B.size();
    // Bの前半部分
    auto mp1 = gen_map(0, N/2);
    // Bの後半部分
    auto mp2 = gen_map(N/2, N);

    // Xを作ることができるか？
    // key1+key2 == XになればOK
    for(auto[key1, val1]: mp1) {
        if (mp2.count(X-key1)) {
            return {true, val1+mp2[X-key1]};
        }
    }
    return {false, ""};
}


// Nは最大で80
// 右回り or 左回り を全探索 = 2^80の計算量で膨大。

// i=0~N-1について
// iが偶数：y軸方向の移動
// iが奇数：x軸方向の移動
// xとyに独立に考えることができる。それぞれX、Yにすることができるか？
// 2^40 = 1e12の計算量

// 半分全列挙すれば、2^20 = 1e6まで落とせる
void solve() {
    ll N, X, Y; cin >> N >> X >> Y;
    vector<vector<ll>> B(2); // B[0]:=偶数回の移動量、B[1]:=奇数回の移動量
    for(ll i=0; i<N; i++) {
        ll a; cin >> a;
        if (i%2 == 0) B[0].push_back(a);
        else B[1].push_back(a);
    }

    // Yについて調べる
    auto[flag_y, history_y] = check(B[0], Y);
    if (!flag_y) {
        cout << "No" << endl;
        return;
    }

    // Xについて調べる
    auto[flag_x, history_x] = check(B[1], X);
    if (!flag_x) {
        cout << "No" << endl;
        return;
    }

    // 履歴を作る
    string history = "";
    char now_dir = 'R'; // 現在の向き
    for(ll i=0; i<(ll)history_y.size(); i++) {
        if (now_dir=='R' && history_y[i]=='+') {
            now_dir='U'; history += "L";
        }
        else if (now_dir=='R' && history_y[i]=='-') {
            now_dir='D'; history += "R";
        }
        else if (now_dir=='L' && history_y[i]=='+') {
            now_dir='U'; history += "R";
        }
        else if (now_dir=='L' && history_y[i]=='-') {
            now_dir='D'; history += "L";
        }

        if (i == (ll)history_x.size()) break;
        if (now_dir=='U' && history_x[i]=='+') {
            now_dir='R'; history += "R";
        }
        else if (now_dir=='U' && history_x[i]=='-') {
            now_dir='L'; history += "L";
        }
        else if (now_dir=='D' && history_x[i]=='+') {
            now_dir='R'; history += "L";
        }
        else if (now_dir=='D' && history_x[i]=='-') {
            now_dir='L'; history += "R";
        }
    }

    // 出力
    cout << "Yes" << endl;
    cout << history << endl;
}


int main() {
    solve();
    return 0;
}