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


void solve() {
    ll N, K; cin >> N >> K;

    vector<ll> P(N);
    for(ll i=0; i<N; i++) {
        cin >> P[i];
    }

    // 重ねるカードmapのlower_boundで求めながらシミュレーションする。
    vector<ll> G(N+1, -1);  // 場に出ていて、自分の下のカードは何か
    vector<ll> ans(N+1, -1);
    map<ll,ll> mp;
    for(ll i=0; i<N; i++) {  // O(N)
        ll p = P[i];
        auto it = mp.lower_bound(p);
        if (it == mp.end()) {
            mp[p] = 1;
            G[p] = -1;

            if (mp[p] == K) {
                ans[p] = i+1;
                mp.erase(p);
            }
        }
        else {
            // 上書き
            ll oldkey = it->first;
            ll oldval = it->second;
            ll newval = oldval + 1;
            mp.erase(oldkey);
            G[p] = oldkey;
            mp[p] = newval;

            if (mp[p] == K) {
                ll now = p;
                while(now != -1) {  // ループ全体で高々N回
                    ans[now] = i+1;
                    now = G[now];
                }
                mp.erase(p);
            }
        }
    }

    // 出力
    for(ll i=1; i<=N; i++) {
        cout << ans[i] << endl;
    }
}

void test() {
    map<ll,ll> mp;
    mp[1] = 100;
    auto it = mp.lower_bound(0);
    cout << it->first << " " << it->second << endl;
    ll key = it->first;
    ll oldval = it->second;
    mp.erase(key);
    mp[0] = oldval + 1;
    for(auto [key, val]: mp) {
        cout << key << " " << val << endl;
    }
}

int main() {
    solve();
    // test();
    return 0;
}