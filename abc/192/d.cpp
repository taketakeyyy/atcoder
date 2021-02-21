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

string X;
ll M;

ll f(ll n) {
    // n進数の値にして返す
    ll base = 1;
    ll num = 0;  // 生成される数字
    for(int i=X.size()-1; i>=0; i--) {  // 最大60ステップ
        if (base > M) {
            // 必ずMをオーバーする
            return M+1;
        }
        int a = X[i]-'0';
        ll abase = (ll)a*base;  // 最大で9*10^18
        if (abase > M) {
            // 必ずMをオーバーする
            return M+1;
        }
        num += abase;
        if (num < 0 || num > M) {
            // オーバーフローしちゃってる場合も、必ずMをオーバーする
            return M+1;
        }
        if (base > M/n) {
            // オーバーフロー対策
            base = M+1;
        }
        else {
            base *= n;
        }
    }
    return num;
}

ll f2(ll n) {
    ll v = 0;
    for (char c: X) {
        if (v > M/n) return M+1;  // オーバーフロー対策
        v = v*n + c-'0';
    }
    return v;
}

void solve(){
    cin >> X; cin >> M;

    if (X.size()==1) {
        ll a = X[0]-'0';
        if (a <= M) {
            cout << 1 << endl;
        }
        else {
            cout << 0 << endl;
        }
        return;
    }

    ll n = 0;
    for (auto x: X) {
        int a = x-'0';
        n = max(n, (ll)a);
    }

    // めぐる2分探索
    ll ac = n, wa = M+1;
    while (wa-ac > 1) {  // waとacが隣り合ったら終了
        ll mid = (ac+wa)/2;
        ll v = f(mid);
        if (v <= M) {
            // OKなら
            ac = mid;
        }
        else {
            wa = mid;
        }
    }
    cout << ac-n << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}