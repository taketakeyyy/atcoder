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

ll N;
vector<string> S;

const ll FIRST_WIN = 100;
ll minimax(ll who_turn, char nxt_ch, ll parent_score, vector<bool> &visited) {
    {// 決着判定
        ll next_i = -1;  // 次の手
        for(ll i=0; i<N; i++) {
            if (visited[i]) continue;
            if (!(nxt_ch==' ' || nxt_ch==S[i][0])) continue;
            next_i = i; break;
        }
        if (next_i == -1) {
            // 使える手がないので、勝負あり
            if (who_turn) return -FIRST_WIN;
            else return FIRST_WIN;
        }
    }

    {// 使える文字があるならそれを使う
        ll res_score;
        if (who_turn) res_score = -FIRST_WIN;
        else res_score = FIRST_WIN;

        for(ll i=0; i<N; i++) {
            if (visited[i]) continue;
            if (!(nxt_ch==' ' || nxt_ch==S[i][0])) continue;
            visited[i] = true;
            ll child_score = minimax(who_turn^1, S[i][1], res_score, visited);
            if (who_turn) {
                // Firstのターンなら、最善手を見つける
                if (child_score > res_score) res_score = child_score;
            }
            else {
                // Secondのターンなら、最悪手を見つける
                if (child_score < res_score) res_score = child_score;
            }
            visited[i] = false;

            if (who_turn) {
                if (res_score > parent_score) break;  // βカット
            }
            else {
                if (res_score < parent_score) break;  // αカット
            }
        }
        return res_score;
    }
}

// 2^16 = 65536
// minimax解法。TLEした。
void solve() {
    cin >> N;
    S.resize(N);
    for(ll i=0; i<N; i++) {
        string s; cin >> s;
        S[i] = {s[0], s[s.size()-1]}; //最初と最後の文字しか要らない
    }

    // minimax
    vector<bool> visited(N, false);
    ll result = minimax(1, ' ', 0, visited);
    if (result == FIRST_WIN) cout << "First" << endl;
    else cout << "Second" << endl;
}

// bitDP解法。
void solve2() {
    cin >> N;
    S.resize(N);
    for(ll i=0; i<N; i++) {
        string s; cin >> s;
        S[i] = {s[0], s[s.size()-1]}; //最初と最後の文字しか要らない
    }

    // しりとりのグラフGを作成
    vector G(N, set<ll>()); // G[i] := 単語iから行ける単語の集合
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            if (i == j) continue;
            if (S[i][1] == S[j][0]) {
                G[i].insert(j);
            }
        }
    }

    // dp[state][i] := すでに使った単語の集合がstateで、現在の単語がiのときに、Firstが勝てるか
    vector dp(1<<N, vector<bool>(N, false));

    for(ll bit=0; bit<(1<<N); bit++) {
        for(ll i=0; i<N; i++) {  // 現在の単語
            if (~bit>>i&1) continue;  // まだ使ってない
            for(ll j=0; j<N; j++) {  // 次の単語
                if (bit>>j&1) continue;  // すでに使った
                if (!G[i].count(j)) continue;
                // iを使っていて、まだjを使っていないなら
                dp[bit|1<<j][j] = dp[bit][i]|1;  // ここわからん???????????
            }
        }
    }
}

// 解説AC
// memo化再帰で全探索
void solve3() {
    cin >> N;
    S.resize(N);
    for(ll i=0; i<N; i++) {
        string s; cin >> s;
        S[i] = {s[0], s[s.size()-1]}; //最初と最後の文字しか要らない
    }

    // メモ化再帰で解く
    vector memo(1<<N, vector<bool>(N));  // memo[state][i] := f(f,state,i)はメモ済みか？
    vector val(1<<N, vector<bool>(N));  // f(f,state,i)の値のメモ値
    // f(f, state, p) := すでに使った単語がstateで、現在の単語がpのときに、勝てるか
    auto f = [&](auto f, ll state, ll p) -> bool {
        if (memo[state][p]) return val[state][p];
        bool res = false;
        for(ll i=0; i<N; i++) { // 次の単語
            if (state>>i&1) continue;  // すでに使っていたら
            if (S[p][1] != S[i][0]) continue;  // 前の文字と違ったら
            res |= !f(f,state|1<<i,i);  // ここがわからない。なんでこれでいいのか?????????
        }
        memo[state][p] = true;
        val[state][p] = res;
        return res;
    };

    for(ll i=0; i<N; i++) {
        if (!f(f,1<<i,i)) { // なぜこれでいいのか????????
            cout << "First" << endl;
            return;
        }
    }
    cout << "Second" << endl;
}


void solve4() {
    cin >> N;
    S.resize(N);
    for(ll i=0; i<N; i++) {
        string s; cin >> s;
        S[i] = {s[0], s[s.size()-1]}; //最初と最後の文字しか要らない
    }

    // メモ化再帰で解く
    vector memo(1<<N, vector<bool>(N));  // memo[state][i] := f(f,state,i)はメモ済みか？
    vector val(1<<N, vector<bool>(N));  // f(f,state,i)の値のメモ値
    // f(f, state, p) := すでに使った単語がstateで、現在の単語がpのときに、Firstが勝てるか
    auto f = [&](auto f, ll state, ll p, ll depth) -> bool {
        if (memo[state][p]) return val[state][p];
        bool res = false;
        for(ll i=0; i<N; i++) { // 次の単語
            if (state>>i&1) continue;  // すでに使っていたら
            if (S[p][1] != S[i][0]) continue;  // 前の文字と違ったら
            res |= !f(f,state|1<<i,i,depth+1);  // ここがわからない
        }
        memo[state][p] = true;
        val[state][p] = res;
        return res;
    };

    for(ll i=0; i<N; i++) {
        if (!f(f,1<<i,i,0)) {
            cout << "First" << endl;
            return;
        }
    }
    cout << "Second" << endl;
}

int main() {
    // solve();
    solve3();
    return 0;
}