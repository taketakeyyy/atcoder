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


void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(int i=0; i<N; i++) cin >> A[i];

    // bit全探索し、和が同じになるパターンが2つ以上あるとき、Yes
    map<ll,vector<ll>> mp;
    ll n = min(N, 8LL);  // N=200はオーバーフローする（鳩ノ巣定理より、たかだか201個の探索でOK）
    for (ll bit=1; bit<1<<n; bit++) {
        vector<ll> a;
        ll total = 0;
        for(ll d=0; d<N; d++) {
            if (bit>>d&1) {
                a.push_back(d+1);
                total += A[d]; total %= 200;
            }
        }

        if (mp[total].size() == 0) {
            mp[total] = a;
        }
        else {
            // 答えを出力
            cout << "Yes" << endl;
            vector<ll> vec = mp[total];
            cout << vec.size();
            for(auto v: vec) {
                cout << " " << v;
            }
            cout << endl;
            cout << a.size();
            for(auto v: a) {
                cout << " " << v;
            }
            cout << endl;
            return;
        }
    }

    cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}