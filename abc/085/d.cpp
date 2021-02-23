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
    ll N, H; cin >> N >> H;
    vector<ll> As(N), Bs(N);
    ll mxA = 0;
    rep(i,N) {
        cin >> As[i] >> Bs[i];
        mxA = max<ll>(mxA, As[i]);
    }
    // A[i] <= B[i] なので、Bでソートして大きいものから順に投げるのが最大火力が出る
    // 方針としては、一番攻撃力の高いmax(A[i])で何回か攻撃し、最後はmax(A[i])以上のB[i]を使って殺す
    // max(A[i])未満のA[i]を使う意味はないし、max(A[i])未満のB[i]を使う意味もない
    vector<ll> newBs;  // mxA以上のBのみを格納したやつ
    for (ll b: Bs) {
        if (b >= mxA) {
            newBs.push_back(b);
        }
    }
    sort(newBs.begin(), newBs.end(), greater<ll>());

    ll ans = 0;
    for(ll b: newBs) {
        H -= b;
        ans++;
        if (H <= 0) break;
    }
    if (H > 0) {
        ans += intceil(H, mxA);
    }
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}