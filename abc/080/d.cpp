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


// この問題、時刻sから時刻tまで放送されるとき、[s, t-1]まで放送されるという意味っぽい
// (s,t)=(1,10)のとき、放送時間は[1, 9.999...]ではなく、[1, 9]
void solve() {
    ll N, C; cin >> N >> C;
    vector<ll> s(N), t(N), c(N);

    // channel[c][i] := チャンネルcが、時刻iに放送されているなら1
    vector channel(C, vector<ll>(100000+5, 0));
    for(ll i=0; i<N; i++) {
        ll s, t, c; cin >> s >> t >> c;
        c--;
        // 放送時間は[s, t-1]まで
        channel[c][s] += 1;
        channel[c][t] -= 1;
    }
    for(ll c=0; c<C; c++) {
        for(ll i=1; i<(ll)channel[c].size(); i++) {
            channel[c][i] += channel[c][i-1];
        }
    }

    // imos[i] := 時刻iに必要な録画機の数
    vector<ll> imos(100000+5, 0);
    for(ll c=0; c<C; c++) {
        bool is_seq = false;  // 放送中か？
        for(ll i=1; i<(ll)channel[c].size(); i++) {
            if (!is_seq && channel[c][i] == 1) {
                is_seq = true;
                imos[i-1] += 1;  // 「S-0.5は録画できない」ので、時刻1個分前から録画する必要がある
                continue;
            }
            if (is_seq && channel[c][i]==0) {
                is_seq = false;
                imos[i] -= 1;
                continue;
            }
        }
    }

    // 各時刻において、必要な録画機の最大値が答え。
    ll ans = 1;
    for(ll i=1; i<(ll)imos.size(); i++) {
        imos[i] += imos[i-1];
        ans = max(ans, imos[i]);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}