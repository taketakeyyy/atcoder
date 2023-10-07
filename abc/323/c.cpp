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
    ll N, M; cin >> N >> M;
    vector<ll> A(M);
    for(ll i=0; i<M; i++) cin >> A[i];
    vector<string> S(N);
    for(ll i=0; i<N; i++) cin >> S[i];

    vector<ll> point(N, 0); // i番目の人の現在のポイント
    for(ll i=0; i<N; i++) {
        point[i] += i+1;
        for(ll j=0; j<M; j++) {
            if (S[i][j] == 'o') {
                point[i] += A[j];
            }
        }
    }

    // 最大点数
    ll max_point = 0;
    for(ll i=0; i<N; i++) {
        max_point = max(max_point, point[i]);
    }

    // A2
    vector<pair<ll,ll>> A2; // (得点、 問題番号)
    for(ll i=0; i<M; i++) {
        A2.push_back({A[i], i});
    }
    sort(A2.begin(), A2.end());
    reverse(A2.begin(), A2.end());

    // 各クエリに答える
    for(ll i=0; i<N; i++) {
        if (point[i] == max_point) {
            cout << 0 << endl;
            continue;
        }

        ll ans = 0;
        ll rest_point = max_point - point[i];
        for(ll j=0; j<M; j++) {
            auto[p, id] = A2[j];
            if (S[i][id] == 'o') continue;
            ans++;
            rest_point -= p;
            if (rest_point < 0) break;
        }
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}