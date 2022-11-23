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

// (1) メルセンヌ・ツイスター法による疑似乱数生成器を、ハードウェア乱数をシードにして初期化
std::random_device seed_gen;
std::mt19937 engine(seed_gen());

// (2) 分布関数を決める
std::uniform_real_distribution<double> dist_eps(0.0, 1.0);  // 一様分布関数[a, b)

// // (3) 出力
// int r = dist(engine);  // 乱数生成
// std::cout << r << std::endl;

ll M;  // グラフ数
double eps;  // エラー率

void init_solver() {
    // ll N = 100;
    ll N;
    for(N=4; N<=100; N++) {
        // if (N*(N-1) >= 2*M-eps*100) break;
        ll NN = N+(eps*100);
        if (NN*(NN-1) >= 2*M) {
            N = min(NN, 100LL);
            break;
        }
    }
    printf("%lld\n", N);
    fflush(stdout);

    // グラフ作成
    ll E = N*(N-1)/2;  // 最大の辺数
    ll e_d = E/(M-1);  // 辺の等差

    vector<ll> e_nums(M);  // グラフG[m] の辺数
    for(ll m=0; m<M; m++) {
        e_nums[m] = m*e_d;
    }

    // 辺情報出力処理
    for (ll m=0; m<M; m++) {
        vector<ll> edges(E);
        for(ll i=0; i<e_d*m; i++) {
            edges[i] = 1;
        }

        for(ll i=e_d*m; i<E; i++) {
            edges[i] = 0;
        }

        // 辺情報出力
        for(ll i=0; i<E; i++) {
            printf("%lld", edges[i]);
            fflush(stdout);
        }
        printf("\n");
        fflush(stdout);
    }

    // クエリ処理
    for(ll q=0; q<100; q++) {
        // グラフH
        string H; cin >> H;
        ll one = 0;
        if ((ll)H.size() != E) {
            // ローカルテスタ
            ll sk = atoi(H.c_str());
            ll query_e_num = e_nums[sk];
            // エラー率eps で 1 と 0 が反転する
            // query_e_num = e_nums[sk]*eps + (E-e_nums[sk])*(1-eps); // は？
            one = query_e_num;
        }
        else {
            // 本番環境
            for(ll i=0; i<(ll)H.size(); i++) {
                if (H[i] == '1') one++;
            }
        }

        // 推測する
        ll idx = lower_bound(e_nums.begin(), e_nums.end(), one) - e_nums.begin();
        ll t;
        if (idx == 0) {
            t = idx;
        }
        else {
            if (e_nums[idx]-one >= one-e_nums[idx-1]) {
                t = idx-1;
            }
            else {
                t = idx;
            }
        }
        t = min(t, M-1);

        printf("%lld\n", t);
        fflush(stdout);
    }
}

/**
 * グラフ数M (10 ≤ M ≤ 100)
 * エラー率eps 0.00 ≤ eps ≤ 0.4
 *
 * (1) 自分でグラフGを作る（頂点数N 4 ≤ N ≤ 100 も自分で決める）
 *   - Nは小さい方がいい！
 * (2) クエリ処理で、Gから作られたグラフHが与えられる。
 * (3) HはどのGから作られたか予測し、予測値を出力せよ
 *
 *
 */
void solve() {
    cin >> M >> eps;

    init_solver();

}


int main() {
    solve();
    return 0;
}