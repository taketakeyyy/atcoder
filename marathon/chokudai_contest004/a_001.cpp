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
// (1) メルセンヌ・ツイスター法による疑似乱数生成器を、ハードウェア乱数をシードにして初期化
std::random_device seed_gen;
std::mt19937 engine(seed_gen());



class Mountain {
    private:
        std::uniform_int_distribution<> dist_ij;  // 一様分布関数（離散）
        std::uniform_int_distribution<> dist_01;

    public:
        vector<vector<ll>> grid;
        vector<vector<ll>> L;
        vector<vector<ll>> R;
        ll N;
        ll move;
        Mountain(ll N, vector<vector<ll>> L, vector<vector<ll>> R) {
            grid.resize(N);
            for(ll i=0; i<N; i++) grid.resize(N);
            this->N = N;
            this->L = L;
            this->R = R;
            this->dist_ij = std::uniform_int_distribution<>(0, N);  // i,j用の一様分布関数（離散）
            this->dist_01 = std::uniform_int_distribution<>(0, 1);  // 0 or 1用の一様分布関数（離散）
            this->move = 1;
        }

        // 状態の初期化
        void init_state() {
            // 適当にLとRの中央値で初期化
            for(ll i=0; i<N; i++) {
                for(ll j=0; j<N; j++) {
                    grid[i][j] = (L[i][j]+R[i][j])/2;
                }
            }
        }

        // 状態遷移
        void change_state() {
            ll i = dist_ij(engine);
            ll j = dist_ij(engine);
            ll r = dist_01(engine);
            ll v;
            if (r == 0) {
                // L側に移動
                v = max(L[i][j], grid[i][j]-move);
            }
            else {
                // R側に移動
                v = min(R[i][j], grid[i][j]-move);
            }
            grid[i][j] = v;
        }

        // 評価関数
        ll calc_score() {
            for(ll i=0; i<N; i++) {
                for(ll j=0; j<N; j++) {
                    ;
                }
            }
        }
};

void solve() {
    ll N;
    vector<ll> B(3);
    for(ll i=0; i<3; i++) cin >> B[i];
    vector<vector<ll>> L(N, vector<ll>(N));
    vector<vector<ll>> R(N, vector<ll>(N));
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            cin >> L[i][j];
        }
    }
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            cin >> R[i][j];
        }
    }

    Mountain m = Mountain(N, L, R);

}


int main() {
    solve();
    return 0;
}