#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;


void solve() {
    ll T; cin >> T;
    for(ll t=0; t<T; t++) {
        ll N, K; cin >> N >> K;
        vector<ll> A(N), B(N);
        for(ll i=0; i<N; i++) cin >> A[i];
        for(ll i=0; i<N; i++) cin >> B[i];

        // (a,b)を、aの値が小さい順にソートする
        vector<pair<ll,ll>> AB(N);
        for(ll i=0; i<N; i++) AB[i] = {A[i],B[i]};
        sort(AB.begin(), AB.end());

        ll ans = INF;
        // Bの小さいものK-1個を、プライオリティキューで管理する
        priority_queue<ll> pq;  // 大きい順を維持する優先度付きキュー
        ll sumB = 0; // Bの和
        for(ll i=0; i<N; i++) {
            auto[a, b] = AB[i];
            if ((ll)pq.size() == K-1) {
                chmin(ans, a*(sumB+b));
            }
            pq.push(b);
            sumB += b;
            if ((ll)pq.size() > K-1) {
                // Bの最も大きいものを削除
                sumB -= pq.top();
                pq.pop();
            }
        }

        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}