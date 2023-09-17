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


// WA
void solve() {
    vector grid(3, vector<ll>(3));
    for(ll i=0; i<3; i++) {
        for(ll j=0; j<3; j++) {
            cin >> grid[i][j];
        }
    }

    // がっかり判定
    auto is_gakkari = [&](ll now_i, ll now_j, vector<vector<bool>> &known) {
        {// 縦の列
            map<ll,ll> mp;
            ll num = 0;
            for(ll i=0; i<3; i++) {
                if (known[i][now_j]) {
                    mp[grid[i][now_j]]++;
                    num++;
                }
            }
            if (num == 2) {
                for(auto[_, val]: mp) {
                    if (val == 2) return true;
                }
            }
        }
        {// 横の列
            map<ll,ll> mp;
            ll num = 0;
            for(ll j=0; j<3; j++) {
                if (known[now_i][j]) {
                    num++;
                    mp[grid[now_i][j]]++;
                }
            }
            if (num == 2) {
                for(auto[_, val]: mp) {
                    if (val == 2) return true;
                }
            }
        }
        {//斜めの列1
            map<ll,ll> mp;
            ll num = 0;
            for(ll i=0; i<3; i++) {
                if (known[i][i]) {
                    num++;
                    mp[grid[i][i]]++;
                }
            }
            if (num == 2) {
                for(auto[_, val]: mp) {
                    if (val == 2) return true;
                }
            }
        }
        {//斜めの列2
            vector<pair<ll,ll>> vecs = {{2,0},{1,1},{0,2}};
            map<ll,ll> mp;
            ll num = 0;
            for(auto[i,j]: vecs) {
                if (known[i][j]) {
                    num++;
                    mp[grid[i][j]]++;
                }
            }
            if (num == 2) {
                for(auto[_, val]: mp) {
                    if (val == 2) return true;
                }
            }
        }
        return false;
    };

    // 全探索9!
    vector<pair<ll,ll>> A;
    for(ll i=0; i<3; i++) {
        for(ll j=0; j<3; j++) {
            A.push_back({i,j});
        }
    }
    ll gakkari = 0;
    ll total = 0;
    sort(A.begin(), A.end());
    do {
        total++;

        // シミュレーションする
        vector known(3, vector<bool>(3, false));// 高橋が知っているマス
        for(ll n=0; n<9; n++) {
            auto[now_i, now_j] = A[n];
            if (is_gakkari(now_i, now_j, known)) {
                gakkari++;
                break;
            }
            known[now_i][now_j] = true;
        }
    }while (next_permutation(A.begin(), A.end()));

    // 答え
    double ans = (double)1.0 - (double)gakkari/total;
    printf("%.10f\n", ans);
}

// 解説AC
void solve2() {
    vector<ll> A(9);
    for(ll i=0; i<9; i++) cin >> A[i];

    // 縦横斜めの列の一覧
    vector<tuple<ll,ll,ll>> row{{0,1,2},{3,4,5},{6,7,8},
                                {0,3,6},{1,4,7},{2,5,8},
                                {0,4,8,},{2,4,6}};

    vector<ll> order(9); // order[i] := iマスが開く順番
    iota(order.begin(), order.end(), 0LL);

    ll gakkari = 0;
    ll total = 0;
    do {
        total++;
        bool is_gakkari = false;
        for(auto[a,b,c]: row) {
            if (A[a]==A[b] && order[a] < order[c] && order[b] < order[c]) {
                is_gakkari = true;
            }
            else if (A[b]==A[c] && order[b] < order[a] && order[c] < order[a]) {
                is_gakkari = true;
            }
            else if (A[c]==A[a] && order[c] < order[b] && order[a] < order[b]) {
                is_gakkari = true;
            }
            if (is_gakkari) {gakkari++; break;}
        }
    }while(next_permutation(order.begin(), order.end()));

    // 答え
    double ans = (double)1.0 - (double)gakkari/total;
    printf("%.10f\n", ans);
}

int main() {
    // solve();
    solve2();
    return 0;
}