#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
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
    ll H, W; cin >> H >> W;
    // 迷路の最も長い経路を答えれば良い
    // H,Wが小さいので、すべての頂点について始点と仮定して、BFSすればよい
    vector<string> grid(H);
    for (int i=0; i<H; i++) cin >> grid[i];

    ll ans = 0;
    for (ll h=0; h<H; h++) {
        for (ll w=0; w<W; w++) {
            if (grid[h][w]=='#') continue;
            pair<ll,ll> s = make_pair(h,w);
            set<pair<ll,ll>> visited;
            visited.insert(s);
            vector<vector<ll>> dist(H, vector<ll>(W,0));
            deque<pair<ll,ll>> que;
            que.push_back(s);
            while(que.size()!=0) {
                ll hh, ww;
                tie(hh, ww) = que.front();
                que.pop_front();

                if (hh-1>=0 && grid[hh-1][ww]=='.' && !visited.count(make_pair(hh-1, ww))) {
                    dist[hh-1][ww] = dist[hh][ww]+1;
                    ans = max(ans, dist[hh-1][ww]);
                    que.push_back(make_pair(hh-1, ww));
                    visited.insert(make_pair(hh-1, ww));
                }
                if (hh+1<H && grid[hh+1][ww]=='.' && !visited.count(make_pair(hh+1, ww))) {
                    dist[hh+1][ww] = dist[hh][ww]+1;
                    ans = max(ans, dist[hh+1][ww]);
                    que.push_back(make_pair(hh+1, ww));
                    visited.insert(make_pair(hh+1, ww));
                }
                if (ww-1>=0 && grid[hh][ww-1]=='.' && !visited.count(make_pair(hh, ww-1))) {
                    dist[hh][ww-1] = dist[hh][ww]+1;
                    ans = max(ans, dist[hh][ww-1]);
                    que.push_back(make_pair(hh, ww-1));
                    visited.insert(make_pair(hh, ww-1));
                }
                if (ww+1<W && grid[hh][ww+1]=='.' && !visited.count(make_pair(hh, ww+1))) {
                    dist[hh][ww+1] = dist[hh][ww]+1;
                    ans = max(ans, dist[hh][ww+1]);
                    que.push_back(make_pair(hh, ww+1));
                    visited.insert(make_pair(hh, ww+1));
                }
            }
        }
    }
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}