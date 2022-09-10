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

ll K;  // _ の長さの最大値
ll N, M;
set<string> Ts;

void dfs(string ans, ll i, vector<string> &Ss) {
    if (i == N) {
        if ((ll)ans.size() > 16 || (ll)ans.size() < 3) {
            return;
        }
        if (Ts.count(ans)) return;
        cout << ans << endl;
        exit(0);  // 終了
    }

    ans += Ss[i];
    if (i != N-1) {
        ll origin_len = (ll)ans.size();
        for(ll k=1; k<=K; k++) {
            for(ll j=1; j<=k; j++) {
                ans += "_";
            }
            if ((ll)ans.size() <= 16) {  // 枝切り
                dfs(ans, i+1, Ss);
            }
            ans = ans.substr(0, origin_len);
        }
    }
    else {
        dfs(ans, i+1, Ss);
    }
}


void solve() {
    cin >> N >> M;
    vector<string> Ss(N);
    ll total_len = 0;
    for(ll i=0; i<N; i++) {
        cin >> Ss[i];
        total_len += (ll)Ss[i].size();
    }
    for(ll i=0; i<M; i++) {
        string t; cin >> t;
        Ts.insert(t);
    }

    if (N >= 2) {
        K = (16-total_len) - (N-1) + 1;  // (残りの文字数) - (_を挟む個数) + 1
        if (K <= 0) {
            cout << -1 << endl;
            return;
        }
    }
    else {
        K = 1;
    }

    sort(Ss.begin(), Ss.end());
    do {
        string ans = "";
        dfs(ans, 0, Ss);
    }while(next_permutation(Ss.begin(), Ss.end()));
    cout << -1 << endl;
}


int main() {
    solve();
    return 0;
}