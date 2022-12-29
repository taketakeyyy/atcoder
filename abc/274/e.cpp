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

// p1からp2に行くのにかかる時間
double calc_time(pair<ll,ll>p1, pair<ll,ll>p2, ll booster_num) {
    auto[x1, y1] = p1;
    auto[x2, y2] = p2;
    return sqrt(pow(x1-x2, 2)+pow(y1-y2, 2)) / pow(2, booster_num);
}

// TLE （dpに原点を含めるとTLE）
void solve() {
    ll N, M; cin >> N >> M;
    vector<pair<ll,ll>> point(N+M+1);  // 原点 + 都市 + 宝箱 の位置
    point[0] = {0,0};  // 原点
    for(ll i=1; i<=N; i++) {  // 都市
        ll x, y; cin >> x >> y;
        point[i] = {x,y};
    }
    for(ll i=N+1; i<N+M+1; i++) {  // 宝箱
        ll p, q; cin >> p >> q;
        point[i] = {p,q};
    }

    // dp[bit][i] := 訪れた都市と宝箱の集合がbitで、現在地がiのときの、旅行にかかった時間の最小値
    vector dp(1<<(N+M+1), vector<double>(N+M+1, numeric_limits<double>::max()));

    // 原点からスタートなので、原点から各都市へのコストは計算しておく（原点は訪れてない扱いとする）
    for(ll i=1; i<N+M+1; i++) {
        dp[1<<i][i] = calc_time({0,0}, point[i], 0);
    }

    // 各bitの状態が、ブースターの数何個かを前計算しておく
    map<ll,ll> booster_num;
    for(ll bit=0; bit<(1<<(N+M+1)); bit++) {
        ll num = 0;
        for(ll b=N+1; b<N+M+1; b++) {
            if (bit>>b&1) num++;
        }
        booster_num[bit] = num;
    }

    // 巡回セールスマン問題的にdp埋める
    for(ll bit=0; bit<(1<<(N+M+1)); bit++) {
        for(ll i=0; i<N+M+1; i++) {  // 現在の位置i
            if (~bit>>i&1) continue;  // iはまだ訪れていないならスキップ
            for(ll j=0; j<N+M+1; j++) {  // 次に行く位置j
                if (bit>>j&1) continue;  // jはすでに訪れている
                // iが訪問済みで、jが未訪問なら、dp更新
                dp[bit|1<<j][j] = min(dp[bit|1<<j][j], dp[bit][i]+calc_time(point[i], point[j], booster_num[bit]));
            }
        }
    }

    // 答えを見つける（宝箱は必ずしも訪れなくてOK）
    double ans = numeric_limits<double>::max();
    for(ll bit=0; bit<(1<<M); bit++) {  // 宝箱の位置のbit全探索
        ll bit2 = bit << (N+1);
        ans = min(ans, dp[((1<<(N+1))-1) | bit2][0]);
    }
    printf("%.7lf\n", ans);
}


// AC（dpに原点を含めない方法。1個分減る）
void solve2() {
    ll N, M; cin >> N >> M;
    vector<pair<ll,ll>> point(N+M);  // 都市 + 宝箱 の位置
    for(ll i=0; i<N; i++) {  // 都市
        ll x, y; cin >> x >> y;
        point[i] = {x,y};
    }
    for(ll i=N; i<N+M; i++) {  // 宝箱
        ll p, q; cin >> p >> q;
        point[i] = {p,q};
    }

    // dp[bit][i] := 訪れた都市と宝箱の集合がbitで、現在地がiのときの、旅行にかかった時間の最小値
    vector dp(1<<(N+M), vector<double>(N+M, numeric_limits<double>::max()));

    // 原点からスタートなので、原点から各都市へのコストは初期値として計算しておく
    for(ll i=0; i<N+M; i++) {
        dp[1<<i][i] = calc_time({0,0}, point[i], 0);
    }

    // 各bitの状態が、ブースターの数何個かを前計算しておく
    map<ll,ll> booster_num;
    for(ll bit=0; bit<(1<<(N+M)); bit++) {
        ll num = 0;
        for(ll b=N; b<N+M; b++) {
            if (bit>>b&1) num++;
        }
        booster_num[bit] = num;
    }

    // 巡回セールスマン問題的にdp埋める
    for(ll bit=0; bit<(1<<(N+M)); bit++) {
        for(ll i=0; i<N+M; i++) {  // 現在の位置i
            if (~bit>>i&1) continue;  // iはまだ訪れていないならスキップ
            for(ll j=0; j<N+M; j++) {  // 次に行く位置j
                if (bit>>j&1) continue;  // jはすでに訪れている
                // iが訪問済みで、jが未訪問なら、dp更新
                dp[bit|1<<j][j] = min(dp[bit|1<<j][j], dp[bit][i]+calc_time(point[i], point[j], booster_num[bit]));
            }
        }
    }

    // 答えを見つける（宝箱は必ずしも訪れなくてOK）
    double ans = numeric_limits<double>::max();
    for(ll bit=0; bit<(1<<M); bit++) {  // 宝箱の位置のbit全探索
        ll bit2 = ((1<<N)-1) | bit<<N;  // すべての都市に訪れた | 宝箱の位置
        for(ll i=0; i<N+M; i++) {
            ans = min(ans, dp[bit2][i] + calc_time(point[i], {0,0}, booster_num[bit2]));
        }
    }
    printf("%.7lf\n", ans);
}


int main() {
    // solve();
    solve2();
    return 0;
}