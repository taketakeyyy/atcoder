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

int N;
vector<vector<int>> es;
vector<int> A;
vector<int> B;
vector<int> depth;
vector<long long> dp;

void depth_dfs(int a, int d) {
    // depthを埋めていくDFS
    depth[a] = d;
    for (int next : es[a]) {
        if (depth[next] == -1) {
            depth_dfs(next, d+1);
        }
    }
}

void imos_dfs(int a, long now) {
    // 差分から実際の値に変換するDFS
    now += dp[a];  // nowは現在のコスト
    dp[a] = now;   // dp[a]は最終的に出力するノードの値

    for (int next : es[a]) {
        if (depth[next] > depth[a]) {
            imos_dfs(next, now);
        }
    }
}

void solve(){
    /*解説AC*/
    cin >> N;
    es.resize(N);
    A.resize(N-1); B.resize(N-1);
    dp = vector<long long>(N, 0);

    for (int i=0; i<N-1; i++) {
        cin >> A[i] >> B[i];
        A[i]--; B[i]--;
        es[A[i]].push_back(B[i]);
        es[B[i]].push_back(A[i]);
    }

    depth.resize(N, -1);
    depth_dfs(0, 0);

    int Q; cin >> Q;
    for (int i=0; i<Q; i++) {
        int t, e, x;
        cin >> t >> e >> x;
        e--;

        int va, vb;
        if (t==1) {
            va = A[e];
            vb = B[e];
        }
        else {
            va = B[e];
            vb = A[e];
        }

        if (depth[va] < depth[vb]) {
            // 通るほうが上、通るほうが下の場合
            // 根に足す
            dp[0] += x;
            // 通らない方を引く
            dp[vb] -= x;
        }
        else {
            // 通るほうが下の場合
            // 部分木に足す
            dp[va] += x;
        }
    }

    imos_dfs(0, 0);

    for (int i=0; i<N; i++) {
        cout << dp[i] << endl;
    }

}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}