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

// 分割統治で2つの長方形が条件をみたすか？
bool f2(ll X, ll Y, ll A, ll B) {
    ll w = intceil(A,Y) + intceil(B,Y);
    return w <= X;
}

// 3つの長方形のうち、1つの長方形が条件をみたすか？
bool f3(ll X, ll Y, ll A, ll B, ll C) {
    ll w = intceil(A,Y); // 幅
    if (w >= X) return false;
    X -= w;
    return f2(X,Y,B,C) || f2(Y,X,B,C);
}


// 解説AC
// 長方形3つを配置するときの性質は
// (i) T字パターン
// (ii) 並列パターン
// の2パターンしかない
void solve() {
    ll X, Y, A, B, C; cin >> X >> Y >> A >> B >> C;
    for(ll fi=0; fi<2; fi++) {
        for(ll ri=0; ri<3; ri++) {
            if (f3(X,Y,A,B,C)) {
                cout << "Yes" << endl;
                return;
            }
            swap(A,B); swap(B,C); // ローテートする
        }
        swap(X,Y);
    }
    cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}