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

ll T;
const ll BEAM_WIDTH = 10000;
const ll N = 20;

struct State {
    ll score;  // スコア
    vector<ll> X;  // 現在のXの状態
    char last_move;  // 最後の動き'A' or 'B';
    ll last_pos;  // beam[i-1][どこ]から遷移したか
};
bool operator> (const State &s1, const State &s2) {
    return (s1.score > s2.score);
}
bool operator< (const State &s1, const State &s2) {
    return (s1.score < s2.score);
}

ll calc_score(vector<ll> const &X) {
    ll score = 0;
    for(ll i=1; i<(ll)X.size(); i++) {
        score += (X[i]==0)? 1:0;
    }
    return score;
}

/**
 * @brief ビームサーチする
 *
 * @return vector<char>
 */
vector<char> beam_search_solver() {
    // beam[t][i] := tターン目のi個目の状態
    vector<vector<State>> beam(T+1);
    beam[0].push_back(State{0,vector<ll>(N+1,0),'?',-1});

    for(ll i=1; i<=T; i++) {
        ll p, q, r;
        cin >> p >> q >> r;

        vector<State> candidates;  // ビームサーチの候補
        for(ll j=0; j<(ll)beam[i-1].size(); j++) {
            {// 操作Aの場合
                State state = beam[i-1][j];
                state.last_move = 'A';
                state.last_pos = j;
                state.X[p]++;
                state.X[q]++;
                state.X[r]++;
                state.score += calc_score(state.X);
                candidates.push_back(state);
            }
            {// 操作Bの場合
                State state = beam[i-1][j];
                state.last_move = 'B';
                state.last_pos = j;
                state.X[p]--;
                state.X[q]--;
                state.X[r]--;
                state.score += calc_score(state.X);
                candidates.push_back(state);
            }
        }

        // ソートして上位BEAM_WIDTHだけ採用する
        sort(candidates.begin(), candidates.end());
        reverse(candidates.begin(), candidates.end());
        ll mxj = min(BEAM_WIDTH, (ll)candidates.size());
        for(ll j=0; j<mxj; j++) beam[i].push_back(candidates[j]);
    }

    // 操作手順を復元する
    vector<char> ans;
    {
        ll j = 0;
        for(ll i=T; i>=1; i--) {
            ans.push_back(beam[i][j].last_move);
            j = beam[i][j].last_pos;
        }
    }
    reverse(ans.begin(), ans.end());

    return ans;
}

void output_answer(vector<char> ans) {
    for(ll i=0; i<(ll)ans.size(); i++) {
        cout << ans[i] << endl;
    }
}

void solve() {
    cin >> T;

    vector<char> ans = beam_search_solver();

    output_answer(ans);
}


int main() {
    solve();
    return 0;
}