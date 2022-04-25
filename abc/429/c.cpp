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

string alpha = "abcdefghijklmnopqrstuvwxyz";

void solve() {
    ll N, K; cin >> N >> K;
    vector<set<char>> Ss(N);
    for(ll i=0; i<N; i++) {
        string s; cin >> s;
        for(char c: s) {
            Ss[i].insert(c);
        }
    }

    // bit全探索
    ll ans = 0;
    for(ll bits=0; bits<(1<<N); bits++) {
        ll cnt = 0;
        map<char, ll> mp;

        for(ll d=0; d<N; d++) {
            if ((bits>>d)&1) {
                for(char c: Ss[d]) {
                    mp[c]++;
                }
            }
        }

        for(auto [key, val]: mp) {
            if (val == K) {
                cnt++;
            }
        }

        ans = max(ans, cnt);
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}