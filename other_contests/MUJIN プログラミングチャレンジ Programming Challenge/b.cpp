#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
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
    // OA,AB,BCの3辺について、
    // (1) 三角形の成立条件が成り立つとき、
    // 必ずCを原点に持ってこれるので、面積は OC*OC*pi
    // (2) 三角形の成立条件が成り立たないとき、
    // 半径r = (最も長い辺)-(その他の2辺の和) の面積を引く
    ll OA, AB, BC; cin >> OA >> AB >> BC;
    double ans = (double)(OA+AB+BC)*(OA+AB+BC)*M_PI;

    vector<ll> E;
    E.push_back(OA);
    E.push_back(AB);
    E.push_back(BC);
    sort(E.begin(), E.end());
    if (E[2] > E[0]+E[1]) {
        // 成り立たない
        ll r = E[2]-E[0]-E[1];
        ans -= (double)r*r*M_PI;
    }

    printf("%.8f\n",ans);
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}