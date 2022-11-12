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
    ll N; cin >> N;
    vector<ll> P(N);
    for(ll i=0; i<N; i++) cin >> P[i];

    set<ll> set_cands;
    vector<ll> cands;
    cands.push_back(P[N-1]);
    set_cands.insert(P[N-1]);
    for(ll i=N-2; i>=0; i--) {
        ll p = P[i];
        ll idx = lower_bound(cands.begin(), cands.end(), p) - cands.begin();
        if (idx == 0) {
            // pより小さい値が存在しない
            cands.push_back(p);
            sort(cands.begin(), cands.end());
            continue;
        }
        else {
            // pより小さい直近の値が見つかった
            idx--;
            ll a = cands[idx];
            cands[idx] = p;
            sort(cands.begin(), cands.end());
            reverse(cands.begin(), cands.end());

            // 出力
            for(ll n=0; n<N; n++) {
                if (n == i) break;
                cout << P[n] << " ";
            }
            cout << a << " ";
            for(ll n=0; n<(ll)cands.size(); n++) {
                cout << cands[n] << " ";
            }
            cout << endl;
            return;
        }
    }
}


int main() {
    solve();
    return 0;
}