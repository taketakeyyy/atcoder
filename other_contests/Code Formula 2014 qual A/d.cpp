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


// 試行錯誤AC
void solve() {
    string S; cin >> S;
    string K; cin >> K;
    // const ll ALL_KEY_NUM = 26+10; // すべてのキートップの種類
    string ALL_KEY_STRING = "1234567890abcdefghijklmnopqrstuvwxyz"; // 全文字種

    // キー位置不明の文字種
    set<char> unknown;
    for(char c: ALL_KEY_STRING) unknown.insert(c);
    for(char k: K) unknown.erase(k);

    // キー位置不明かつ、Sに含まれている文字種の数
    set<char> unknown_S;
    for(char c: S) {
        if (unknown.count(c)) unknown_S.insert(c);
    }

    // S中に重複している位置不明キーの数（確率1で確定して押せるキーの数）
    ll fix_num = S.size() - unknown_S.size();

    // dp[i][a][b] := 現在、i文字目を入力しようとしていて、キー位置がわからない文字種がa個で、キー位置がわからないSの文字種がb個の状態で、終了するまでに叩くキーの回数の期待値
    ll UNKNOWN_NUM = unknown.size();
    ll UNKNOWN_S_NUM = unknown_S.size();
    vector dp(S.size()+1, vector<vector<double>>(UNKNOWN_NUM+1, vector<double>(UNKNOWN_S_NUM+1, 0)));
    for(ll i=(ll)S.size()-1; i>=0; i--) {
        if (unknown_S.count(S[i])) {
            // i文字目のキートップの位置が不明なとき
            for(ll a=1; a<UNKNOWN_NUM+1; a++) {
                for(ll b=1; b<UNKNOWN_S_NUM+1; b++) {
                    if (a < b) break; // ありえない
                    double p1 = (double)(a-b)/a; // Sに属さない不明なキーを叩く確率
                    double p2 = (double)(b-1)/a; // S[i]ではないが、Sに属す不明なキーを叩く確率
                    double p3 = (double)1/a; // S[i]のキーを叩く確率
                    dp[i][a][b] = p1*(2+dp[i][a-1][b]) + p2*(3+dp[i][a-1][b-1]) + p3*(1+dp[i+1][a-1][b-1]);
                    // dp[i][a][b] = p1*(2+dp[i][a-1][b]) + p2*(2+dp[i][a-1][b-1]) + p3*(1+dp[i+1][a-1][b-1]);
                }
            }
            unknown_S.erase(S[i]); // 2回目以降は知っている扱いする
            unknown.erase(S[i]);
        }
        else {
            // i文字目のキートップの位置がわかっているとき
            for(ll a=0; a<UNKNOWN_NUM+1; a++) {
                for(ll b=0; b<UNKNOWN_S_NUM+1; b++) {
                    if (a < b) break; // ありえない
                    // dp[i][a][b] = 1+dp[i+1][a][b];
                    dp[i][a][b] = dp[i+1][a][b];
                }
            }
        }
    }

    double ans = fix_num + dp[0][UNKNOWN_NUM][UNKNOWN_S_NUM];
    printf("%.10lf\n", ans);
}


// 完全理解AC
void solve2() {
    string S; cin >> S;
    string K; cin >> K;
    string ALL_KEY_STRING = "1234567890abcdefghijklmnopqrstuvwxyz"; // 全文字種

    // キー位置不明の文字種
    set<char> unknown;
    for(char c: ALL_KEY_STRING) unknown.insert(c);
    for(char k: K) unknown.erase(k);

    // キー位置不明かつ、Sに含まれている文字種の数
    set<char> unknown_S;
    for(char c: S) {
        if (unknown.count(c)) unknown_S.insert(c);
    }

    // S中の確率1で確定して押せるキーの数
    ll fix_num = S.size() - unknown_S.size();

    // 文字列Sから、重複文字を削除した文字列S2を作る
    set<char> S_set = set(S.begin(), S.end());
    string S2 = "";
    for(char c: S_set) S2 += c;

    // dp[i][a][b] := 現在、i文字目を入力しようとしていて、キー位置がわからない文字種がa個で、キー位置がわからないSの文字種がb個の状態で、終了するまでに叩くキーの回数の期待値
    ll UNKNOWN_NUM = unknown.size();
    ll UNKNOWN_S_NUM = unknown_S.size();
    vector dp(S2.size()+1, vector<vector<double>>(UNKNOWN_NUM+1, vector<double>(UNKNOWN_S_NUM+1, 0)));
    for(ll i=(ll)S2.size()-1; i>=0; i--) {
        // i文字目のキートップの位置が不明なとき
        for(ll a=1; a<UNKNOWN_NUM+1; a++) {
            for(ll b=1; b<UNKNOWN_S_NUM+1; b++) {
                if (a < b) break; // ありえない
                double p1 = (double)(a-b)/a; // Sに属さない不明なキーを叩く確率
                double p2 = (double)(b-1)/a; // S[i]ではないが、Sに属す不明なキーを叩く確率
                double p3 = (double)1/a; // S[i]のキーを叩く確率
                dp[i][a][b] = p1*(2+dp[i][a-1][b]) + p2*(3+dp[i][a-1][b-1]) + p3*(1+dp[i+1][a-1][b-1]);
            }
        }
    }

    double ans = fix_num + dp[0][UNKNOWN_NUM][UNKNOWN_S_NUM];
    printf("%.10lf\n", ans);
}


int main() {
    // solve();
    solve2();
    return 0;
}