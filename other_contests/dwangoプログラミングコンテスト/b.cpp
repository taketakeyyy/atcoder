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
    string S; cin >> S;
    // 25の取り出し方は、1通り
    // 2525の取り出し方は、長さ1が2通り、長さ1が1通り = 3通り
    // 252525の取り出し方は、長さ1が3通り、長さ2が2通り、長さ3が1通り = 6通り
    // (25)*nの取り出し方は、n+(n-1)+...+1通り
    map<ll, ll> mp;
    bool splitting = false;
    ll seq = 0;  //  25の長さ
    for (int i=0; i<S.size(); i++) {
        if (!splitting && i+1<S.size() && S[i]=='2' && S[i+1]=='5') {
            // ニコニコ文字列発見
            splitting = true;
            i++;
            seq++;
            continue;
        }
        else if (splitting && i+1<S.size() && S[i]=='2' && S[i+1]=='5') {
            // ニコニコ文字列の長さ数え中
            i++;
            seq++;
            continue;
        }
        else if ((splitting && S[i]!='2') ||
                 (splitting && i+1==S.size()) ||
                 (splitting && S[i]=='2' && i+1<S.size() && S[i+1]!='5')) {
            // ニコニコ文字列の長さ数え終了
            mp[seq]++;
            splitting = false;
            seq = 0;
            continue;
        }
    }
    if (splitting) {
        mp[seq]++;
    }

    ll ans = 0;
    for (auto [key, value]: mp) {
        ans += ((1+key)*key/2)*value;
    }
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}