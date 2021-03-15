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
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

template <typename T>
map<T, T> prime_factor(T n) {
    // 因数2と5の指数部の個数を数える
    map<T, T> ans;

    while(1) {
        if(n%2!=0) {
            break;
        }
        ans[2]++;
        n /=2;
    }

    while(1) {
        if (n%5!=0) {
            break;
        }
        ans[5]++;
        n /= 5;
    }

    return ans;
}

void solve() {
    // 主客転倒では？
    // 実数だと難しいので、整数に直して考えるのが常套手段
    // Aiを10^9倍して整数に直す(Bi)
    // Ai*Ajが整数になる = Bi*Bj/10^18が整数になる
    // Biの因数2の指数部をp2[i]、Bjの因数2の指数部をp2[j]とする
    // Biの因数5の指数部をp5[i]、Bjの因数5の指数部をp5[j]とする
    // (1) p2[i]+p2[j]>=18
    // (2) p5[i]+p5[j]>=18
    // 上記2つを満たす個数を数えればよい????????????

    // p2の個数の範囲は、
    // A[i]の最小値が0より、最小個数は0
    // A[i]の最大値が10^4より、10^9倍してるから、10^13 < 2^60
    // よって、[0,60]で十分?
    // p5の個数の範囲もそれ以下なので適当に[0,60]で十分

    // cnt[p2i][p5j] := 因数2の個数がp2i個、因数5の個数がp5j個のBの個数
    // として、主客転倒で数える
    const int CNT_MAX = 60;
    ll N; cin >> N;
    vector<double> A(N);
    vector<ll> B(N);
    vector<ll> p2(N);
    vector<ll> p5(N);
    vector<vector<ll>> cnt(CNT_MAX, vector<ll>(CNT_MAX, 0));
    rep(i,N) {
        string s; cin >> s;
        ll x = 0;
        bool f = false;
        ll rest = 9;
        for (char c: s) {
            if (c!='.') {
                x = x * 10 + c - '0';
                if (f) rest--;
            }
            else {
                f = true;
            }
        }
        for(int j=0; j<rest; j++) x*=10;
        map<ll,ll> mp = prime_factor(x);
        cnt[mp[2]][mp[5]]++;
        p2[i] = mp[2];
        p5[i] = mp[5];
    }

    ll ans = 0;
    for(int i=0; i<N; i++) {
        int p2js = (ll)max(0LL, (ll)18-p2[i]);
        int p5js = (ll)max(0LL, (ll)18-p5[i]);
        for(int p2j=p2js; p2j<CNT_MAX; p2j++) {
            for(int p5j=p5js; p5j<CNT_MAX; p5j++) {
                ans += cnt[p2j][p5j];
            }
        }
        if (p2js <= p2[i] && p5js <= p5[i]) {
            // B[i]*B[i]のパターンを足してしまうので、1引く
            ans--;
        }
    }
    ans /= 2;
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}