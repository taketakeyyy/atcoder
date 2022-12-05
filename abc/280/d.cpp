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

/*
正整数nを素因数分解して、因数をkey、指数部をvalueとしたmapを返す関数
*/
template <typename T>
map<T, T> prime_factor_ver_map(T n) {
    map<T, T> ans;
    if (n <= 1) return ans;

    for (T i=2; i*i<=n; i++) {
        while (n%i == 0) {
            ans[i]++;
            n /= i;
        }
    }

    if (n != 1) ans[n]++;

    return ans;
}

// 解説AC
void solve() {
    ll K; cin >> K;

    ll p, ans = 1;
    for(p=2; (p*p)<=K; p++) {
        ll a = 0;  // p^a のaは指数部
        while(K%p == 0) {
            K /= p; a++;
        }

        ll n = 0;  // 答えの候補
        while(a > 0) {  // 指数部がまだ残っているなら続ける
            n += p;
            ll x = n;
            while(x%p == 0) {
                x /= p; a--;
            }
        }
        ans = max(ans, n);
    }
    ans = max(ans, K);
    cout << ans << endl;
}

// ルジャンドルの定理
// n!が素数pで割り切れる回数
ll f(ll n, ll p) {
    if (n == 0) return 0;
    n /= p;
    return n + f(n,p);
}

// 二分探索
void solve2() {
    ll K; cin >> K;

    // Kを素因数分解
    vector<pair<ll,ll>> ps;  // (素因数,指数部)
    ll k = K;
    for(ll p=2; p*p<=k; p++) {
        if (k%p == 1) continue;

        ll cnt = 0;  // 割り切れる回数
        while(k%p == 0) {
            k /= p; cnt++;
        }
        ps.emplace_back(p,cnt);
    }
    if (k != 1) ps.emplace_back(k,1);  // このときkは素数

    // 二分探索
    ll l = 0, r = K;
    while(r-l != 1) {
        ll mid = (l+r)/2;
        bool is_ok = true;
        for(auto[p, cnt]: ps) {
            if (f(mid,p) < cnt) is_ok = false;
        }

        if (is_ok) r = mid;
        else l = mid;
    }
    // l か r が答え
    bool is_ok = true;
    for(auto[p, cnt]: ps) {
        if (f(l,p) < cnt) is_ok = false;
    }
    if (is_ok) cout << l << endl;
    else cout << r << endl;
}


int main() {
    solve2();
    return 0;
}