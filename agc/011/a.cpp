#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
const int INF = 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
struct mint {
    ll x; // typedef long long ll;
    mint(ll x=0):x((x%MOD+MOD)%MOD){}
    mint operator-() const { return mint(-x);}
    mint& operator+=(const mint a) {
        if ((x += a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += MOD-a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator*=(const mint a) { (x *= a.x) %= MOD; return *this;}
    mint operator+(const mint a) const { return mint(*this) += a;}
    mint operator-(const mint a) const { return mint(*this) -= a;}
    mint operator*(const mint a) const { return mint(*this) *= a;}
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }

    // for prime MOD
    mint inv() const { return pow(MOD-2);}
    mint& operator/=(const mint a) { return *this *= a.inv();}
    mint operator/(const mint a) const { return mint(*this) /= a;}
};
istream& operator>>(istream& is, mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}


void solve(){
    ll N, C, K; cin >> N >> C >> K;
    vector<ll> Ts(N);
    rep(i,N) cin >> Ts[i];
    // 時刻の左から順に見ていって、「怒り出す人がいる」or「バスの定員に達した」らバスを出発させる必要があるので、それを走査する
    sort(Ts.begin(), Ts.end());

    ll ans = 0;  // 求める値
    ll bus = 0;  // 現在のバスの乗員
    ll limit = -1;  // 怒り出す人がいる時刻
    for(ll i=0; i<N; i++) {
        if (limit == -1) {
            // 乗客0のとき
            bus++;
            limit = Ts[i]+K;
        }
        else if (Ts[i] > limit) {
            // 怒り出す人がいるので、バスを出発させて、iの人は新しいバスに乗せる
            ans++;
            bus = 1;
            limit = Ts[i]+K;
        }
        else {
            // 怒る人はいない
            bus++;
        }

        if (bus==C) {
            bus = 0;
            ans++;
            limit = -1;  // 乗客0なので怒る人がいない
        }
    }
    if (bus > 0) ans++;

    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}