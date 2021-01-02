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


void solve(){
    long long N; cin >> N;
    vector<tuple<long long, long long, long long>> diffs(N);
    long long aoki = 0L;
    for (long long i=0; i<N; i++) {
        long long a, b;
        cin >> a >> b;
        aoki += a;
        diffs[i] = make_tuple(a+a+b, a, a+b);  // (差分, 青木派の人数, 青木+高橋)
    }

    sort(diffs.begin(), diffs.end());
    reverse(diffs.begin(), diffs.end());

    // for (long long i=0; i<N; i++) {
    //     long long diff, _aoki, _total;
    //     tie(diff, _aoki, _total) = diffs[i];
    //     cout << diff << " " << _aoki << " " << _total << endl;
    // }

    long long ans = 0;
    long long takahashi = 0L;
    for (long long i=0; i<N; i++) {
        long long diff, _aoki, _takahashi;
        tie(diff, _aoki, _takahashi) = diffs[i];
        aoki -= _aoki;
        takahashi += _takahashi;
        ans ++;
        // cout << "now: " << aoki << " / " << takahashi << endl;
        if (takahashi > aoki) break;
    }

    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}