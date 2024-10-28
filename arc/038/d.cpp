#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;



// 後退解析の練習問題
void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> X(N);
    for(ll i=0; i<N; i++) cin >> X[i];

    // 先手が頂点uにいる状態：u (0,1,...,N-1)
    // 後手が頂点uにいる状態：u+N (N,N+1,...,2N-1)
    vector<vector<ll>> revG(2*N); // revG[u] := 後退解析用グラフ。頂点uから張られている辺(行き先v)のリスト
    vector<ll> deg(2*N, 0); // deg[u] := 元のグラフの出次数。頂点uの出次数
    for(ll i=0; i<M; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        revG[b].push_back(a+N); // 先手番から後手番への遷移
        revG[b+N].push_back(a); // 後手番から先手番への遷移
        deg[a]++;
        deg[a+N]++;
    }

    // 二分探索用。先手はスコアLIMIT以上にできるか？
    auto judge = [&N, &X, &revG, &deg](ll LIMIT) -> bool {
        if (X[0] >= LIMIT) return true;

        // 後退解析をする
        vector<ll> cdeg = deg;
        queue<ll> que; // キュー
        vector<ll> memo(2*N, -1); // 1:勝ち,0:負け,-1:未確定

        // 初期条件
        for(ll u=0; u<N; u++) {
            if (X[u] >= LIMIT) {
                memo[u] = 1; // 先手勝ち
                que.push(u); // 勝敗が確定したものをキューに入れていく

                if (cdeg[u] == 0) {
                    memo[u+N] = 0; // 後手負け
                    que.push(u+N);
                }
            }
            else {
                memo[u+N] = 1; // 後手勝ち
                que.push(u+N);

                if (cdeg[u] == 0) {
                    memo[u] = 0; // 先手負け
                    que.push(u);
                }
            }
        }

        // 後退解析実行
        while(!que.empty()) {
            ll u = que.front(); que.pop();

            // 次の探索
            for(ll v: revG[u]) {
                if (memo[v] != -1) continue; // すでに勝敗が決まっているならスキップ

                cdeg[v]--; // (u,v)の辺を削除
                if (memo[u] == 0) { // （元のグラフで）遷移先にひとつでも「×」があるなら、勝ち確定なので「○」
                    memo[v] = 1;
                    que.push(v);
                }
                else if (memo[u]==1 and cdeg[v]==0) { // （元のグラフで）遷移先にひとつも「×」がないなら、負け確定なので「×」
                    memo[v] = 0;
                    que.push(v);
                }
            }
        }

        return (memo[0]==1);
    };

    // 二分探索で求める
    ll l=0, r=1e9+1;
    while(r-l > 1) {
        ll mid = (l+r)/2;
        if (judge(mid)) l = mid;
        else r = mid;
    }
    if (judge(r)) cout << r << endl;
    else cout << l << endl;
}


int main() {
    solve();
    return 0;
}