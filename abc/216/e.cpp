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
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    sort(A.begin(), A.end());

    // 等差数列の和
    // aをlになるまで足す(a+(a-1)+...+(l+1))
    auto sumd = [&](ll a, ll l) -> ll {
        if (a <= l) return 0LL;
        ll n = a-l;
        return (a+l+1)*n/2;
    };

    // 二分探索用関数
    // アトラクションの楽しさがx以上のものをxになるまで乗ることができるか？
    auto bf = [&](ll x) -> pair<ll,ll> {
        ll total = 0;
        ll cnt = 0; // 操作回数
        auto it = lower_bound(A.begin(), A.end(), x);
        while(it != A.end()) {
            total += sumd((*it), x);
            cnt += (*it) - x;
            it++;
            if (cnt > K) return {-1, cnt};
        }
        return {total, cnt};
    };

    // 二分探索
    ll x;
    {
        ll l = 0;
        ll r = A[N-1];
        while(r-l != 1) {
            ll mid = (l+r)/2;
            auto[total, cnt] = bf(mid);
            if (total == -1) l = mid;
            else r = mid;
        }
        auto[total, cnt] = bf(l);
        if (total != -1) x = l;
        else x = r;
    }

    // 今、アトラクションの楽しさx以上のものは、xになるまで乗ることができることがわかった。
    // あとは残りの回数操作する
    {
        ll ans = 0;
        auto[total, cnt] = bf(x);
        ans += total;
        K -= cnt; // 残りの操作回数
        ans += x*K;
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}