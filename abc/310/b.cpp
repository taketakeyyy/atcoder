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
    ll N, M; cin >> N >> M;
    vector<ll> P(N), C(N);
    vector<set<ll>> F(N);
    for(ll i=0; i<N; i++) {
        cin >> P[i] >> C[i];
        for(ll j=0; j<C[i]; j++) {
            ll f; cin >> f;
            F[i].insert(f);
        }
    }

    // jはiの上位互換か？
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            if (i == j) continue;
            if (P[i] >= P[j]) {
                bool is_have = true;
                for(ll f: F[i]) {
                    if (F[j].count(f)) continue;
                    is_have = false;
                    break;
                }
                if (is_have) {
                    if (P[i] > P[j]) {
                        cout << "Yes" << endl;
                        return;
                    }
                    else {
                        // j番目の製品はi番目の製品にない機能を1つ以上持つか？
                        if (F[j].size() > F[i].size()) {
                            cout << "Yes" << endl;
                            return;
                        }
                    }
                }
            }
        }
    }
    cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}