#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


// WA解法
// まず、グラフはDAGである（閉路はない）
// 通路を塞ぐことを考えない場合、求める期待値E[i]は、
// E[i] := 現在部屋iにいる状態で、終了するまでに通る通路の数の期待値 で解ける。
// 次に、どう通路を塞げばいいのか？を考える。
// Nが600で、Mが高々180000と小さそうなので、M本の通路のうち1本を塞いでE[i]を求めるというのをMパターン全探索してもギリ行けそうだが、無理そうでもあるO(NM)
// そこで、事前に部屋1から部屋Nまでの最短経路を求めておき、その最短経路を通る部屋から分岐する通路の集合をSとする。
// 集合Sの通路を塞ぐかどうかを考えれば良いので（ここが間違い。入力例3みたいなのはそうとは限らないっぽい）、この場合の計算量はO(N|S|)
// このように、「適切な塞ぐ通路を探す」というのを自分で考えると誤っているケースが多いので、「適切なものを探す」ときは最大（最小）のものを選択するようにするとよい（solve2以降）。
void solve() {
    ll N, M; cin >> N >> M;
    vector<set<ll>> G(N+1);
    vector<set<ll>> invG(N+1); // Gの逆グラフ
    for(ll i=0; i<M; i++) {
        ll s, t; cin >> s >> t;
        G[s].insert(t);
        invG[t].insert(s);
    }

    // 部屋1から部屋Nまでの最短経路をBFSで求める
    // 最短経路が複数ある場合、複数求める必要があることに注意
    vector<ll> dist(N+1, INF); // dist[i] := 部屋1から部屋iまでに通る通路の数の最小値
    dist[1] = 0;
    {
        deque<pair<ll,ll>> deq; // (部屋番号, コスト)
        deq.push_back({1,0});
        while(!deq.empty()) {
            auto[u, cost] = deq.front(); deq.pop_front();

            for(ll v: G[u]) {
                if (dist[v] < cost+1) continue;
                dist[v] = cost+1;
                deq.push_back({v, cost+1});
            }
        }
    }

    // 最短経路で通る部屋を求める
    vector<bool> best_room(N+1, false); // 最短経路で通る部屋か？
    best_room[N] = true;
    // 部屋Nから逆順にコストが1ずつ下がるように辿っていけば最短経路の部屋が求まる
    {
        deque<pair<ll,ll>> deq; // (部屋番号, コスト)
        deq.push_back({N,dist[N]});
        while(!deq.empty()) {
            auto [u, cost] = deq.front(); deq.pop_front();

            for(ll v: invG[u]) {
                if (dist[v] != cost-1) continue;
                best_room[v] = true;
                deq.push_back({v, cost-1});
            }
        }
    }

    // 塞ぐ通路の候補を列挙する
    vector<pair<ll,ll>> unables; // 青木が塞ぐ通路(u,v)のリスト
    unables.push_back({-1,-1}); // 1個も通路を塞げないときのために便宜上ダミーを入れておく
    for(ll u=1; u<=N; u++) {
        if (!best_room[u]) continue;
        for(ll v: G[u]) {
            if (best_room[v]) continue;
            unables.push_back({u,v});
        }
    }

    // 答えを求める
    double ans = std::numeric_limits<double>::max();
    for(auto[un_u, un_v]: unables) { // 今回青木は(un_u, un_v)の通路を塞ぐ
        // dp[i] := 現在部屋iにいる状態で、終了するまでに通る通路の数の期待値
        vector<double> dp(N+1, 0.0);
        dp[N] = 0.0;
        for(ll i=N-1; i>=1; i--) {
            if (i == un_u && G[i].count(un_v)) {
                // 塞がれた通路が存在する場合
                ll room_num = (ll)G[i].size() - 1; // 遷移できる部屋の数

                // dpの更新
                double p = (double)1.0/room_num; // 遷移確率
                dp[i] = 1.0;
                for(ll j: G[i]) {
                    if (j == un_v) continue;
                    dp[i] += p*dp[j];
                }
            }
            else {
                // 塞がれた通路が存在しない場合
                ll room_num = G[i].size(); // 遷移できる部屋の数

                // dpの更新
                double p = (double)1.0/room_num; // 遷移確率
                dp[i] = 1.0;
                for(ll j: G[i]) {
                    dp[i] += p*dp[j];
                }
            }
        }
        ans = min(ans, dp[1]);
    }
    printf("%.10f\n", ans);
}


// シンプル実装AC
// setのforループは遅くてTLEするので注意。
void solve2() {
    ll N, M; cin >> N >> M;
    // vector<set<ll>> G(N+1); // forループが遅い！
    vector<vector<ll>> G(N+1);
    for(ll i=0; i<M; i++) {
        ll s, t; cin >> s >> t;
        // G[s].insert(t);
        G[s].push_back(t);
    }

    // 青木は通路を一切塞がない場合を考える。
    // dp[i] := 現在部屋iにいる状態で、終了するまでに通る通路の数の期待値
    vector<double> dp(N+1, 0.0);
    dp[N] = 0.0;
    for(ll i=N-1; i>=1; i--) { // O(N)
        // dp更新
        double p = (double)1/G[i].size(); // 遷移確率
        dp[i] = 1;
        for(ll j: G[i]) { // 合計で高々M回
            dp[i] += p*dp[j];
        }
    }

    // 青木は通路を1つ塞ぐことを考える。青木はどの通路を塞ぐのが適切か？
    // 部屋uから出ている通路のどれかを塞ぐことを考える。uから遷移できる部屋のうち、最も「通る通路の数の期待値」が大きい部屋vへの通路を塞ぐのが適切。
    // なので、各頂点uについて塞ぐ通路を探して、その通路を塞いだ場合のDP計算をすればいいので、O(N(N+M))
    double ans = dp[1];
    for(ll u=N-1; u>=1; u--) { // O(N)
        if (G[u].size() == 1) continue; // 1つしかない通路は塞いだら部屋Nに到達できなくなるので駄目

        // 青木が塞ぐ通路(u, target_v)を求める
        ll target_v = -1;
        double max_expect = -1.0;
        for(ll v: G[u]) {
            if (max_expect >= dp[v]) continue;
            max_expect = dp[v];
            target_v = v;
        }

        // (u, target_v)の通路を塞いだときの期待値dp2を求める
        vector<double> dp2(N+1, 0.0);
        dp2[N] = 0.0;
        for(ll i=N-1; i>=1; i--) { // O(N+M)
            if (i == u) {
                double p = (double)1.0/(G[i].size()-1); // 遷移確率
                dp2[i] = 1;
                for(ll j: G[i]) {
                    if (j == target_v) continue;
                    dp2[i] += p*dp2[j];
                }
            }
            else {
                double p = (double)1.0/(G[i].size()); // 遷移確率
                dp2[i] = 1;
                for(ll j: G[i]) {
                    dp2[i] += p*dp2[j];
                }
            }
        }

        // 答え更新
        ans = min(ans, dp2[1]);
    }
    printf("%.10f\n", ans);
}


// インラインDPを使って高速化
void solve3() {
    ll N, M; cin >> N >> M;
    // vector<set<ll>> G(N+1); // forループが遅い！
    vector<vector<ll>> G(N+1);
    for(ll i=0; i<M; i++) {
        ll s, t; cin >> s >> t;
        // G[s].insert(t);
        G[s].push_back(t);
    }

    // 青木は通路を一切塞がない場合を考える。
    // dp[i] := 現在部屋iにいる状態で、終了するまでに通る通路の数の期待値
    vector<double> dp(N+1, 0.0);
    dp[N] = 0.0;
    for(ll i=N-1; i>=1; i--) { // O(N)
        // dp更新
        double p = (double)1/G[i].size(); // 遷移確率
        dp[i] = 1;
        for(ll j: G[i]) { // 合計で高々M回
            dp[i] += p*dp[j];
        }
    }

    // 青木は通路を1つ塞ぐことを考える。青木はどの通路を塞ぐのが適切か？
    // 部屋uから出ている通路のどれかを塞ぐことを考える。uから遷移できる部屋のうち、最も「通る通路の数の期待値」が大きい部屋vへの通路を塞ぐのが適切。
    // なので、各頂点uについて塞ぐ通路を探して、その通路を塞いだ場合のDP計算をすればいいので、O(N(N+M))
    vector<double> dp2 = dp; // dp2 := 適切な通路を一つ塞いだときのdp
    double ans = dp[1];
    for(ll u=N-1; u>=1; u--) {
        if (G[u].size() == 1) continue; // 1つしかない通路は塞いだら部屋Nに到達できなくなるので駄目

        // 青木が塞ぐ通路(u, target_v)を求める
        ll target_v = -1;
        double max_expect = -1.0;
        for(ll v: G[u]) {
            if (max_expect >= dp[v]) continue;
            max_expect = dp[v];
            target_v = v;
        }

        // (u, target_v)の通路を塞いだときの期待値を求める
        // 部屋uより数字が大きい期待値は影響しないので、部屋u以下だけdp2を更新すればいい（インラインDPができる）
        { // 部屋uのdp2更新
            double p = (double)1.0/((ll)G[u].size()-1); // 遷移確率
            dp2[u] = 1;
            for(ll j: G[u]) {
                if (j == target_v) continue;
                dp2[u] += p*dp[j];
            }
        }
        // 部屋u-1以下のdp2更新
        for(ll i=u-1; i>=1; i--) {
            double p = (double)1.0/(G[i].size()); // 遷移確率
            dp2[i] = 1;
            for(ll j: G[i]) {
                if (j > u) dp2[i] += p*dp[j];
                else dp2[i] += p*dp2[j];
            }
        }

        // 答え更新
        ans = min(ans, dp2[1]);

        // dp2[u]の期待値を戻しておく
        dp2[u] = dp[u];
    }
    printf("%.10f\n", ans);
}


int main() {
    // solve();
    // solve2();
    solve3();
    return 0;
}