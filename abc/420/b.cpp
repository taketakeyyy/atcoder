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
// 初項a, 末項l, 項数n のときの等差数列の和
ll tousa1(const ll &a, const ll &l, const ll &n) { return ((a+l)*n)/2; }
// 初項a, 公差d, 項数n のときの等差数列の和
ll tousa2(const ll &a, const ll &d, const ll &n) { return ((2*a+(n-1)*d)*n)/2; }


void solve() {
    ll N, M; cin >> N >> M;
    vector<string> S(N);
    for(ll i=0; i<N; i++) {
        cin >> S[i];
    }

    vector<ll> score(N, 0LL);
    for(ll i=0; i<M; i++) {
        ll one = 0;
        ll zero = 0;
        for(ll j=0; j<N; j++) {
            if (S[j][i] == '1') one++;
            else zero++;
        }

        if (zero==0 or one==0) {
            for(ll j=0; j<N; j++) score[j]++;
        }
        else if (zero < one) {
            for(ll j=0; j<N; j++) {
                if (S[j][i] == '0') score[j]++;
            }
        }
        else {
            for(ll j=0; j<N; j++) {
                if (S[j][i] == '1') score[j]++;
            }
        }
    }

    // （スコア、人ID）
    vector<pair<ll,ll>> pairs(N);
    for(ll i=0 ;i<N; i++) {
        pairs[i] = {score[i], i};
    }
    sort(pairs.begin(), pairs.end());
    reverse(pairs.begin(), pairs.end());

    ll max_score = pairs[0].first;
    vector<ll> ans; ans.push_back(pairs[0].second);
    for(ll i=1; i<N; i++) {
        if (pairs[i].first < max_score) break;
        ans.push_back(pairs[i].second);
    }

    // answer
    sort(ans.begin(), ans.end());
    for(ll i=0; i<(ll)ans.size(); i++) {
        cout << ans[i]+1 << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}