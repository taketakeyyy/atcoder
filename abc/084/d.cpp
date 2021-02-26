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


vector<bool> is_prime(100001, true);  // is_prime[i] := iは素数かどうか
vector<ll> sum_near_2017(100001, 0);  // 2017に近た数の累積和
void make_prime() {
    // エラトステネスの篩
    is_prime[0] = false; is_prime[1] = false;
    for(int i=2; i<100001; i++) {
        if (is_prime[i]) {
            for (int j=i*2; j<100001; j+=i) {
                is_prime[j] = false;
            }

            // 2017に似た数の処理
            if (i&1) {
                if (is_prime[(i+1)/2]) {
                    sum_near_2017[i] = sum_near_2017[i-1] + 1;
                }
                else {
                    sum_near_2017[i] = sum_near_2017[i-1];
                }
            }
        }
        else {
            sum_near_2017[i] = sum_near_2017[i-1];
        }
    }
}


void solve(){
    make_prime();
    ll Q; cin >> Q;
    for (ll i=0; i<Q; i++) {
        ll l, r; cin >> l >> r;
        cout << (sum_near_2017[r]-sum_near_2017[l-1]) << endl;
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}