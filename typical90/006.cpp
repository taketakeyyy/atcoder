#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll N, K; cin >> N >> K;
    string S; cin >> S;

    // dp[i][ch] := 文字列Sの位置i番目の時点で、最も左にある文字chのインデックス番号
    vector<map<char, ll>> dp(N);
    for(int i=0; i<26; i++) {
        dp[N-1][(char)('a'+i)] = INF;
    }
    dp[N-1][S[N-1]] = N-1;

    for(int i=N-2; i>=0; i--) {
        for(int j=0; j<26; j++) {
            dp[i][(char)('a'+j)] = dp[i+1][(char)('a'+j)];
        }
        dp[i][S[i]] = i;
    }

    // 辞書順最小の文字列を貪欲に作成する
    string ans = "";
    int pos = 0;
    for(int i=1; i<=K; i++) {  // K文字の文字列を作るので、K回繰り返す
        for(int j=0; j<26; j++) {  // 次に選べる文字を、aから順に走査する
            int nxpos = dp[pos][(char)('a'+j)];  // 次に選ぶ文字の、最左のインデックス番号
            if ((int)ans.size()+(N-nxpos) >= K) { // nxposの文字以降すべてを選んだときに作れる文字列の長さがK以上なら、nxposを選んでもOK（nxposの文字を選んでもK文字作れるか？）
                ans += (char)('a'+j);
                pos = nxpos + 1;
                break;
            }
        }
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}