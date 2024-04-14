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


/*
正整数xを素因数分解して、因数をkey、指数部をvalueとしたmapを返す関数
*/
map<ll,ll> prime_factor(ll x) {
    map<ll,ll> res;
    if (x <= 1) return res;

    for(ll i=2; i*i<=x; i++) {
        while (x%i == 0) {
            res[i]++;
            x /= i;
        }
    }

    if (x != 1) {
        res[x]++;
    }
    return res;
}

void solve() {
    ll N; cin >> N;
    vector<ll> A;
    ll zero_num = 0;
    for(ll i=0; i<N; i++) {
        ll a; cin >> a;
        if (a == 0) {
            zero_num++;
        }
        else {
            A.push_back(a);
        }
    }

    // 各Aを素因数分解する
    map<vector<ll>,ll> mp; // key:素因数の肩が奇数の数字, val:その個数
    for(ll i=0; i<(ll)A.size(); i++) {
        auto pf = prime_factor(A[i]);
        vector<ll> vec;
        for(auto [key, val]: pf) {
            if (val%2 != 0) vec.push_back(key);
        }
        sort(vec.begin(), vec.end());
        mp[vec]++;
    }

    // 数え上げ
    ll ans = 0;
    // ゼロは別個で数え上げる
    ans += (((N-1)+(N-zero_num))*zero_num)/2;//等差数列の和

    for(auto[key, val]: mp) {
        ll a = 1;//初項
        ll l = val-1;//末項
        ll n = val-1;//項数
        ans += ((a+l)*n)/2;//等差数列の和
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}