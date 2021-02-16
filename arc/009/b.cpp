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
    vector<ll>Bs(10);
    rep(i,10) cin >> Bs[i];
    vector<ll> table(10);  // 変換テーブル
    rep(i,10) {
        table[Bs[i]] = i;
    }

    ll N; cin >> N;
    vector<ll> As(N);
    rep(i, N) {
        ll a; cin >> a;
        As[i] = a;
    }

    auto convert = [&table](ll x) {
        // AtCoder国の数字を、通常の数字に変換する
        ll res = table[x%10];
        ll tmp = x/10;
        ll exp = 1;
        while(tmp!=0) {
            res += table[tmp%10] * pow(10, exp);
            tmp /= 10;
            exp++;
        }
        return res;
    };

    vector<pair<ll, ll>> AAs(N);
    rep(i, N) {
        AAs[i] = make_pair(As[i], convert(As[i]));
    }

    sort(AAs.begin(), AAs.end(), [](auto x, auto y) {return x.second <= y.second;});

    rep(i,N) {
        cout << AAs[i].first << endl;
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}