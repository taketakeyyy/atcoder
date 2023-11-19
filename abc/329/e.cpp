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


// 逆から見ていく。
// X = ####### の状態から S=ABCBABC へいけるかどうかではなく、
// X = ABCBABC の状態から X=####### へいけるかどうかを調べる。
// T=ABCのスタンプを押したところをワイルドカードにしていく
// X = ???BABC (?はワイルドカード)
// X = ???B???
// X = ???????
void solve() {
    ll N, M; cin >> N >> M;
    string S, T; cin >> S >> T;
    string X = S;

    vector<ll> is_stack(N, false); // スタックに積んだインデックス
    stack<ll> stk;
    {// Xの中からTを探し、それをワイルドカード'?'に変える
        auto pos = X.find(T);
        while(pos != string::npos) {
            for(ll i=0; i<M; i++) {
                X[pos+i] = '?';
            }

            // '?'に変えた端の(M-1)個分をスタックに積む
            for(ll i=pos-1; i>=(ll)pos-(M-1); i--) {
                if (i < 0) break;
                if (X[i] == '?') continue;
                stk.push(i);
                is_stack[i] = true;
            }
            for(ll i=pos+(M-1)+1; i<=(ll)pos+(M-1)+(M-1); i++) {
                if (i >= N) break;
                if (X[i] == '?') continue;
                stk.push(i);
                is_stack[i] = true;
            }

            pos = X.find(T, pos+T.size());
        }
    }

    // Xの位置posにTのスタンプを押せるところを探して、押せたら押す
    auto match = [&](ll pos) -> void {
        if (X[pos] == '?') return;

        for(ll s=pos-(M-1); s<=pos; s++) {
            if (s < 0) continue;
            bool is_ok = true;
            for(ll i=0; i<M; i++) {
                if (s+i >= N) {
                    is_ok = false;
                    break;
                }
                if (X[s+i]=='?' or X[s+i]==T[i]) continue;
                is_ok = false;
                break;
            }
            if (!is_ok) continue;
            // スタンプ押せる
            for(ll i=0; i<M; i++) {
                X[s+i] = '?';
            }
            // 端の(M-1)個分をスタックに積む
            for(ll i=s; i>=s-(M-1); i--) {
                if (i < 0) break;
                if (X[i] == '?') continue;
                if (is_stack[i]) continue;
                is_stack[i] = true;
                stk.push(i);
            }
            for(ll i=s+(M-1)+1; i<=s+(M-1)+(M-1); i++) {
                if (i >= N) break;
                if (X[i] == '?') continue;
                if (is_stack[i]) continue;
                is_stack[i] = true;
                stk.push(i);
            }
        }
    };

    // スタックが空になるまでスタンプを押せる箇所を探す。
    while(!stk.empty()) {
        ll pos = stk.top(); stk.pop();
        is_stack[pos] = false;
        match(pos);
    }

    // すべて?になったか
    bool is_ok = true;
    for(ll i=0; i<N; i++) {
        if (X[i] != '?') {
            is_ok = false;
            break;
        }
    }
    if (is_ok) cout << "Yes" << endl;
    else cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}