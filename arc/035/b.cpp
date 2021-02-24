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
    ll N; cin >> N;
    vector<ll> Ts(N);
    rep(i,N) {
        cin >> Ts[i];
    }
    // 早く解けるやつから解いたほうがいい
    sort(Ts.begin(), Ts.end());

    ll ans_time = 0;
    ll ans_num = 1;
    ll pre_t = -1;
    ll seq = 1;
    ll elapsed_time = 0;
    for(int i=0; i<Ts.size(); i++) {
        ans_time += elapsed_time + Ts[i];
        elapsed_time += Ts[i];
        if (pre_t == Ts[i]) {
            seq++;
        }
        else {
            if (seq>1) {
                for(ll j=1; j<=seq; j++) {
                    ans_num *= j;
                    ans_num %= MOD;
                }
            }
            seq = 1;
        }
        pre_t = Ts[i];
    }
    if (seq>1) {
        for(ll j=1; j<=seq; j++) {
            ans_num *= j;
            ans_num %= MOD;
        }
    }
    cout << ans_time << endl;
    cout << ans_num << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}