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
    map<char, ll> table;
    table['b'] = '1';
    table['c'] = '1';
    table['t'] = '3';
    table['j'] = '3';
    table['l'] = '5';
    table['v'] = '5';
    table['p'] = '7';
    table['m'] = '7';
    table['n'] = '9';
    table['g'] = '9';
    table['d'] = '2';
    table['w'] = '2';
    table['f'] = '4';
    table['q'] = '4';
    table['s'] = '6';
    table['x'] = '6';
    table['h'] = '8';
    table['k'] = '8';
    table['z'] = '0';
    table['r'] = '0';

    ll N; cin >> N;
    bool first = true;
    for (ll i=0; i<N; i++) {
        string s; cin >> s;
        transform(s.begin(), s.end(), s.begin(), ::tolower);

        string ans = "";
        for(auto c: s) {
            if (table.count(c)) {
                ans += table[c];
            }
        }
        if (!ans.empty()) {
            if (first) {
                cout << ans;
                first = false;
            }
            else {
                cout << " " << ans;
            }
        }
    }
    cout << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}