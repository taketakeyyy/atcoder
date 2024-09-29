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
    ll N, M, K; cin >> N >> M >> K;
    vector<pair<ll,ll>> A(N); // (票数,人id)
    ll sumA = 0;
    for(ll i=0; i<N; i++) {
        ll a; cin >> a;
        A[i] = {a, i};
        sumA += a;
    }
    sort(A.begin(), A.end());

    // エッジケース
    if (N == M) {
        for(ll i=0; i<N; i++) cout << 0 << " ";
        cout << endl;
        return;
    }

    vector<ll> id2idx(N);
    for(ll i=0; i<N; i++) {
        auto[_, id] = A[i];
        id2idx[id] = i;
    }

    // 累積和
    vector<ll> S(N+1, 0);
    for(ll i=1; i<=N; i++) S[i] = S[i-1] + A[i-1].first;

    // 人idの票数に+xしたとき、当選するかどうか
    auto judge = [&](ll id, ll x, ll restK) -> bool {
        // 票数limit以上の人間がM人以上いたら、人idは落選する
        ll idx = id2idx[id];
        ll limit = A[idx].first + x + 1;

        // [l,r]の区間の人間に、limit以上の票を配りたい
        ll r = lower_bound(A.begin(), A.end(), make_pair(limit, INF)) - A.begin();
        ll l = N-M;
        if (r < l) return false;

        // 人id以外のM人を、limit以上の票数にするための必要票数needを計算する
        ll need = (limit)*(r-l) - (S[r]-S[l]);
        if (l<=idx and idx<r) {
            need += A[idx].first;
            need -= A[l-1].first;
        }
        return need > restK;
    };

    ll restK = K - sumA;
    for(ll id=0; id<N; id++) {
        ll l = 0;
        ll r = restK;
        while(r-l > 1) {
            ll mid = (l+r)/2;
            if (judge(id,mid,restK-mid)) r = mid;
            else l = mid;
        }
        if (judge(id,l,restK-l)) cout << l << " ";
        else if (judge(id,r,restK-r)) cout << r << " ";
        else cout << -1 << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}