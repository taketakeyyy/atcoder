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
    ll N; cin >> N;
    string S; cin >> S;

    // まず左から見ていく
    ll cnt = 0;
    bool found = false;
    for (char c: S) {
        if (c == '(') {
            found = true;
            cnt++;
        }
        else {
            if (found) {
                cnt = max(cnt-1, 0LL);
            }
        }
    }

    string R = "";
    for(ll i=0; i<cnt; i++) {
        R += ")";
    }

    // 次に右から見ていく
    cnt = 0;
    found = false;
    for (int i=S.size()-1; i>=0; i--) {
        char c = S[i];
        if (c == ')') {
            found = true;
            cnt++;
        }
        else {
            if (found) {
                cnt = max(cnt-1, 0LL);
            }
        }
    }

    string L = "";
    for(ll i=0; i<cnt; i++) {
        L += "(";
    }

    string ans = L + S + R;
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}