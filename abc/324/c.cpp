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


void solve() {
    ll N; string T; cin >> N >> T;

    vector<ll> anss;
    for(ll i=0; i<N; i++) {
        string S; cin >> S;
        if (S == T) {
            anss.push_back(i);
            continue;
        }
        else if ((ll)S.size() == (ll)T.size()+1) {
            // 1文字追加されたやつか？
            ll ti = 0;
            ll miss = 0;
            for(ll si=0; si<(ll)S.size(); si++) {
                if (S[si] == T[ti]) {
                    ti++;
                    continue;
                }
                else {
                    miss++;
                    continue;
                }
            }

            if (miss == 1) {
                anss.push_back(i);
                continue;
            }
        }
        else if ((ll)S.size()+1 == (ll)T.size()) {
            // 1文字削除されたやつか？
            ll si = 0;
            ll miss = 0;
            for(ll ti=0; ti<(ll)T.size(); ti++) {
                if (T[ti] == S[si]) {
                    si++;
                    continue;
                }
                else {
                    miss++;
                    continue;
                }
            }

            if (miss == 1) {
                anss.push_back(i);
            }
        }
        else if ((ll)S.size() == (ll)T.size()) {
            // 1文字を別の文字に入れ替えたやつか？
            ll miss = 0;
            for(ll j=0; j<(ll)S.size(); j++) {
                if (S[j] == T[j]) continue;
                else {
                    miss++;
                }
            }

            if (miss == 1) {
                anss.push_back(i);
            }
        }
    }

    // 出力
    sort(anss.begin(), anss.end());
    cout << (ll)anss.size() << endl;
    for(ll ans : anss) {
        cout << ans+1 << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}