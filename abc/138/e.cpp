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


void solve() {
    string S, T;
    cin >> S >> T;

    // pos[ch] := 文字chのインデックスのリスト
    map<char,vector<ll>> pos;
    for(ll i=0; i<(ll)S.size(); i++) {
        pos[S[i]].push_back(i);
    }

    ll ans = 0;
    ll idx = 0; // 現在のインデックス
    for(ll i=0; i<(ll)T.size(); i++) {
        char t = T[i];

        // 「インデックスidx以上で、最初に文字tが現れる位置は？」
        while(1) {
            auto it = lower_bound(pos[t].begin(), pos[t].end(), idx);
            if (it == pos[t].end()) {
                // 見つからなかった
                if (idx == 0) {
                    // インデックス0以降から探して見つからない場合、そもそも存在しない文字
                    cout << -1 << endl;
                    return;
                }
                else {
                    // インデックスを0にして再び探す
                    ans += (ll)S.size();
                    idx = 0;
                    continue;
                }
            }
            else {
                // 見つかった
                idx = (*it) + 1;
                break;
            }
        }
    }
    ans += idx;
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}