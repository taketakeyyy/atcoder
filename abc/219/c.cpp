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

string X;

void solve() {
    cin >> X;
    ll N; cin >> N;
    vector<string> S(N);
    for(ll i=0; i<N; i++) cin >> S[i];

    // 文字を数字に変換
    map<char, ll> mp;
    for(ll i=0; i<X.size(); i++) {
        mp[X[i]] = i;
    }

    // 国民の名前を数字に変換
    vector<pair<vector<ll>,ll>> name(N);
    for(ll i=0; i<N; i++) {
        vector<ll> v;
        for(ll j=0; j<S[i].size(); j++) {
            v.push_back(mp[S[i][j]]);
        }
        name[i] = {v, i};
    }

    // ソート
    sort(name.begin(), name.end());

    // 出力
    for(ll i=0; i<N; i++) {
        ll id;
        tie(ignore, id) = name[i];
        cout << S[id] << endl;
    }
}


int main() {
    solve();
    return 0;
}