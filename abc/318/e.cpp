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


// 解説AC(nok0)
// ・(i,j,k)のjに着目する
// ・不変量を考える
void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    map<ll,vector<ll>> a2idx; // Aの値のインデックスのリスト
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        a2idx[A[i]].push_back(i);
    }

    auto count = [&](vector<ll> &vec, ll j) {
        ll left_num = lower_bound(vec.begin(), vec.end(), j) - vec.begin();
        ll right_num = lower_bound(vec.begin(), vec.end(), j) - vec.begin();
        right_num = (ll)vec.size() - right_num;
        return left_num * right_num;
    };

    // 不変量を考える。totalはあまり変わらない
    ll total = 0;
    ll ans = 0;
    {// j=1のとき計算
        ll j = 1;
        for(auto[a, vec]: a2idx) {
            total += count(vec, j);
        }

        // A[j]を引く
        ll diff = count(a2idx[A[j]], j);

        ans = total - diff;

        if (A[j] != A[j+1]) {
            total -= count(a2idx[A[j]], j);
            total -= count(a2idx[A[j+1]], j);
        }
        else {
            total -= count(a2idx[A[j]], j);
        }
    }

    for(ll j=2; j<=N-2; j++) {
        if (A[j] != A[j-1]) {
            total += count(a2idx[A[j]], j);
            total += count(a2idx[A[j-1]], j);
        }
        else {
            total += count(a2idx[A[j]], j);
        }
        ll diff = count(a2idx[A[j]], j);
        ans += total - diff;

        if (A[j] != A[j+1]) {
            total -= count(a2idx[A[j]], j);
            total -= count(a2idx[A[j+1]], j);
        }
        else {
            total -= count(a2idx[A[j]], j);
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}