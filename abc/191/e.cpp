#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
const ll INF = 1001001001;
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
    ll N, M; cin >> N >> M;
    // ダイクストラを各頂点についてやったら、O(VElog(V))で、ギリ間に合うんじゃないか説
    vector<ll>As(M), Bs(M), Cs(M);
    vector<vector<pair<ll, ll>>> graph(N);  // graph[i] := 頂点iから行ける頂点群
    rep(i, M) {
        cin >> As[i] >> Bs[i] >> Cs[i];
        As[i]--; Bs[i]--;
        graph[As[i]].push_back(make_pair(Bs[i], Cs[i]));
    }

    for(int s=0; s<N; s++) {
        vector<ll> dist(N, INF);  // 始点sから各頂点までの最短コストを格納する
        dist[s] = 0;
        priority_queue<pair<ll, ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> que;
        que.push(make_pair(s,0));

        ll ans = INF;
        while(!que.empty()) {
            ll u, d;
            tie(u, d) = que.top();
            que.pop();

            if (dist[u] < d) continue;

            for (int i=0; i<graph[u].size(); i++) {
                int v, cost;
                tie(v, cost) = graph[u][i];

                if (v==s) {
                    ans = min(ans, dist[u]+cost);
                    continue;
                }
                if (dist[v] > dist[u]+cost) {
                    dist[v] = dist[u]+cost;
                    que.push(make_pair(v, dist[v]));
                }
            }
        }

        if (ans==INF) {
            cout << -1 << endl;
        }
        else {
            cout << ans << endl;
        }
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}