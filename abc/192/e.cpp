#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
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
    ll N, M, X, Y; cin >> N >> M >> X >> Y;
    X--; Y--;
    vector<vector<tuple<ll, ll, ll>>> graph(N);  //graph[i] := 頂点iから行ける頂点群(頂点番号, コスト, 発車時刻の倍数K)

    for (int i=0; i<M; i++) {
        ll A, B, T, K;
        cin >> A >> B >> T >> K;
        A--; B--;
        graph[A].emplace_back(make_tuple(B, T, K));
        graph[B].emplace_back(make_tuple(A, T, K));
    }

    vector<ll> dist(N, INF);
    dist[X] = 0;
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> que;
    que.push(make_pair(X,0));

    while(!que.empty()) {
        ll u, d;
        tie(u, d) = que.top();
        que.pop();

        // スキップ処理
        if (dist[u] < d) continue;

        // 更新処理
        for (ll i=0; i<graph[u].size(); i++) {
            ll v, cost, k;
            tie(v, cost, k) = graph[u][i];

            ll now = dist[u];
            if (now%k != 0) {
                now += k-(now%k);
            }
            if (dist[v] > now+cost) {
                dist[v] = now+cost;
                que.push(make_pair(v, dist[v]));
            }
        }
    }

    if (dist[Y]==INF) {
        cout << -1 << endl;
    }
    else {
        cout << dist[Y] << endl;
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}