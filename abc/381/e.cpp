#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// 初項a, 末項l, 項数n のときの等差数列の和
ll tousa1(const ll &a, const ll &l, const ll &n) { return ((a+l)*n)/2; }
// 初項a, 公差d, 項数n のときの等差数列の和
ll tousa2(const ll &a, const ll &d, const ll &n) { return ((2*a+(n-1)*d)*n)/2; }


// TLE
void solve() {
    ll N, Q; cin >> N >> Q;
    string S; cin >> S;
    vector<ll> R1(N+1, 0LL);
    for(ll i=1; i<=N; i++) {
        if (S[i-1]=='1') {
            R1[i] = R1[i-1] + 1;
        }
        else {
            R1[i] = R1[i-1] + 0;
        }
    }
    vector<ll> R2(N+1, 0LL);
    for(ll i=1; i<=N; i++) {
        if (S[i-1]=='2') {
            R2[i] = R2[i-1] + 1;
        }
        else {
            R2[i] = R2[i-1] + 0;
        }
    }

    vector<ll> slashPos;
    for(ll i=0; i<N; i++) {
        if (S[i] == '/') slashPos.push_back(i);
    }

    for(ll q=0; q<Q; q++) {
        ll L, R; cin >> L >> R;
        L--; R--;

        auto itr = lower_bound(slashPos.begin(), slashPos.end(), L);
        ll ans = 0;
        while(1) {
            if (itr == slashPos.end()) break;
            ll idx = *itr;
            if (R < idx) break;

            ll len1 = R1[idx-1+1] - R1[L];
            ll len2 = R2[R+1] - R2[idx];
            ll mn = min(len1, len2);
            chmax(ans, 2*mn+1);
            itr++;
        }
        cout << ans << endl;
    }
}

void solve2() {
    ll N, Q; cin >> N >> Q;
    string S; cin >> S;
    vector<ll> R1(N+1, 0LL); // 1の累積和
    for(ll i=1; i<=N; i++) {
        if (S[i-1]=='1') {
            R1[i] = R1[i-1] + 1;
        }
        else {
            R1[i] = R1[i-1] + 0;
        }
    }
    vector<ll> R2(N+1, 0LL); // 2の累積和
    for(ll i=1; i<=N; i++) {
        if (S[i-1]=='2') {
            R2[i] = R2[i-1] + 1;
        }
        else {
            R2[i] = R2[i-1] + 0;
        }
    }

    vector<ll> slashPos; // '/'のインデックスの位置
    for(ll i=0; i<N; i++) {
        if (S[i] == '/') slashPos.push_back(i);
    }

    // 部分列の長さを計算する
    auto f = [&](ll slash_idx, ll L, ll R) -> ll {
        ll pos = slashPos[slash_idx];

        ll len1 = R1[pos-1+1] - R1[L];
        ll len2 = R2[R+1] - R2[pos];
        ll mn = min(len1, len2);
        return mn*2+1;
    };

    // 左の1の個数よりも、右の2の個数のほうが多いか？
    auto judge = [&](ll slash_idx, ll L, ll R) -> bool {
        ll pos = slashPos[slash_idx];

        ll len1 = R1[pos-1+1] - R1[L];
        ll len2 = R2[R+1] - R2[pos];
        return len1 < len2;
    };

    for(ll q=0; q<Q; q++) {
        ll L, R; cin >> L >> R;
        L--; R--;

        // 二分探索
        ll l = lower_bound(slashPos.begin(), slashPos.end(), L) - slashPos.begin();
        if (l == (ll)slashPos.size()) {
            cout << 0 << endl;
            continue;
        }
        ll r = upper_bound(slashPos.begin(), slashPos.end(), R) - slashPos.begin();
        r--;
        while(r-l > 1) {
            ll mid = (l+r)/2;
            if (judge(mid, L, R)) l = mid;
            else r = mid;
        }
        ll ans = 0;
        for(ll i=l; i<=r; i++) {
            chmax(ans, f(i,L,R));
        }

        cout << ans << endl;
    }
}

int main() {
    // solve();
    solve2();
    return 0;
}