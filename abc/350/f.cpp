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

// 解説AC(physics0523)
void solve() {
    string S; cin >> S;

    // 対応するカッコの位置をあらかじめ求める
    map<ll,ll> l2r; // '('のインデックス番号から、対応する')'のインデックス番号を求める
    map<ll,ll> r2l; // ')'のインデックス番号から、対応する'('のインデックス番号を求める
    auto where_is_kakko = [&]() {
        stack<ll> stk; // '('のインデックス番号をスタックに格納
        for(ll i=0; i<(ll)S.size(); i++) {
            if (S[i]=='(') stk.push(i);
            else if (S[i]==')') {
                ll l = stk.top(); stk.pop();
                ll r = i;
                l2r[l]=r; r2l[r]=l;
            }
        }
    };
    where_is_kakko();

    // 文字cをis_flipに応じて出力する
    auto out = [&](char c, bool is_flip) {
        if (is_flip) {
            if ('A'<=c and c<='Z') cout << (char)(c+32);
            else cout << (char)(c-32);
        }
        else {
            cout << c;
        }
    };

    // ()で囲まれた中身を再帰的に処理する
    auto dfs = [&](auto dfs, ll l, ll r, bool is_flip) -> void {
        if (!is_flip) { // 左から読む
            for(ll i=l; i<=r; i++) {
                if (S[i]=='(') {
                    dfs(dfs, i+1, l2r[i]-1, !is_flip);
                    i = l2r[i]; // 一気に飛ばす
                }
                else {
                    out(S[i], is_flip);
                }
            }
        }
        else { // 右から読む
            for(ll i=r; i>=l; i--) {
                if (S[i]==')') {
                    dfs(dfs, r2l[i]+1, i-1, !is_flip);
                    i = r2l[i]; // 一気に飛ばす
                }
                else {
                    out(S[i], is_flip);
                }
            }
        }
    };

    // カッコの塊ごとに出力する
    for(ll i=0; i<(ll)S.size(); i++) {
        if (S[i]=='(') {
            dfs(dfs, i+1, l2r[i]-1, true);
            i = l2r[i]; // 一気に飛ばす
        }
        else {
            cout << S[i];
        }
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}