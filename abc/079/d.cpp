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


ll H, W;
vector<vector<ll>> Cs(10, vector<ll>(10));
vector<ll> costs(10);

void dfs(set<ll> visited, ll now, ll s, ll cost) {
    if (visited.size()==9) return;

    for(ll nx=0; nx<10; nx++) {
        if (nx==1) continue;
        if (visited.count(nx)) {continue;}
        if (costs[s] <= cost+Cs[now][nx]) {
            continue;
        }
        costs[s] = min(costs[s], cost+Cs[now][nx]+Cs[nx][1]);
        visited.insert(nx);
        dfs(visited, nx, s, cost+Cs[now][nx]);
        visited.erase(nx);
    }
}


void solve(){
    // 普通に1以外の数字を変えればいいのだが、たとえば5->1にするよりも、5->4->1のほうが魔力量が少なかったら、そうする必要がある
    cin >> H >> W;
    rep(i, 10) {
        rep (j, 10) {
            cin >> Cs[i][j];
        }
    }

    rep(i, 10) {
        costs[i] = Cs[i][1];
    }

    for (ll s=0; s<10; s++) {
        if (s==1) continue;
        set<ll> visited; visited.insert(s);
        dfs(visited, s, s, 0);
    }

    ll ans = 0;
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            ll num; cin >> num;
            if (num==1 || num==-1) continue;
            ans += costs[num];
        }
    }
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}