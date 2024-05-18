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
    ll N; cin >> N;
    vector<ll> A(N), B(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i] >> B[i];
    }

    const ll TAKA = 0; // 高橋の値
    // const ll AOKI = 1;

    // まだカードを選ぶことができるか？
    auto can_select = [&](const ll &state) -> bool {
        for(ll i=0; i<N; i++) {
            if (state>>i&1) continue;
            for(ll j=i+1; j<N; j++) {
                if (state>>j&1) continue;
                if (A[i]==A[j] or B[i]==B[j]) return true;
            }
        }
        return false;
    };

     // f(f, state, who_turn) := 現在のカードの状態がstateで、手番がwho_turnのときは、誰の勝ち盤面か
    vector<ll> memo(1LL<<N, -1); // memo[state] := 現在の状態がstateのとき、誰の勝ち盤面か
    auto f = [&](auto f, ll state, ll who_turn) -> ll {
        // 終了条件
        if (memo[state] != -1) return memo[state]; // これ忘れてTLEした！！！
        if (can_select(state) == false) {
            return memo[state] = who_turn^1LL; // who_turnの負け
        }

        // 次の探索
        for(ll i=0; i<N; i++) {
            if (state>>i&1) continue;
            for(ll j=i+1; j<N; j++) {
                if (state>>j&1) continue;
                if (A[i]==A[j] or B[i]==B[j]) {
                    ll nstate = state;
                    nstate |= 1LL<<i;
                    nstate |= 1LL<<j;
                    ll res = f(f, nstate, who_turn^1LL);
                    if (res == who_turn) { // 遷移先にひとつでも勝ちパターンがあったら、現在のwho_turnの勝ち
                        return memo[state] = who_turn;
                    }
                }
            }
        }

        // ひとつも勝ちパターンがなかったので、who_turnの負け
        return memo[state] = who_turn^1LL;
    };
    f(f, 0LL, TAKA);
    if (memo[0] == TAKA) cout << "Takahashi" << endl;
    else cout << "Aoki" << endl;
}


int main() {
    solve();
    return 0;
}