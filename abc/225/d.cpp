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
    ll N, Q; cin >> N >> Q;
    vector<pair<ll,ll>> train(N);
    for(ll i=0; i<N; i++) {
        train[i] = {i, i};
    }

    for(ll q=0; q<Q; q++) {
        ll command, x, y;
        cin >> command >> x;
        x--;

        if (command == 1) {
            cin >> y; y--;
            train[x].second = y;
            train[y].first = x;
        }
        else if (command == 2) {
            cin >> y; y--;
            train[x].second = x;
            train[y].first = y;
        }
        else {
            // 先頭車両を見つける
            ll f = train[x].first;
            while(f != train[f].first) {
                f = train[f].first;
            }

            // 出力する
            string ans = "";
            ll n = 1;
            ans += to_string(f+1) + " ";
            ll s = train[f].second;
            while(s != train[s].second) {
                ans += to_string(s+1) + " ";
                s = train[s].second;
                n++;
            }
            if (s != f) {
                ans += to_string(s+1);
                n++;
            }
            cout << n << " " << ans << endl;
        }
    }
}


int main() {
    solve();
    return 0;
}