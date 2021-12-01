#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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
    ll N, K, P; cin >> N >> K >> P;

    // N=40をbit全探索はむりぽ
    // 半分全列挙ならいけそう
    vector<ll> A1(N/2);
    vector<ll> A2(N-(N/2));
    for (ll i=0; i<N/2; i++) {
        cin >> A1[i];
    }
    for (ll i=0; i<(ll)A2.size(); i++) {
        cin >> A2[i];
    }

    // group1[i] := i個選んだときの値段の合計のリスト
    vector<vector<ll>> group1(A1.size()+1);
    for(ll bit=0; bit<(1<<A1.size()); bit++) {
        ll cnt = 0;
        ll total = 0;
        for(ll d=0; d<(ll)A1.size(); d++) {
            if ((bit>>d)&1) {
                cnt++;
                total += A1[d];
            }
        }

        if (total>P || cnt>K) continue;
        group1[cnt].push_back(total);
    }

    // group2[i] := 同様
    vector<vector<ll>> group2(A2.size()+1);
    for (ll bit=0; bit<(1<<A2.size()); bit++) {
        ll cnt = 0;
        ll total = 0;
        for (ll d=0; d<(ll)A2.size(); d++) {
            if ((bit>>d)&1) {
                cnt++;
                total += A2[d];
            }
        }

        if (total>P || cnt>K) continue;
        group2[cnt].push_back(total);
    }

    // ソートしておくとあとでにぶたんで高速に答えを数えられる
    for (ll i=0; i<(ll)group1.size(); i++) {
        sort(group1[i].begin(), group1[i].end());
    }
    for (ll i=0; i<(ll)group2.size(); i++) {
        sort(group2[i].begin(), group2[i].end());
    }

    // 答えを数える
    ll ans = 0;
    for(ll i=0; i<(ll)group1.size(); i++) {
        if (K-i<0 || K-i>=(ll)group2.size()) continue;
        for(auto v1: group1[i]) {
            auto itr = upper_bound(group2[K-i].begin(), group2[K-i].end(), P-v1);
            ans += (ll)(itr - group2[K-i].begin());
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}