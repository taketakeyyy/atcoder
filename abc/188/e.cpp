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

int N, M;
vector<long long> As(N);
vector<vector<int>> paths(N);
set<int> visited;
long long ans = LONG_LONG_MIN;

void dfs(int now, long long buy) {
    for (auto nx: paths[now]) {
        if (visited.count(nx)) continue;
        ans = max(ans, As[nx]-buy);
        buy = min(buy, As[nx]);
        dfs(nx, buy);
    }
}

void solve(){
    cin >> N >> M;
    for (int i=0; i<N; i++) {
        cin >> As[i];
    }
    for (int i=0; i<M; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        paths[x].push_back(y);
    }


    for (int i=0; i<N; i++) {
        long long buy = As[i];
        visited.insert(i);
        for (auto nx: paths[i]) {
            if (visited.count(nx)) continue;
            dfs(nx, buy);
        }
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}