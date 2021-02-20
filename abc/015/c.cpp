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


ll N, K;
vector<vector<ll>> q;

bool dfs(ll i, ll bits) {
    if (i==N) {
        if (bits==0LL) {
            return false;
        }
        return true;
    }

    bool a = true;
    for(ll j=0; j<K; j++) {
        ll new_bits = bits ^ q[i][j];
        a = dfs(i+1, new_bits);
        if (!a) return false;
    }
    return true;
}


void solve(){
    // N,Kが小さいので全探索する
    cin >> N >> K;
    q = vector<vector<ll>>(N, vector<ll>(K));

    rep(i, N) {
        rep (j, K) {
            cin >> q[i][j];
        }
    }

    bool ans = dfs(0, 0);
    if (ans) cout << "Nothing" << endl;
    else cout << "Found" << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}