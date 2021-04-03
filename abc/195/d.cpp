#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

bool bag_sort(pair<ll,ll> x, pair<ll,ll> y) {
    if (x.second > y.second) {
        return true;
    }
    else if (x.second == y.second) {
        if (x.first == y.first) {
            return false;
        }
        else if (x.first > y.first) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

void solve() {
    ll N, M, Q;
    cin >> N >> M >> Q;
    vector<pair<ll,ll>> bags;
    for(int i=0; i<N; i++) {
        ll w, v;
        cin >> w >> v;
        bags.push_back(make_pair(w,v));
    }
    sort(bags.begin(), bags.end(), bag_sort);

    vector<ll>X(M);
    for(int i=0; i<M; i++) cin >> X[i];
    for(int q=0; q<Q; q++) {  // O(Q)
        ll l, r; cin >> l >> r;
        l--; r--;
        vector<ll> newX;
        for(int i=0; i<M; i++) {
            if (i>=l && i<=r) continue;
            newX.push_back(X[i]);
        }
        sort(newX.begin(), newX.end());
        vector<bool> used(newX.size(), false);
        // 価値の大きい順に入れていくが、できるだけ大きい荷物を先に入れる
        ll ans = 0;
        for(int i=0; i<N; i++) {  // O(N)
            ll w, v;
            tie(w, v) = bags[i];
            for(int j=0; j<newX.size(); j++) {  // O(M)
                if (w <= newX[j] && !used[j]) {
                    ans += v;
                    used[j] = true;
                    break;
                }
            }
        }
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}