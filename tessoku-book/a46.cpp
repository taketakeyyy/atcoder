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
// std::random_device seed_gen;
// std::mt19937 engine(seed_gen());


ll N;  // 都市数
vector<pair<ll,ll>> city;  // city[i] := 街iの座標(x,y)

/**
 * @brief 距離の計算
 *
 */
double calc_distance(ll x1, ll y1, ll x2, ll y2) {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

/**
 * @brief スコアを計算する
 *
 * @param history
 * @return double
 */
double calc_score(vector<ll> history) {
    double total = 0;
    for(ll i=0; i<(ll)history.size()-1; i++) {
        ll u = history[i];
        ll v = history[i+1];
        auto[x1, y1] = city[u];
        auto[x2, y2] = city[v];
        total += calc_distance(x1, y1, x2, y2);
    }
    return total;
}

/**
 * @brief [a, b]の整数をランダムに返す
 *
 */
ll random_ll(ll a, ll b) {
    return a + rand() % (b-a+1);
}

/**
 * @brief 0以上1未満の乱数を返す
 *
 * @return double
 */
double random_double() {
    return 1.0 * rand() / RAND_MAX;
}

vector<ll> donyoku_solver() {
    vector<ll> ans;

    // 貪欲法（現在地から最も近い都市に移動する）
    set<ll> visited;
    visited.insert(0);
    ans.push_back(0);
    ll x, y;
    tie(x, y) = city[0];
    while(true) {
        bool is_found = false;
        double best_d = (double)INF;
        ll best_i;
        for(ll i=0; i<N; i++) {
            if (visited.count(i)) continue;
            is_found = true;
            auto[nx, ny] = city[i];
            double nd = calc_distance(x,y,nx,ny);
            if (nd < best_d) {
                best_d = nd;
                best_i = i;
            }
        }

        if (is_found) {
            ans.push_back(best_i);
            tie(x, y) = city[best_i];
            visited.insert(best_i);
            continue;
        }
        break;
    }
    ans.push_back(0);

    return ans;
}

/**
 * @brief 焼きなまし法
 * ランダムな区間[a,b]を選び、移動順序を反転させ（2-opt法）、スコアが伸びたらそれを採用する
 * スコアが伸びない場合でも、温度による確率で採用する
 *
 * @param start_clock
 * @param history
 */
void annealing_solver(clock_t const &start_clock, vector<ll> &history) {
    const double LIMIT_SEC = 0.97;  // 制限時間

    double best_score = calc_score(history);
    ll count = 0;
    // std::uniform_int_distribution<> dist_int(1, (ll)history.size()-2);  // 一様分布関数（離散）[start, end]
    // std::uniform_real_distribution<> dist_real(0.0, 1.0);  // 一様分布関数（連続）[start, end)
    double T = 30;  // 温度
    while(LIMIT_SEC > (double)(clock() - start_clock) / CLOCKS_PER_SEC) {
        // ll a = dist_int(engine);
        // ll b = dist_int(engine);
        ll a = random_ll(1, (ll)history.size()-2);
        ll b = random_ll(1, (ll)history.size()-2);

        if (a == b) continue;
        if (a > b) swap(a, b);
        count++;

        // 区間反転
        reverse(history.begin()+a, history.begin()+b+1);

        // 新しいスコア計算
        double new_score = calc_score(history);

        if (new_score < best_score) {
            best_score = new_score;
        }
        else {
            // double rp = dist_real(engine);
            double rp = random_double();
            double P = exp((best_score - new_score) / T);
            if (P >= rp) {
                // 悪くなるのを受け入れる
                best_score = new_score;
            }
            else {
                reverse(history.begin()+a, history.begin()+b+1);
            }
        }
        T = max(0.000001, T*0.99995);  // 冷やす（0除算に注意.最終的にT=1程度になるくらいに冷やしている）
    }
    // cout << "count: " << count << endl;
}

/**
 * @brief 出力する
 *
 * @param history
 */
void output(vector<ll> history) {
    for(ll i=0; i<(ll)history.size(); i++) {
        cout << history[i]+1 << endl;
    }
}

void solve() {
    // 入力
    cin >> N;
    city.resize(N);
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        city[i] = {x,y};
    }

    // クロックスタート
    clock_t start_clock = clock();

    // 貪欲法で初期解を得る
    auto ans = donyoku_solver();

    // 焼きなましする
    annealing_solver(start_clock, ans);

    // 出力
    output(ans);
}


int main() {
    solve();
    return 0;
}