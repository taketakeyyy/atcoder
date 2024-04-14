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


void solve() {
    ll N; cin >> N;
    string S; cin >> S;
    ll Q; cin >> Q;

    vector<pair<char,ll>> T(N); // T[i] := (文字, 挿入されたターン)
    pair<ll,ll> flip = {-1, -1}; // (小文字(0)か大文字か(1), それをするターン)
    for(ll i=0; i<N; i++) {
        T[i] = {S[i], -1};
    }

    // クエリ処理
    for(ll q=0; q<Q; q++) {
        ll t, x;
        char c;
        cin >> t >> x >> c;
        x--;

        if (t == 1) {
            T[x] = {c, q};
        }
        else if (t == 2) {
            flip = {0, q};
        }
        else {
            flip = {1, q};
        }
    }

    // 答え
    for(ll i=0; i<N; i++) {
        if (flip.first == -1) {
            cout << T[i].first;
        }
        else {
            if (T[i].second < flip.second) {
                // flipに従う
                if (flip.first == 0) {
                    cout << (char)tolower(T[i].first);
                }
                else {
                    cout << (char)toupper(T[i].first);
                }
            }
            else {
                // flipに従わない
                cout << T[i].first;
            }
        }
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}