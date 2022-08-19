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
 */
class Solver {
    public:
        ll N, K;
        vector<vector<ll>> grid;  // 各マスには色を塗る
        ll MAX_ACTION_NUM;  // 最大行動回数
        map<ll,pair<ll,ll>> id2pos;  // コンピュータidの現在位置
        map<pair<ll,ll>,ll> pos2id;  // コンピュータの現在位置からidを割り出す
        set<ll> unconnected_ids;  // 接続されていないコンピュータid
        set<string> connect_list;  // 接続操作のリスト（操作の順番は関係ないように接続させるので集合にする）
        vector<string> move_list;  // 移動操作のリスト

        Solver(ll N_, ll K_) {
            N=N_; K=K_;
            grid.resize(N);
            for(ll i=0; i<N; i++) grid[i].resize(N);
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
         * @brief 入力を受け取ってgridを作成する
         *
         */
        void input_grid() {
            vector<string> tmp_grid(N);
            for(ll i=0; i<N; i++) {
                string s; cin >> s;
                tmp_grid[i] = s;
            }

            ll id = 0;  // 各コンピュータを識別できるようにidを付与する
            for(ll i=0; i<N; i++) {
                for(ll j=0; j<N; j++) {
                    grid[i][j] = ll(tmp_grid[i][j] - '0');
                    if (grid[i][j] > 0) {
                        set_id2pos(id, i, j);
                        id++;
                    }
                }
            }

            // 最初、すべてのコンピュータは接続されていない
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
            // [TODO] バグっている。本来はこれは不要なはず。
            // if (grid[i2][j2] > 0) {
            //     return false;
            // }

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
        void initial_solve() {
            ll NIL = -99;
            // 左右に見てケーブルをつなげていく
            for(ll i=0; i<N; i++) {
                ll pre_color = NIL;
                pair<ll,ll> pre_pos = {NIL, NIL};

                for(ll j=0; j<N; j++) {
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

            // [TODO]バグっている。苦肉の策
            // if (grid[ti][tj]==0) return;

            // 接続回数と履歴の更新
            connect_action(ti, tj, ni, nj, color);
        }

        /**
         * @brief つながっていないコンピュータの最近傍のケーブルを探し、到達可能ならば移動させる
         *
         */
        void move_strategy() {
            ll failed_num = 0;  // 連続移動失敗回数
            ll MAX_FAILED = 10;  // 失敗の限界

            while(!unconnected_ids.empty()) {
                if (failed_num >= MAX_FAILED) { break; }
                if ((ll)connect_list.size()+(ll)move_list.size() > MAX_ACTION_NUM) break;

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
                    if ((ll)connect_list.size()+(ll)move_list.size()+(move_num+1LL)+1LL > MAX_ACTION_NUM) continue;  // 行動回数オーバーなので打ち切り

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

                if (is_success) {
                    failed_num = 0;
                }
                else {
                    failed_num++;
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
         * @brief 左右に走査して、接続リストを作成する
         *
         */
        void make_connect_list_LR() {
            ll NIL = -99;
            for(ll i=0; i<N; i++) {
                ll pre_color = NIL;
                pair<ll,ll> pre_pos = {NIL, NIL};

                for(ll j=0; j<N; j++) {
                    if (grid[i][j] > 0) {
                        // コンピュータが置かれているならば
                        if (pre_color == NIL) {
                            // 接続されていない
                            pre_color = grid[i][j];
                            pre_pos = {i,j};
                            continue;
                        }
                        else {
                            if (pre_color == grid[i][j]) {
                                // 接続されている
                                append_connect_list(pre_pos.first, pre_pos.second, i, j);  // ここでバグっている重複してappendしてしまっている。
                                pre_pos = {i,j};
                                continue;
                            }
                            else {
                                // 接続されていない
                                pre_color = grid[i][j];
                                pre_pos = {i,j};
                                continue;
                            }
                        }
                    }
                    if (grid[i][j] < 0) {
                        // ケーブルが敷かれているならば
                        if (pre_color == NIL) {
                            continue;
                        }
                        else {
                            if (grid[i][j] == -pre_color) {
                                continue;
                            }
                            else {
                                pre_color = NIL;
                                continue;
                            }
                        }
                    }
                    if (grid[i][j] == 0) {
                        continue;
                    }
                }
            }
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
         * @brief ソルバー実行
         *
         */
        void run() {
            input_grid();
            initial_solve();
            move_strategy();
            // make_connect_list_LR();
            output();
        }

};

// K は [2, 5]
// 移動＋接続の操作の合計は100 * K 以下
void solve() {
    ll N, K; cin >> N >> K;

    Solver solver = Solver(N, K);
    solver.run();

}


int main() {
    // test_aoba();
    solve();
    return 0;
}