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


// 2のd乗の計算は、1<<d だとオーバーフローするので注意
// 正しくは 1LL<<d
void solve() {
    string S; cin >> S;
    ll N; cin >> N;

    ll D = S.size();
    string rS = S;
    reverse(rS.begin(), rS.end());

    // (1)まず、?以外のところを計算する
    ll ans = 0;
    for(ll d=0; d<D; d++) {
        if (rS[d] == '1') ans += 1LL<<d;
    }

    // (2) ? をすべて 0 にしたとき、Nを超えるなら終了
    if (ans > N) {
        cout << -1 << endl;
    }
    else {
        // (3) 上位桁から順に ? を 1 に変更してみて、Nを超えないなら採用する
        for(ll d=D-1; d>=0; d--) {
            if (rS[d] == '?') {
                ans += 1LL<<d;
                if (ans <= N) continue;
                ans -= 1LL<<d;
            }
        }
        cout << ans << endl;
    }
}


// 解説AC
void solve2() {
    string S; cin >> S;
    ll N; cin >> N;
    ll D = S.size();

    ll ans = 0;
    // ? をすべて 0 にする
    reverse(S.begin(), S.end());
    for(ll i=0; i<D; i++) {
        if (S[i] == '1') ans += 1LL<<i;
    }

    if (ans > N) {
        cout << -1 << endl;
    }
    else {
        // 上位桁から順に ? を 1にできるか試みる
        for(ll i=D-1; i>=0; i--) {
            if (S[i] == '?' && (ans | 1LL<<i) <= N) {
                ans |= 1LL<<i;
            }
        }
        cout << ans << endl;
    }
}

// WA
void solve3() {
    string S; cin >> S;
    ll N; cin >> N;

    // 文字列Sを60文字にする
    while((ll)S.size() != 60) {
        S = '0' + S;
    }

    // Nを文字列Tにする
    string T = "............................................................";
    for(ll d=0; d<60; d++) {
        if (N>>d&1) T[d] = '1';
        else T[d] = '0';
    }
    reverse(T.begin(), T.end());

    // 左から見ていく
    bool is_T_big = false; // Tのほうが大きいか？
    for(ll i=0; i<60; i++) {
        if (S[i] == T[i]) continue;
        if (is_T_big) {
            if (S[i] == '?') S[i] = '1';
            continue;
        }
        else {
            if (S[i]=='0' && T[i]=='1') {
                is_T_big = true;
                continue;
            }
            if (S[i]=='1' && T[i]=='0') {
                cout << -1 << endl;
                return;
            }
            if (S[i]=='?' && T[i]=='0') {
                S[i] = '0';
                continue;
            }
            else {
                // 後ろを見て決める
                bool is_ok = false;
                for(ll j=i+1; j<60; j++) {
                    if (S[j]==T[j]) continue;
                    if (S[j]=='1' && T[j]=='0') {
                        S[i] = '0';
                        is_T_big = true;
                        is_ok = true;
                        break;
                    }
                    else {
                        S[i] = '1';
                        is_ok = true;
                        break;
                    }
                }
                if (!is_ok) {
                    S[i] = '1';
                }
                continue;
            }
        }
    }

    // Sを数字になおす
    ll ans = 0;
    reverse(S.begin(), S.end());
    for(ll d=0; d<60; d++) {
        // if (S[d]=='1') ans += (1<<d);
        if (S[d]=='1') ans += (1LL<<d);
    }
    if (ans > N) cout << -1 << endl;
    else cout << ans << endl;
}

int main() {
    solve();
    // solve2();
    // solve3();
    return 0;
}