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
    /*AC*/
    ll S; cin >> S;
    // (X3,Y3)=(0,0)に固定
    // 外積の面積の公式より、X1*Y2-X2*Y1 = S
    // X1=10^9, X2=1と固定すると、Y2とY1の値次第で10^19以下のすべての値を作成できる
    ll x1, x2, y1, y2;
    x1 = 1000000000;
    x2 = 1;

    for (ll y2=1LL; y2<=1000000000; y2++) {
        ll y1 = 1000000000*y2 - S;
        if (y1 >= 0 && y1 <= 1000000000) {
            cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << 0 << " " << 0 << endl;
            return;
        }
    }
}

void solve2() {
    ll S; cin >> S;
    // (X3,Y3)=(0,0)に固定
    // 外積の面積の公式より、X1*Y2-X2*Y1 = S
    // X1=10^9, X2=1と固定すると、Y2とY1の値次第で10^19以下のすべての値を作成できる
    // S=[0,100], Y=[0,10]で考えてみる。
    // 10Y2-Y1 = S
    // S=100のとき、Y2=10, Y1=0
    // S=99のとき、Y2=10,Y1=1
    // S=88のとき、Y2=9,Y1=2
    // S=1のとき、Y2=1,Y1=9
    // S=0のとき、Y2=0,Y1=0
    // このように、Y2=ceil(S/10),Y1=Y2*10-Sで求まる
    ll x1, x2, y1, y2;
    x1 = 1000000000;
    x2 = 1;
    y2 = (ll)ceil((double)S/x1);
    y1 = y2*x1-S;
    cout << x1 << " " << y1 << " " << x2 << " " << y2 << " 0 0" << endl;
}


int main(int argc, char const *argv[]){
    solve2();
    return 0;
}