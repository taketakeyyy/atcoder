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
    ll N, Q; cin >> N >> Q;
    vector<ll> X(Q+1);
    for(ll i=1; i<=Q; i++) cin >> X[i];
    vector<ll> A(N+1, 0LL);

    // 必要になったら足す
    vector<ll> rui(Q+1, 0LL); // クエリqまでの、Aに足す値の累積和
    unordered_map<ll,ll> when; // when[x] := 集合Sにxが追加されたタイミング
    unordered_set<ll> S;
    for(ll q=1; q<=Q; q++) {
        ll x = X[q];
        if (S.contains(x)) {
            S.erase(x);

            // 削除タイミングでAに足す
            A[x] += rui[q-1]-rui[when[x]-1];
            when[x] = -1;
        }
        else {
            S.insert(x);
            when[x] = q;
        }
        rui[q] = rui[q-1] + (ll)S.size();
    }
    // まだ足してないやつを足す
    for(auto[x, val]: when) {
        if (val == -1) continue;
        A[x] += rui[Q]-rui[when[x]-1];
    }

    // 答え
    for(ll i=1; i<=N; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}