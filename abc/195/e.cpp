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


// 2人ゲームの基本の考え
// 後ろから考える（最終状態から考える）
// 今回の手番がxのときにxが勝つには、盤面Sから遷移可能な盤面S'のうち、ひとつでも勝ち盤面があるなら、その盤面に行けば勝てるので、Sも勝ち盤面になる
// 逆に、ひとつも勝ち盤面がないなら、どの盤面に遷移しても負けなので、Sも負け盤面になる
void solve() {
    ll N; cin >> N;
    string S; cin >> S;
    string X; cin >> X;

    // dp[i][j] := i番目までの文字まで見て、10進数で表された数(mod 7)がjのとき、高橋が勝つかどうか
    vector<bool> dp(7, false);
    dp[0] = true;
    ll pow10 = 1;
    for(ll i=N-1; i>=0; i--) {
        vector<bool> newdp(7, false);
        ll a = S[i]-'0'; // 今回の値
        a *= pow10;
        a %= 7;
        for(ll j=0; j<7; j++) {
            ll nj = a + j;
            nj %= 7;
            if (X[i]=='T') { // 高橋のターン
                // 高橋が勝つには、盤面Sから遷移可能な盤面S'のうち、ひとつでも勝ち盤面があるなら、その盤面に行けば勝てるので、Sも勝ち盤面になる
                // jから遷移可能な盤面：jとnj
                newdp[j] = dp[j] | dp[nj];
            }
            else {// 青木のターン
                // 青木が勝つには、盤面Sから遷移可能な盤面S'のうち、ひとつでも勝ち盤面があるなら、その盤面に行けば勝てるので、Sも勝ち盤面になる
                // jから遷移可能な盤面:jとnj
                newdp[j] = !(!dp[j] | !dp[nj]);
            }
        }
        pow10 *= 10; pow10 %= 7;
        swap(newdp, dp);
    }

    // 答え
    if (dp[0]) cout << "Takahashi" << endl;
    else cout << "Aoki" << endl;
}


int main() {
    solve();
    return 0;
}