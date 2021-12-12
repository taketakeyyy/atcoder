#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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


void solve() {
    string S; cin >> S;
    ll K; cin >> K;

    // K==0のときはそのまま数える
    if (K == 0) {
        ll ans = 0;
        ll seq = 0;
        for(ll i=0; i<S.size(); i++) {
            if (S[i]=='X') {
                seq++;
            }
            else {
                seq = 0;
            }
            ans = max(ans, seq);
        }
        cout << ans << endl;
        return;
    }


    vector<ll> dot_idx;  // ドットのインデックスを格納
    for(ll i=0; i<(ll)S.size(); i++) {
        if (S[i]=='.') dot_idx.push_back(i);
    }

    ll N = S.size();
    vector<ll> L(N, -1);  // 連続するXの左端の位置
    vector<ll> R(N, -1);  // 連続するXの右端の位置

    // Lを作る
    if (S[0]=='X') {
        L[0] = 0;
    }
    for(ll i=1; i<N; i++) {
        if (S[i]=='X' && S[i-1]=='X') {
            L[i] = L[i-1];
        }
        else if (S[i]=='X' && S[i-1]=='.') {
            L[i] = i;
        }
    }

    // Rを作る
    if (S[N-1]=='X') {
        R[N-1] = N-1;
    }
    for(ll i=N-2; i>=0; i--) {
        if (S[i]=='X' && S[i+1]=='X') {
            R[i] = R[i+1];
        }
        else if (S[i]=='X' && S[i+1]=='.') {
            R[i] = i;
        }
    }

    // 答えを探索
    ll ans = 0;
    if (dot_idx.size() != 0) {
        for(ll i=0; i<(ll)dot_idx.size(); i++) {
            ll ldot_idx = dot_idx[i];
            ll rdot_idx;
            if (i+K-1 < (ll)dot_idx.size()) {
                rdot_idx = dot_idx[i+K-1];
            }
            else {
                rdot_idx = N-1;
            }

            // 左の位置を探索
            ll l;
            if (ldot_idx-1 >= 0) {
                if (L[ldot_idx-1] != -1) {
                    l = L[ldot_idx-1];
                }
                else {
                    l = ldot_idx;
                }
            }
            else {
                l = 0;
            }

            // 右の位置を探索
            ll r;
            if (rdot_idx+1 <= N-1) {
                if (R[rdot_idx+1] != -1) {
                    r = R[rdot_idx+1];
                }
                else {
                    r = rdot_idx;
                }
            }
            else {
                r = N-1;
            }

            ans = max(ans, r-l+1);
        }
    }
    else {
        ans = S.size();
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}