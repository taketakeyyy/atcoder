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

// 移動に便利なベクトル
string vm = "ULDR";  // 上左下右
vector<ll> vy = {-1,0,1,0};
vector<ll> vx = {0,-1,0,1};
// (1) メルセンヌ・ツイスター法による疑似乱数生成器を、ハードウェア乱数をシードにして初期化
std::random_device seed_gen;
std::mt19937 engine(seed_gen());

/***
 *  UnionFindVerSize
 *
 * Descriptions:
 *  UnionFindのサイズバージョン
 *  グループの併合のとき、サイズが大きい方が、小さい方を併合する
 *  競プロでは、ノードの個数やグループの最小値とかを求めるので、こちらを使うことが多い
 *
 * Args
 *  N(T): N個のノードのUnionFindを作成する
 *
 * ならし計算量
 *  O(α(N))
 *    - α(N)はアッカーマン関数
 *    - 相当小さい（logより小さい）
 ***/
template <typename T>
struct UnionFindVerSize {
    private:
        vector<T> sizes;   // グループのサイズ
        vector<T> parents;  // 親の番号を格納する。自分が親の場合は自分の番号になり、それがそのグループの番号になる
        T group_num;  // 連結成分の個数

    public:
        UnionFindVerSize(T N=0): sizes(N,1), parents(N) {
            for (T i=0; i<N; i++) {
                parents[i] = i;
            }
            this->group_num = N;
        }

        T find_root(T x) {
            /* ノード番号xの木の根（xがどのグループか）を求める */
            if (this->parents[x] == x) return x;
            this->parents[x] = this->find_root(this->parents[x]);  // 縮約
            return this->parents[x];
        }

        void unite(T x, T y) {
            /* ノード番号xとyが属する木を併合する（グループの併合） */
            T gx = this->find_root(x); T gy = this->find_root(y);
            if (gx == gy) return;

            // 深い方が浅い方を併合する（木の偏りが減るので）
            if (this->sizes[gx] < this->sizes[gy]) {
                this->parents[gx] = gy;
                this->sizes[gy] += this->sizes[gx];
            }
            else {
                this->parents[gy] = gx;
                this->sizes[gx] += this->sizes[gy];
            }
            this->group_num--;
        }

        T get_size(T x) {
            /* ノード番号xが属するグループの深さを返す */
            return this->sizes[this->find_root(x)];
        }

        bool is_same_group(T x, T y) {
            /* ノード番号xとyが同じ集合に属するか否か */
            return this->find_root(x) == this->find_root(y);
        }

        T get_group_num() {
            /* 連結成分の個数を返す */
            return this->group_num;
        }

        void print_parents() {
            /* デバッグ用parentsの中身を出力する */
            for (T i=0; i<this->parents.size(); i++) {
                cout << this->parents[i] << endl;
            }
        }

        void print_sizes() {
            /* デバッグ用sizesの中身を出力する */
            for (T i=0; i<this->sizes.size(); i++) {
                cout << this->sizes[i] << endl;
            }
        }
};

struct Computer {
    ll id, color, y, x;
};

/**
 * @brief ソルバー
 *  grid[i][j] には、色を塗る。
 *  0: なにも置かれていない
 *  正の整数: コンピュータの色（種類色）
 *  負の整数: コンピュータの色をつなぐケーブル（1同士を繋ぐ場合は、-1になる）
 *
 * [新方針]
 * クラスタの大きさを大きくするほど得点は高くなる。
 * なるべく結合するようにする
 *
 * [新方針2]
 * 評価関数を作成。
 * 移動とクラスタ結合を交互に繰り返す。
 * 平行世界で上記を何度か試し、最も良いスコアのものを採用
 *
 */
class Solver {
    public:
        ll N, K;
        vector<vector<ll>> grid;  // 各マスには色を塗る
        vector<vector<ll>> init_grid;  // 初期化用grid
        ll MAX_ACTION_NUM;  // 最大行動回数
        map<ll,pair<ll,ll>> id2pos;  // コンピュータidの現在位置
        map<pair<ll,ll>,ll> pos2id;  // コンピュータの現在位置からidを割り出す
        set<ll> unconnected_ids;  // 接続されていないコンピュータid
        set<string> connect_list;  // 接続操作のリスト（操作の順番は関係ないように接続させるので集合にする）
        vector<string> move_list;  // 移動操作のリスト
        set<string> best_connect_list;  // 保存用
        vector<string> best_move_list;  // 保存用
        UnionFindVerSize<ll> uf;  // クラスタのグループ

        Solver(ll N_, ll K_) {
            N=N_; K=K_;
            grid.resize(N);
            init_grid.resize(N);
            for(ll i=0; i<N; i++) grid[i].resize(N);
            for(ll i=0; i<N; i++) init_grid[i].resize(N);
            MAX_ACTION_NUM = 100*K;
        }

        /**
         * @brief gridの中に収まっているか判定
         *
         * @return true
         * @return false
         */
        bool is_inside_grid(ll i, ll j) {
            return (i>=0 && i<N && j>=0 && j<N);
        }

        /**
         * @brief Set the id2pos object
         *
         * @param id
         * @param i
         * @param j
         */
        void set_id2pos(ll id, ll i, ll j) {
            id2pos[id] = {i,j};
            pos2id[{i,j}] = id;
        }

        /**
         * @brief id2pos[id]を{ni,nj}に更新する
         *
         * @param id
         * @param ni 新しい位置i
         * @param nj 新しい位置j
         */
        void update_id2pos(ll id, ll ni, ll nj) {
            auto [oi, oj] = id2pos[id];
            // id2posの更新
            id2pos[id] = {ni,nj};
            // pos2idの更新
            pos2id.erase({oi,oj});
            pos2id[{ni,nj}] = id;
        }

        /**
         * @brief 入力を受け取ってinit_gridを作成する
         *
         */
        void input_grid() {
            vector<string> tmp_grid(N);
            for(ll i=0; i<N; i++) {
                string s; cin >> s;
                tmp_grid[i] = s;
            }

            for(ll i=0; i<N; i++) {
                for(ll j=0; j<N; j++) {
                    init_grid[i][j] = ll(tmp_grid[i][j] - '0');
                }
            }
        }

        /**
         * @brief 初期化
         *
         */
        void init() {
            // リスト初期化
            move_list.clear();
            connect_list.clear();

            // 各コンピュータを識別できるようにidを付与する
            ll id = 0;
            id2pos.clear();
            pos2id.clear();
            for(ll i=0; i<N; i++) {
                for(ll j=0; j<N; j++) {
                    grid[i][j] = init_grid[i][j];
                    if (grid[i][j] > 0) {
                        set_id2pos(id, i, j);
                        id++;
                    }
                }
            }

            // UnionFind作成
            this->uf = UnionFindVerSize<ll>(id);  // 100*K個

            // 最初、すべてのコンピュータは接続されていない
            unconnected_ids.clear();
            for(ll i=0; i<id; i++) {
                unconnected_ids.insert(i);
            }
        }

        /**
         * @brief 移動行動を一回する
         * コンピュータを位置{i1,j1}から隣接する位置{i2,j2}に移動する。
         * 移動は1マス移動であること。
         *
         */
        bool move_action(ll i1, ll j1, ll i2, ll j2) {
            // gridを塗り直す
            grid[i2][j2] = grid[i1][j1];
            grid[i1][j1] = 0;

            // id2posテーブルを更新
            ll id = pos2id[{i1,j1}];
            id2pos[id] = {i2,j2};
            // pos2idテーブルを更新
            pos2id[{i2,j2}] = id;
            pos2id.erase({i1,j1});

            // 移動リストを追加
            move_list.push_back(make_operator_string(i1,j1,i2,j2));
            return true;
        }

        /**
         * @brief 接続行動を一回する
         * コンピュータ{i1, j1}, コンピュータ{i2, j2}間のマスをケーブルで繋ぐ
         *
         * @param color コンピュータの色
         */
        void connect_action(ll i1, ll j1, ll i2, ll j2, ll color) {
            if ((i1==i2)&&(j1==j2)) return;

            // 接続されてないリストから除外する
            unconnected_ids.erase(pos2id[{i1,j1}]);
            unconnected_ids.erase(pos2id[{i2,j2}]);

            // ケーブルを敷く
            if (i1 == i2) {
                ll s = min(j1, j2);
                ll t = max(j1, j2);
                for(ll j=s+1; j<t; j++) {
                    grid[i1][j] = -color;
                }
            }
            else if (j1 == j2) {
                ll s = min(i1, i2);
                ll t = max(i1, i2);
                for(ll i=s+1; i<t; i++) {
                    grid[i][j1] = -color;
                }
            }

            // 接続リストを追加
            append_connect_list(i1,j1,i2,j2);
        }

        /**
         * @brief 初期解作る
         *
         */
        void initial_solve(ll limit_num) {
            ll NIL = -99;
            // 左右に見てケーブルをつなげていく
            for(ll i=0; i<N; i++) {
                ll pre_color = NIL;
                pair<ll,ll> pre_pos = {NIL, NIL};

                for(ll j=0; j<N; j++) {
                    if (limit_num == 0) return;

                    if (grid[i][j] != 0) {
                        // マスにコンピュータが置かれているならば
                        if (pre_color == NIL) {
                            pre_color = grid[i][j];
                            pre_pos = {i,j};
                            continue;
                        }
                        else {
                            if (pre_color == grid[i][j]) {
                                if ((ll)connect_list.size()+(ll)move_list.size() > MAX_ACTION_NUM) continue;
                                // ケーブルをつなぐ
                                connect_action(pre_pos.first, pre_pos.second, i, j, grid[i][j]);
                                pre_pos = {i,j};
                                limit_num--;
                                continue;
                            }
                            else {
                                // ケーブルを繋がない
                                pre_color = grid[i][j];
                                pre_pos = {i,j};
                                continue;
                            }
                        }
                    }
                }
            }
        }

        /**
         * @brief 移動操作、接続操作の文字列を作成する
         *
         * @param si
         * @param sj
         * @param ti
         * @param tj
         * @return string
         */
        string make_operator_string(ll si, ll sj, ll ti, ll tj) {
            return to_string(si) + " " + to_string(sj) + " " + to_string(ti) + " " + to_string(tj);
        }

        /**
         * @brief 移動履歴のmove_historyを使って移動操作する
         *
         * @param si 開始地点i
         * @param sj 開始地点j
         * @param move_history
         *
         * @note ULDR
         */
        void move_action_with_move_list(ll si, ll sj, const vector<ll> &move_history) {
            ll i = si;
            ll j = sj;
            ll ni, nj;
            for(ll m: move_history) {
                if (m == 0) { // 上
                    ni = i-1; nj = j;
                }
                if (m == 1) { // 左
                    ni = i; nj = j-1;
                }
                if (m == 2) { // 下
                    ni = i+1; nj = j;
                }
                if (m == 3) { // 右
                    ni = i; nj = j+1;
                }
                bool is_ok = move_action(i, j, ni, nj);
                if (!is_ok) break;
                // move_list.push_back(make_operator_string(i,j,ni,nj));
                i=ni; j=nj;
            }
        }

        /**
         * @brief コンピュータ{si,sj}をケーブルが敷かれている場所{ti,tj}に割り込ませる
         *
         * @param i
         * @param j
         */
        void move_cable_middle(ll si, ll sj, ll ti, ll tj, const vector<ll> &move_history) {
            // 左右にケーブルが敷かれているのか、上下にケーブルが敷かれているのかを判定
            // [TODO] 今は必ず左右にしかれている
            move_action_with_move_list(si, sj, move_history);
            if (true) {
                // 左右に接続する場合
                ll target_color = grid[ti][tj];
                // 左に走査
                ll li, lj;
                for(ll j=tj-1; j>=0; j--) {
                    if (grid[ti][j] == target_color) {
                        li = ti; lj = j;
                        break;
                    }
                }
                // 右に走査
                ll ri, rj;
                for(ll j=tj+1; j<N; j++) {
                    if (grid[ti][j] == target_color) {
                        ri = ti; rj = j;
                        break;
                    }
                }
                // 接続リストから(li,lj),(ri,rj)の接続を除外する
                remove_connect_list(li, lj, ri, rj);
                // 接続リストに{(li,lj)(ti,tj)}, {(ti,tj)(ri,rj)}の接続を追加する
                connect_action(li, lj, ti, tj, target_color);
                connect_action(ti, tj, ri, rj, target_color);
            }
        }

        /**
         * @brief {si,sj}にあるコンピュータを{ti,tj}に移動させ、隣接するコンピュータ{ni,nj}と接続する
         *
         */
        void move_adjacent(ll si, ll sj, ll ti, ll tj, ll ni, ll nj, ll color, const vector<ll> &move_history) {
            if (!(si==ti && sj==tj)) {
                move_action_with_move_list(si, sj, move_history);
            }

            // 接続回数と履歴の更新
            connect_action(ti, tj, ni, nj, color);
        }

        /**
         * @brief つながっていないコンピュータの最近傍のケーブルを探し、到達可能ならば移動させる
         *
         * @param margin のちのクラスタ結合の得点の上げ幅が大きいと思われるので、ある程度行動回数を残すといいかも
         */
        void move_strategy(ll margin) {
            clock_t clock_start = clock();
            clock_t MAX_CLOCK = 0.2 * CLOCKS_PER_SEC;

            while(!unconnected_ids.empty()) {
                if (clock() - clock_start > MAX_CLOCK) break;
                if ((ll)connect_list.size()+(ll)move_list.size() > MAX_ACTION_NUM-margin) break;

                // 移動させるコンピュータを乱数で決める
                std::uniform_int_distribution<> dist(0, (int)unconnected_ids.size()-1);  // 一様分布関数（離散）[0, SIZE-1]
                ll r = dist(engine);
                auto it = unconnected_ids.begin();
                advance(it, r);
                ll id = *it;

                // BFSで移動先を探す
                auto [si, sj] = id2pos[id];
                ll target_color = grid[si][sj];
                deque<tuple<ll,ll,vector<ll>>> deq; deq.push_back({si,sj,{}});  // {i,j,移動履歴}
                set<pair<ll,ll>> visited; visited.insert({si,sj});
                bool is_success = false;  // 移動＆接続成功したか
                while(!deq.empty()) {
                    if (is_success) break;

                    auto [i, j, move_history] = deq.front(); deq.pop_front();
                    ll move_num = (ll)move_history.size();
                    if ((ll)connect_list.size()+(ll)move_list.size()+(move_num+1LL)+1LL > MAX_ACTION_NUM-margin) continue;  // 行動回数オーバーなので打ち切り

                    for(ll m=0; m<4; m++) {
                        ll ni = i + vy[m];
                        ll nj = j + vx[m];
                        if (!is_inside_grid(ni, nj)) continue;
                        if (visited.count({ni,nj})) continue;

                        if (grid[ni][nj] == -target_color) {
                            // 既存のケーブルが敷かれている場所にコンピュータを割り込ませる
                            is_success = true;
                            move_history.push_back(m);
                            move_cable_middle(si, sj, ni, nj, move_history);
                            break;
                        }
                        else if (grid[ni][nj] == target_color) {
                            // 同色のコンピュータと隣り合っているので、接続できる
                            is_success = true;
                            // move_history.push_back(m); 不要
                            move_adjacent(si, sj, i, j, ni, nj, target_color, move_history);
                            break;
                        }
                        else if (grid[ni][nj] == 0) {
                            // 空きマスなので移動可能
                            visited.insert({ni,nj});
                            move_history.push_back(m);
                            deq.push_back({ni,nj,move_history});
                            move_history.pop_back();
                        }
                    }
                }

            }
        }

        /**
         * @brief {si,sj}のコンピュータと、{ti,tj}のコンピュータを接続する操作を作成して、接続リストに追加する
         *
         * @param si
         * @param sj
         * @param ti
         * @param tj
         */
        void append_connect_list(ll si, ll sj, ll ti, ll tj) {
            string s = make_operator_string(si, sj, ti, tj);
            connect_list.insert(s);

            // クラスタ結合
            uf.unite(pos2id[{si,sj}], pos2id[{ti,tj}]);
        }

        /**
         * @brief connect_listから{si,sj}{ti,tj}の接続を削除する
         * {si,sj}{ti,tj}は、{左,右}または{上、下}の順序が保証されているものとする
         *
         * @param si
         * @param sj
         * @param ti
         * @param tj
         */
        void remove_connect_list(ll si, ll sj, ll ti, ll tj) {
            string s = make_operator_string(si, sj, ti, tj);
            connect_list.erase(s);
        }

        /**
         * @brief なるべくクラスタを大きくする
         *
         * 上下左右に走査して、クラスタを結合できるなら結合する
         *
         */
        void maximum_cluster(ll margin) {
            vector<ll> ids(100*K);
            for(ll i=0; i<100*K; i++) ids[i] = i;

            for(ll id: ids) {
                // 上下左右に走査して別クラスタを見つけたら、接続する
                auto [si, sj] = id2pos[{id}];
                ll target_color = grid[si][sj];
                // 上に走査
                if ((ll)connect_list.size() + (ll)move_list.size() + 1LL > MAX_ACTION_NUM-margin) break;
                for(ll i=si-1; i>=0; i--) {
                    if (grid[i][sj] < 0) break;
                    if (grid[i][sj] != target_color) break;
                    if (grid[i][sj] == 0) continue;
                    if (uf.is_same_group(pos2id[{si,sj}], pos2id[{i,sj}])) break;
                    connect_action(si, sj, i, sj, target_color);
                    break;
                }

                // 下に走査
                if ((ll)connect_list.size() + (ll)move_list.size() + 1LL > MAX_ACTION_NUM-margin) break;
                for(ll i=si+1; i<N; i++) {
                    if (grid[i][sj] < 0) break;
                    if (grid[i][sj] != target_color) break;
                    if (grid[i][sj] == 0) continue;
                    if (uf.is_same_group(pos2id[{si,sj}], pos2id[{i,sj}])) break;
                    connect_action(si, sj, i, sj, target_color);
                    break;
                }

                // 左に走査
                if ((ll)connect_list.size() + (ll)move_list.size() + 1LL > MAX_ACTION_NUM-margin) break;
                for(ll j=sj-1; j>=0; j--) {
                    if (grid[si][j] < 0) break;
                    if (grid[si][j] != target_color) break;
                    if (grid[si][j] == 0) continue;
                    if (uf.is_same_group(pos2id[{si,sj}], pos2id[{si,j}])) break;
                    connect_action(si, sj, si, j, target_color);
                    break;
                }

                // 右に走査
                if ((ll)connect_list.size() + (ll)move_list.size() + 1LL > MAX_ACTION_NUM-margin) break;
                for(ll j=sj+1; j<N; j++) {
                    if (grid[si][j] < 0) break;
                    if (grid[si][j] != target_color) break;
                    if (grid[si][j] == 0) continue;
                    if (uf.is_same_group(pos2id[{si,sj}], pos2id[{si,j}])) break;
                    connect_action(si, sj, si, j, target_color);
                    break;
                }
            }
        }

        /**
         * @brief 出力用のリストを保存する
         *
         */
        void save_output() {
            best_connect_list = connect_list;
            best_move_list = move_list;
        }

        /**
         * @brief 出力する
         *
         */
        void output() {
            printf("%lld\n", (ll)move_list.size());
            for(string s: move_list) {
                printf("%s\n", s.c_str());
            }
            printf("%lld\n", (ll)connect_list.size());
            for(string s: connect_list) {
                printf("%s\n", s.c_str());
            }
        }

        /**
         * @brief 素朴な実行
         *
         * @return ll
         */
        ll naive_run() {
            init();
            initial_solve(100*K);
            move_strategy(0);
            maximum_cluster(0);
            return calc_score();
        }

        /**
         * @brief ソルバー実行
         *
         */
        void run() {
            clock_t clock_start = clock();
            ll best_score = naive_run();
            save_output();

            // 制限時間いっぱいいろんな方法で繰り返す
            while(clock() - clock_start < 1.8*CLOCKS_PER_SEC) {
                init();

                // std::uniform_int_distribution<> dist1(10, (int)100*K);  // 一様分布関数（離散）[10, 100*K]
                std::uniform_int_distribution<> dist1(100, (int)100*K);  // 一様分布関数（離散）[10, 100*K]
                ll limit = dist1(engine);
                initial_solve(limit);

                ll steady_num = 0;
                ll T = 1;
                while(steady_num < 3) {
                    T *= 2;
                    ll bf_action_num = (ll)move_list.size()+(ll)connect_list.size();

                    // std::uniform_int_distribution<> dist2(10, (int)100);  // 一様分布関数（離散）[10, 100]
                    std::uniform_int_distribution<> dist2(0, (int)MAX_ACTION_NUM/T);  // 一様分布関数（離散）[10, 100]
                    ll margin = dist2(engine);
                    move_strategy(margin);
                    maximum_cluster(margin);

                    // しばらく繰り返して平衡状態が続いたらループを抜ける
                    ll af_action_num = (ll)move_list.size()+(ll)connect_list.size();
                    if (bf_action_num == af_action_num) {
                        steady_num++;
                    }
                    else {
                        steady_num = 0;
                    }
                }

                ll score = calc_score();
                if (score > best_score) {
                    best_score = score;
                    save_output();
                }
            }
            output();
        }

        /**
         * @brief 評価関数
         *
         * @return ll
         */
        ll calc_score() {
            vector<ll> ids(100*K);
            for(ll i=0; i<100*K; i++) ids[i] = i;

            ll ans = 0;
            set<ll> used;
            for(auto id: ids) {
                ll root = uf.find_root(id);
                if (used.count(root)) continue;
                ll n = uf.get_size(root);
                n--;
                ans += (n*(n+1))/2;
            }
            return ans;
        }
};

// K は [2, 5]
// 移動＋接続の操作の合計は100 * K 以下
void solve() {
    ll N, K; cin >> N >> K;

    Solver solver = Solver(N, K);
    solver.input_grid();
    solver.run();
}


int main() {
    solve();
    return 0;
}