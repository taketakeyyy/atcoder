#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
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
// 初項a, 末項l, 項数n のときの等差数列の和
ll tousa1(const ll &a, const ll &l, const ll &n) { return ((a+l)*n)/2; }
// 初項a, 公差d, 項数n のときの等差数列の和
ll tousa2(const ll &a, const ll &d, const ll &n) { return ((2*a+(n-1)*d)*n)/2; }


void solve() {
    string S; cin >> S;
    ll gx, gy; cin >> gx >> gy;
    // 原点を+MARGINずらす
    const ll MARGIN = 8010;
    gx += MARGIN;
    gy += MARGIN;

    // ランレングス圧縮 + 縦と横に分割
    vector<ll> Xs, Ys;
    {
        ll seq = 0; // 連続する'F'の文字数
        ll dir = 0; // 0:x方向, 1:y方向
        for(const char &ch: S) {
            if (ch == 'T') {
                if (dir == 0) Xs.push_back(seq);
                else Ys.push_back(seq);
                seq = 0;
                dir ^= 1LL;
                continue;
            }
            else {
                seq++;
                continue;
            }
        }
        if (dir == 0) Xs.push_back(seq);
        else Ys.push_back(seq);
    }

    // x軸方向とy軸方向で、到達可能性を独立に考える
    const ll MAX_X = MARGIN*2;
    auto f = [&](vector<bool> &dp, const vector<ll> &Xs) -> void {
        for(ll num: Xs) {
            vector<bool> ndp(MAX_X, false);
            for(ll x=0; x<MAX_X; x++) {
                if (dp[x]) {
                    if (x+num<MAX_X) ndp[x+num] = true;
                    if (x-num>=0) ndp[x-num] = true;
                }
            }
            swap(ndp, dp);
        }
    };

    // x軸方向のdp
    vector<bool> dpX(MAX_X, false);
    // 最初の移動はx軸正方向しか移動できないことに注意！
    dpX[MARGIN+Xs[0]] = true;
    Xs.erase(Xs.begin());
    f(dpX, Xs);

    // y軸方向のdp
    vector<bool> dpY(MAX_X, false);
    dpY[MARGIN] = true;
    f(dpY, Ys);

    // 答え
    if (dpX[gx] and dpY[gy]) cout << "Yes" << endl;
    else cout << "No" << endl;
}

void solve2() {
    string S; cin >> S;
    ll gx, gy; cin >> gx >> gy;
    // 原点を+MARGINずらす
    constexpr ll MARGIN = 8010;
    gx += MARGIN;
    gy += MARGIN;

    // ランレングス圧縮 + 縦と横に分割
    vector<ll> Xs, Ys;
    {
        ll seq = 0; // 連続する'F'の文字数
        ll dir = 0; // 0:x方向, 1:y方向
        for(const char &ch: S) {
            if (ch == 'T') {
                if (dir == 0) Xs.push_back(seq);
                else Ys.push_back(seq);
                seq = 0;
                dir ^= 1LL;
                continue;
            }
            else {
                seq++;
                continue;
            }
        }
        if (dir == 0) Xs.push_back(seq);
        else Ys.push_back(seq);
    }

    // x軸方向とy軸方向で、到達可能性を独立に考える
    constexpr ll MAX_X = MARGIN*2;
    auto f = [&](bitset<MAX_X> &dp, const vector<ll> &Xs) -> void {
        for(ll num: Xs) {
            bitset<MAX_X> ndp;
            ndp |= (dp<<num) | (dp>>num);
            swap(ndp, dp);
        }
    };

    // x軸方向のdp
    bitset<MAX_X> dpX;
    // 最初の移動はx軸正方向しか移動できないことに注意！
    dpX[MARGIN+Xs[0]] = true;
    Xs.erase(Xs.begin());
    f(dpX, Xs);

    // y軸方向のdp
    bitset<MAX_X> dpY;
    dpY[MARGIN] = true;
    f(dpY, Ys);

    // 答え
    if (dpX[gx] and dpY[gy]) cout << "Yes" << endl;
    else cout << "No" << endl;
}



int main() {
    // solve();
    solve2();
    return 0;
}