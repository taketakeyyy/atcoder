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


ll send(ll A, ll B, ll C, ll D) {
    printf("? %lld %lld %lld %lld\n", A, B, C, D);
    flush(cout);
    ll res; cin >> res;
    return res;
}

// まず行を絞り込んで、次に列を絞り込む
// [1, MID) の区間を狭めていくめぐる式二分探索
void solve() {
    ll N; cin >> N;

    // 行を絞り込む質問をする
    ll U=1, D=N+1;
    while(D-U != 1) { // [U, D)で考えると便利？
        ll MID = (U+D)/2;
        ll res = send(1, MID-1, 1, N); // [U, MID)
        (res == MID-1 ? U : D) = MID;
    }

    // 列を絞り込む質問をする
    ll L=1, R=N+1;
    while(R-L != 1) {
        ll MID = (R+L)/2;
        ll res = send(1, N, 1, MID-1);
        (res == MID-1 ? L : R) = MID;
    }

    // 出力
    printf("! %lld %lld\n", U, L);
    flush(cout);
}

// [L, MID) の矩形区間を狭めていくめぐる式二分探索
void solve2() {
    ll N; cin >> N;

    // 行を絞り込む質問をする
    ll U=1, D=N+1;
    while(D-U != 1) {  // [U, D)で考えると便利？
        ll MID = (U+D)/2;
        ll res = send(U, MID-1, 1, N);  // [U, MID)
        (res == MID-U ? U : D) = MID;
    }

    // 列を絞り込む質問をする
    ll L=1, R=N+1;
    while(R-L != 1) {
        ll MID = (R+L)/2;
        ll res = send(1, N, L, MID-1);
        (res == MID-L ? L : R) = MID;
    }

    // 出力
    printf("! %lld %lld\n", U, L);
    flush(cout);
}


int main() {
    // solve();
    // solve2();
    return 0;
}