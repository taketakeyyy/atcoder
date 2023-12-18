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
    ll N; cin >> N;

    // 必要なポーションを調べる
    vector<ll> T(N), X(N);
    map<ll,ll> mp; // 必要なポーションの分布
    for(ll i=0; i<N; i++) {
        ll t, x; cin >> t >> x;
        x--;
        T[i] = t; X[i] = x;
        if (t == 1) {

        }
        else {
            mp[x]++;
        }
    }

    // シミュレーション
    auto sim = [&](ll Kmax) -> pair<bool, vector<ll>> {
        map<ll,ll> portion;
        map<ll,ll> mons;
        vector<ll> anss;
        ll K = 0;
        for(ll i=0; i<N; i++) {
            ll t = T[i];
            ll x = X[i];
            if (t == 1) {
                // ポーションをひろうか
                if (K < Kmax) {
                    if (portion[x] < mp[x]) {
                        portion[x]++;
                        K++;
                        anss.push_back(1);
                    }
                    else {
                        anss.push_back(0);
                    }
                }
                else {
                    anss.push_back(0);
                }
            }
            else {
                // 敵を倒す
                mons[x]++;
                K--;
                if (portion[x] < mons[x]) {
                    return {false,anss};
                }
            }
        }
        return {true, anss};
    };

    // 答え
    ll l=1, r=2e5;
    while(r-l != 1) {
        ll mid = (l+r)/2;
        auto res = sim(mid);
        if (res.first) r = mid;
        else l = mid;
    }
    ll Kmin = -1;
    vector<ll> anss;
    {
        auto res = sim(l);
        if (res.first) {
            Kmin = l; anss=res.second;
        }
        else {
            auto res = sim(r);
            if (res.first) {
                Kmin = r; anss=res.second;
            }
            else {
                cout << -1 << endl;
                return;
            }
        }
    }
    cout << Kmin << endl;
    for(ll ans: anss) {
        cout << ans << " ";
    }
    cout << endl;
}

void solve2() {
    ll N; cin >> N;

    // 必要なポーションを調べる
    vector<ll> T(N), X(N);
    map<ll,ll> mp; // 必要なポーションの分布
    for(ll i=0; i<N; i++) {
        ll t, x; cin >> t >> x;
        x--;
        T[i] = t; X[i] = x;
        if (t == 1) {

        }
        else {
            mp[x]++;
        }
    }

    // 後ろから決めていく
    ll Kmin = 0;
    auto back_sim = [&](vector<ll> &anss) {
        map<ll,ll> mons;
        map<ll,ll> portion;
        ll K = 0;
        for(ll i=N-1; i>=0; i--) {
            ll t = T[i];
            ll x = X[i];
            if (t == 1) {
                // ポーションをひろうか
                if (portion[x] < mons[x]) {
                    portion[x]++;
                    K++; Kmin = max(Kmin, K);
                    anss.push_back(1);
                }
                else {
                    anss.push_back(0);
                }
            }
            else {
                // モンスターを倒す
                mons[x]++;
                K = max(K-1,0LL);
            }
        }

        // 検証
        for(auto[key, val]: mons) {
            if (portion[key] != val) {
                return false;
            }
        }
        return true;
    };

    vector<ll> anss;
    bool res = back_sim(anss);
    if (!res) {
        cout << -1 << endl;
        return;
    }
    cout << Kmin << endl;
    reverse(anss.begin(), anss.end());
    for(ll ans: anss) {
        cout << ans << " ";
    }
    cout << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}