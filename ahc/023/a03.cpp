#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
// #include <iostream>
// #include <vector>
// #include <tuple>
// #include <utility>
// #include <algorithm>
// #include <deque>
// #include <exception>
// #include <stdexcept>
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
const string vs = "URDL";  // 上右下左
const vector<ll> vy = { -1, 0, 1, 0 };
const vector<ll> vx = { 0, 1, 0, -1 };

/**
 * @brief 高速化してビームサーチの状態数を増やす
 * * rest_crops が持つ情報をidだけにした
 */

// 区画
class Section {
private:
    ll m_id; // セクションID
    ll m_h; // h座標
    ll m_w; // w座標
    ll m_planted_crop_id; // このセクションを使用中の作物ID
    vector<ll> m_to; // 行き先のセクションID
    vector<ll> m_from; // このセクションに来れるセクションID
public:
    Section (ll id, ll h, ll w) {
        m_id = id;
        m_h = h;
        m_w = w;
        m_planted_crop_id = -1;
    }

    ll id() const { return m_id; }
    ll h() const { return m_h; }
    ll w() const { return m_w; }
    ll planted_crop_id() const { return m_planted_crop_id; }
    void planted_crop_id(ll crop_id) { m_planted_crop_id = crop_id; }
    vector<ll> to() const { return m_to; }
    vector<ll> from() const { return m_from; }

    void append_to(ll section_id) {
        m_to.push_back(section_id);
    }

    void append_from(ll section_id) {
        m_from.push_back(section_id);
    }
};

// 作物
class Crop {
private:
    ll m_id; // 作物ID
    ll m_s; // 植える時期
    ll m_d; // 収穫時期
    bool m_is_harvested; // 収穫したか？
    ll m_value; // この作物を収穫したときの価値
public:
    Crop (ll id, ll s, ll d) {
        m_id = id;
        m_s = s;
        m_d = d;
        m_is_harvested = false;
        m_value = d-s+1;
    }

    ll id() const { return m_id; }
    ll s() const { return m_s; }
    ll d() const { return m_d; }
    bool is_harvested() const { return m_is_harvested; }
    void is_harvested(bool flag) { m_is_harvested = flag; }
    ll value () const { return m_value; }
};

// 出力情報
class Output {
private:
    ll m_crop_id; // 作物id
    ll m_h; // 座標h
    ll m_w; // 座標w
    ll m_s; // 植える時期
public:
    Output (ll crop_id, ll h, ll w, ll s) {
        m_crop_id = crop_id;
        m_h = h;
        m_w = w;
        m_s = s;
    }

    // 出力する
    void output() {
        cout << m_crop_id+1 << " " << m_h << " " << m_w << " " << m_s << endl;
    }
};

struct Action {
public:
    ll upper_value;
    ll upper_use_size;
};

class State {
private:
    vector<Crop> m_crops; // m_crops[作物ID] := 作物情報
    vector<ll> m_rest_crops; // まだ植えていない作物IDのリスト
    vector<Section> m_sections; // m_sections[セクションID] := セクション情報
    ll m_available_section; // 現在使用可能な区画の数
    // vector<Output> m_history; // 答えのヒストリー
    ll m_score = 0; // この状態のスコア
public:
    State(vector<Crop> crops, vector<Section> sections) {
        m_crops = crops;
        for(Crop crop: crops) m_rest_crops.push_back(crop.id());
        m_sections = sections;
        m_available_section = 0;
    }
    Action first_action;
    void crops(vector<Crop> crops) {m_crops = crops;}
    vector<Crop> crops() const {return m_crops;}
    Crop crop(ll crop_id) const {return m_crops[crop_id];}
    vector<Crop> &get_ref_crops() {return m_crops;}
    void rest_crops(vector<ll> rest_crops) {m_rest_crops = rest_crops;}
    vector<ll> rest_crops() const {return m_rest_crops;}
    void sections(vector<Section> sections) {m_sections = sections;}
    vector<Section> sections() const {return m_sections;}
    void set_section(ll id, Section section) {m_sections[id] = section;}
    void section_append_to(ll id, ll nid) {m_sections[id].append_to(nid);}
    vector<Section> &get_ref_sections() {return m_sections;}
    void available_section(ll num) {m_available_section = num;}
    ll available_section() const {return m_available_section;}
    void increment_available_section() {m_available_section++;}
    void decrement_available_section() {m_available_section--;}
    // vector<Output> history() const {return m_history;}
    // void append_history(Output output) {m_history.push_back(output);}
    ll score() const {return m_score;}

    // もう植えられないものを除外する
    void exclude_expired_crops(ll turn) {
        vector<ll> new_rest_crops;
        for(ll cid: m_rest_crops) {
            if (m_crops[cid].s() < turn) continue;
            new_rest_crops.push_back(cid);
        }
        m_rest_crops = new_rest_crops;
    }

    // 得点を更新する
    void update_score() {
        ll ret = 0;
        for(Crop crop: m_crops) {
            if (crop.is_harvested()) ret += crop.value();
        }
        ret *= 1e6;
        ret /= (20*20*100);
        m_score = ret;
    }

    // rest_cropsを更新する
    void update_rest_crops() {
        vector<ll> new_rest_crops;
        for(Crop crop: m_crops) {
            if (crop.is_harvested()) continue;
            new_rest_crops.push_back(crop.id());
        }
        m_rest_crops = new_rest_crops;
    }

};
bool operator<(const State &s1, const State &s2) { return s1.score() < s2.score(); }
bool operator>(const State &s1, const State &s2) { return s1.score() > s2.score(); }


class Solver {
private:
    ll mH, mW, mT, m_i0;
    vector<vector<vector<bool>>> m_grid; // m_grid[h][w] := 区画(h,w)が通れる方角(上右下左)
    ll mK; // 作物の個数

    // 土地の範囲から出ていないか？
    bool is_inside(ll h, ll w) {
        return (h>=0 && h<mH && w>=0 && w<mW);
    }

    // 土地をBFSで巡って情報を得る
    void init_bfs(State &state) {
        deque<tuple<ll,ll,ll>> deq; // (h,w,コスト)
        deq.push_back({m_i0,0,0});
        vector visited(mH, vector<bool>(mW, false));
        visited[m_i0][0] = true;
        while(!deq.empty()) {
            auto[h, w, cost] = deq.front(); deq.pop_front();
            state.set_section(h*mW+w, Section{h*mW+w, h, w});
            state.increment_available_section();

            for(ll vi=0; vi<4; vi++) {
                if (!m_grid[h][w][vi]) continue;
                ll nh = h + vy[vi];
                ll nw = w + vx[vi];
                if (!is_inside(nh, nw)) continue;
                if (visited[nh][nw]) continue;
                visited[nh][nw] = true;
                deq.push_back({nh,nw,cost+1});
                state.section_append_to(h*mW+w, nh*mW+nw);
            }
        }
    }

public:
    Solver() {
        ;
    }
    vector<Output> m_ans_history; // 答えのヒストリー

    // 入力を受け取って初期状態を構築する
    State input_and_build() {
        cin >> mT >> mH >> mW >> m_i0;
        m_grid.resize(mH);
        for(ll h=0; h<mH; h++) {
            m_grid[h].resize(mW);
            for(ll w=0; w<mW; w++) m_grid[h][w].assign(4, true);
        }
        // 水路情報の構築
        for(ll h=0; h<mH-1; h++) {
            string s; std::cin >> s;
            for(ll w=0; w<mW; w++) {
                if (s[w] == '1') {
                    // 区画(h,w)の南側に水路
                    m_grid[h][w][2] = false; // 区画(h,w)は南側は通れない
                    m_grid[h+1][w][0] = false; // 区画(h+1,w)は北側は通れない
                }
            }
        }
        for(ll h=0; h<mH; h++) {
            string s; std::cin >> s;
            for(ll w=0; w<mW-1; w++) {
                if (s[w] == '1') {
                    // 区画(h,w)の東側に水路
                    m_grid[h][w][1] = false;
                    m_grid[h][w+1][3] = false;
                }
            }
        }
        // 端っこの区画の処理（画面外に出れないようにする）
        for(ll h=0; h<mH; h++) {
            for(ll w=0; w<mW; w++) {
                if (h == 0) m_grid[h][w][0] = false;
                if (h == mH-1) m_grid[h][w][2] = false;
                if (w == 0) m_grid[h][w][3] = false;
                if (w == mW-1) m_grid[h][w][1] = false;
            }
        }

        // 作物情報の構築
        cin >> mK;
        vector<Crop> crops;
        for(ll k=0; k<mK; k++) {
            ll s, d; cin >> s >> d;
            crops.push_back(Crop{k, s, d});
        }

        // m_sectionsの初期化
        vector<Section> sections;
        sections.assign(mH*mW, Section{-1,-1,-1});

        // BFSして情報を得る
        State state = State(crops, sections);
        this->init_bfs(state);

        return state;
    }

    void do_plant(vector<Crop> &proc_crops, State &state, ll use_size, ll now_turn, bool history_flag) {
        // 植える処理
        auto &ref_sections = state.get_ref_sections();
        auto &ref_crops = state.get_ref_crops();
        ll start = m_i0*mW + 0;
        auto dfs = [&](auto dfs, ll section_id, ll &crop_i) {
            // 終了条件
            if (ref_sections[section_id].planted_crop_id() != -1) return;
            if (crop_i == use_size) return;

            // 次の探索
            for(ll n_sec_id: ref_sections[section_id].to()) {
                if (ref_sections[n_sec_id].planted_crop_id() != -1) continue;
                dfs(dfs, n_sec_id, crop_i);
            }

            // crop_i植えられるかチェック [TODO] 今回のcrop_iが駄目ならfalseを返すようにしている
            auto check = [&]() -> bool {
                if (crop_i == use_size) return false;
                // 隣接するセクションより大きいdを持つ作物は植えられない
                for(ll n_sec_id: ref_sections[section_id].to()) {
                    ll n_crop_id = ref_sections[n_sec_id].planted_crop_id();
                    if (n_crop_id == -1) return false;
                    if (proc_crops[crop_i].d() > ref_crops[n_crop_id].d()) return false;
                }
                return true;
            };
            if (!check()) return;

            // 植える
            ll target_crop_id = proc_crops[crop_i].id();
            ref_sections[section_id].planted_crop_id(target_crop_id);
            state.decrement_available_section();
            ref_crops[target_crop_id].is_harvested(true);
            if (history_flag) m_ans_history.push_back(Output{target_crop_id, ref_sections[section_id].h(), ref_sections[section_id].w(), now_turn});
            crop_i++;
        };
        ll crop_i = 0;
        dfs(dfs, start, crop_i);
    }

    // 価値が大きい順に貪欲に植える
    void plan_value_greedy(ll now_turn, State &state, ll upper_value, ll upper_use_size, bool history_flag) {
        if (state.available_section() == 0) return;

        // もう植えられないものを除外する
        state.exclude_expired_crops(now_turn);

        // 価値が大きい順にソートする
        auto comp_value = [&](const Crop &a, const Crop &b) {
            return a.value() > b.value();
        };

        vector<Crop> value_order_crops;

        // 価値が上限値を超えるcropは除外する
        for(auto cid: state.rest_crops()) {
            if (state.crop(cid).value() > upper_value) continue;
            value_order_crops.push_back(state.crop(cid));
        }
        sort(value_order_crops.begin(), value_order_crops.end(), comp_value);

        // 収穫時期が遅い順にソートする
        auto comp_d = [&](const Crop &a, const Crop &b) {
            return a.d() > b.d();
        };

        // 今回植える作物の上限値を決める
        ll use_size = min(min((ll)value_order_crops.size(), state.available_section()), upper_use_size);
        sort(value_order_crops.begin(), value_order_crops.begin()+use_size, comp_d);

        // 植える処理をします
        do_plant(value_order_crops, state, use_size, now_turn, history_flag);

        // rest_cropsを更新する
        state.update_rest_crops();

        // state.scoreを更新する
        state.update_score();
    }

    // 収穫ターンにすること
    void harvest_turn(ll now_turn, State &state) {
        ll start = m_i0*mW + 0;
        auto &ref_sections = state.get_ref_sections();
        auto &ref_crops = state.get_ref_crops();

        auto dfs = [&](auto dfs, ll section_id) {
            if (ref_sections[section_id].planted_crop_id() != -1) {
                // このセクションに作物が植えられている場合
                ll cid = ref_sections[section_id].planted_crop_id();
                if (ref_crops[cid].d() == now_turn) {
                    // 収穫できるとき
                    ref_crops[cid].is_harvested(true);
                    ref_sections[section_id].planted_crop_id(-1);
                    state.increment_available_section();
                }
                else {
                    // 収穫できなかったとき
                    return;
                }
            }

            // 次の探索
            for(ll n_sec_id: ref_sections[section_id].to()) {
                dfs(dfs, n_sec_id);
            }
        };
        dfs(dfs, start);
    }

    // ビームサーチ
    State beam_search(ll now_turn, State now_state) {
        const ll BEAM_WIDTH = 3; // ビーム幅
        const ll BEAM_DEPTH = 5; // ビーム深さ
        static vector<ll> upper_values = {100, 60, 30};
        // static vector<ll> upper_values = {100, 50};
        // static vector<ll> upper_values = {100};
        // static vector<ll> upper_use_sizes = {400, 300, 200, 100};
        static vector<ll> upper_use_sizes = {400, 200, 100};
        // static vector<ll> upper_use_sizes = {400, 100};

        priority_queue<State> beam; beam.push(now_state);
        const ll TURN_LIMIT = min(now_turn+BEAM_DEPTH, 100LL);
        for(ll turn=now_turn; turn<=TURN_LIMIT; turn++) {
            priority_queue<State> nxt_beam;
            while(!beam.empty()) {
                auto state = beam.top(); beam.pop();
                for(ll upper_value: upper_values) {
                    for(ll upper_use_size: upper_use_sizes) {
                        plan_value_greedy(turn, state, upper_value, upper_use_size, false);
                        harvest_turn(turn, state);
                        if (turn == now_turn) { state.first_action = Action{upper_value, upper_use_size}; }
                        nxt_beam.push(state);
                    }
                }
            }
            // 次の深さのビームを設定する
            for(ll i=0; i<min(BEAM_WIDTH, (ll)nxt_beam.size()); i++) {
                State state = nxt_beam.top(); nxt_beam.pop();
                beam.push(state);
            }
        }

        // ベストなアクションを行う
        State best_state = beam.top();
        plan_value_greedy(now_turn, now_state, best_state.first_action.upper_value, best_state.first_action.upper_use_size, true);
        harvest_turn(now_turn, now_state);
        return now_state;
    }

    // 実行する
    State run(State state) {
        for(ll turn=1; turn<=100; turn++) {
            state = beam_search(turn, state);
        }
        return state;
    }

    // 答えを出力する
    void best_output() {
        // State state = m_beam.top();
        cout << m_ans_history.size() << endl;
        for(Output output: m_ans_history) {
            output.output();
        }
    }
};


void solve() {
    auto start = std::chrono::system_clock::now();

    Solver solver = Solver();
    State init_state = solver.input_and_build();
    State result_state = solver.run(init_state);
    solver.best_output();

    auto end = std::chrono::system_clock::now();
    auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    // [TODO]提出時はコメントアウトすること
    // 要した時間をミリ秒表示
    std::cout << msec << " milli sec \n";
    // 点数を表示
    cout << "point:" << result_state.score() << endl;
}


int main() {
    solve();
    return 0;
}