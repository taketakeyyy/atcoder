#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/b)
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


ll f(ll i, ll j, ll k, ll l) {
    return (i-k)*(i-k) + (j-l)*(j-l);
}

bool is_inside(ll i, ll j, ll N) {
    return (i>=0 && i<N && j>=0 && j<N);
}

// 前処理で移動方向を調べる解放
void solve1() {
    ll N, M; cin >> N >> M;

    // どういう移動をするのか調べる
    set<pair<ll,ll>> vmove;
    for(ll k=0; k<N; k++) {
        for(ll l=0; l<N; l++) {
            if (f(0,0,k,l) != M) continue;
            vmove.insert({k,l});
            vmove.insert({-k,l});
            vmove.insert({k,-l});
            vmove.insert({-k,-l});
            vmove.insert({l,k});
            vmove.insert({-l,k});
            vmove.insert({l,-k});
            vmove.insert({-l,-k});
        }
    }

    // BFS探索
    vector<vector<ll>> dist(N, vector<ll>(N, -1));
    deque<tuple<ll,ll,ll>> deq;
    deq.push_back({0,0,0});
    dist[0][0] = 0;
    while(!deq.empty()) {
        auto[i, j, cnt] = deq.front(); deq.pop_front();

        for(auto [vi, vj]: vmove) {
            ll k = i + vi;
            ll l = j + vj;
            if (!is_inside(k,l,N)) continue;
            if (dist[k][l] != -1) continue;
            dist[k][l] = cnt + 1;
            deq.push_back({k,l,cnt+1});
        }
    }

    // 出力
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            if (j < N-1) cout << dist[i][j] << " ";
            else cout << dist[i][j];
        }
        cout << endl;
    }
}

// 平方数だった場合、平方根した値を返す(0も含む)。そうでないなら-1を返す
vector<ll> square_memo(1000001, -1);  // メモ化
void make_square_memo() {
    for(ll i=0; i*i<=1000000; i++) {
        square_memo[i*i] = i;
    }
}
ll square(ll i, ll j, ll k, ll M) {
    ll D = M - (i-k)*(i-k);  // 解の公式のルートの中身部分。整理済み
    // D は平方数か？
    if (D < 0) return -1;
    return square_memo[D];
}


// 解の公式を使ってlをO(1)で求めるために、平方数の前処理をする解放
void solve2() {
    ll N, M; cin >> N >> M;

    // 平方数となるものを前処理で作成
    make_square_memo();

    // BFS探索
    vector<vector<ll>> dist(N, vector<ll>(N, -1));
    deque<tuple<ll,ll,ll>> deq;
    deq.push_back({0,0,0});
    dist[0][0] = 0;
    while(!deq.empty()) {
        auto[i, j, cnt] = deq.front(); deq.pop_front();

        for(ll k=0; k<N; k++) {
            // 解の公式より、kを決めたらlが求まる。
            // まず解の公式のルートの中身が平方数か判定する
            ll s = square(i,j,k,M);
            if (s == -1) continue;
            if (j+s>=0 && j+s<N) {
                ll l = j+s;
                if (dist[k][l] == -1) {
                    dist[k][l] = cnt + 1;
                    deq.push_back({k,l,cnt+1});
                }
            }
            if (j-s>=0 && j-s<N) {
                ll l = j-s;
                if (dist[k][l] == -1) {
                    dist[k][l] = cnt + 1;
                    deq.push_back({k,l,cnt+1});
                }
            }
        }
    }

    // 出力
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            if (j < N-1) cout << dist[i][j] << " ";
            else cout << dist[i][j];
        }
        cout << endl;
    }
}

int main() {
    // solve1();
    solve2();
    return 0;
}