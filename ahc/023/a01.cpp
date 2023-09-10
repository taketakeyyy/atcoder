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

class Solver {
private:
    ll mH, mW, mT, m_i0;
    vector<vector<vector<bool>>> m_grid; // m_grid[h][w] := 区画(h,w)が通れる方角(上右下左)
    ll mK; // 作物の個数
    vector<Crop> m_crops; // m_crops[作物ID] := 作物情報
    vector<Crop> m_rest_crops; // まだ植えていない作物のリスト
    ll m_available_section; // 現在使用可能な区画の数
    vector<Section> m_sections; // m_sections[セクションID] := セクション情報
    vector<Output> m_history; // 答えのヒストリー

    // 土地の範囲から出ていないか？
    bool is_inside(ll h, ll w) {
        return (h>=0 && h<mH && w>=0 && w<mW);
    }

    // 土地をBFSで巡って情報を得る
    void bfs() {
        deque<tuple<ll,ll,ll>> deq; // (h,w,コスト)
        deq.push_back({m_i0,0,0});
        vector visited(mH, vector<bool>(mW, false));
        visited[m_i0][0] = true;
        while(!deq.empty()) {
            auto[h, w, cost] = deq.front(); deq.pop_front();
            m_sections[h*mW+w] = Section{h*mW+w, h, w};
            m_available_section++;

            for(ll vi=0; vi<4; vi++) {
                if (!m_grid[h][w][vi]) continue;
                ll nh = h + vy[vi];
                ll nw = w + vx[vi];
                if (!is_inside(nh, nw)) continue;
                if (visited[nh][nw]) continue;
                visited[nh][nw] = true;
                deq.push_back({nh,nw,cost+1});
                m_sections[h*mW+w].append_to(nh*mW+nw);
            }
        }
    }

public:
    Solver() {
        ;
    }

    // 入力を受け取って初期状態を構築する
    void input_and_build() {
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
        for(ll k=0; k<mK; k++) {
            ll s, d; cin >> s >> d;
            m_crops.push_back(Crop{k, s, d});
        }
        m_rest_crops = m_crops;

        // m_sectionsの初期化
        m_sections.assign(mH*mW, Section{-1,-1,-1});
        m_available_section = 0;

        // BFSして情報を得る
        this->bfs();
    }

    // 得点を返す
    ll calc_eval() {
        ll ret = 0;
        for(ll k=0; k<mK; k++) {
            Crop crop = m_crops[k];
            if (crop.is_harvested()) ret += crop.value();
        }
        ret *= 1e6;
        ret /= (mH*mW*mT);
        return ret;
    }

    // 価値が大きい順に貪欲に植える
    void plan_greedy(ll now_turn) {
        // もう植えられないものを除外する
        {
            vector<Crop> new_rest_crops;
            for(Crop crop: m_rest_crops) {
                if (crop.s() < now_turn) continue;
                new_rest_crops.push_back(crop);
            }
            m_rest_crops = new_rest_crops;
        }

        // 価値が大きい順にソートする
        auto comp_value = [&](const Crop &a, const Crop &b) {
            return a.value() > b.value();
        };
        auto value_order_crops = m_rest_crops;
        sort(value_order_crops.begin(), value_order_crops.end(), comp_value);

        // 収穫時期が遅い順にソートする
        auto comp_d = [&](const Crop &a, const Crop &b) {
            return a.d() > b.d();
        };
        ll use_size = min((ll)value_order_crops.size(), m_available_section);
        sort(value_order_crops.begin(), value_order_crops.begin()+use_size, comp_d);

        // 残りのm_rest_cropsを更新する
        {
            vector<Crop> new_rest_crops(value_order_crops.size()-use_size, Crop{-1,-1,-1});
            for(ll i=0; i<(ll)new_rest_crops.size(); i++) {
                new_rest_crops[i] = value_order_crops[use_size+i];
            }
            m_rest_crops = new_rest_crops;
        }

        // 植える処理
        ll start = m_i0*mW + 0;
        auto dfs = [&](auto dfs, ll section_id, ll &crop_i) {
            // 終了条件
            if (m_sections[section_id].planted_crop_id() != -1) return;
            if (crop_i == use_size) return;

            // 次の探索
            for(ll n_sec_id: m_sections[section_id].to()) {
                if (m_sections[n_sec_id].planted_crop_id() != -1) continue;
                dfs(dfs, n_sec_id, crop_i);
            }

            // crop_i植えられるかチェック [TODO] 今回のcrop_iが駄目ならfalseを返すようにしている
            auto check = [&]() -> bool {
                if (crop_i == use_size) return false;
                // 隣接するセクションより大きいdを持つ作物は植えられない
                for(ll n_sec_id: m_sections[section_id].to()) {
                    ll n_crop_id = m_sections[n_sec_id].planted_crop_id();
                    if (n_crop_id == -1) return false;
                    if (value_order_crops[crop_i].d() > m_crops[n_crop_id].d()) return false;
                }
                return true;
            };
            if (!check()) return;

            // 植える
            ll target_crop_id = value_order_crops[crop_i].id();
            m_sections[section_id].planted_crop_id(target_crop_id);
            m_available_section--;
            m_crops[target_crop_id].is_harvested(true);
            m_history.push_back(Output{target_crop_id, m_sections[section_id].h(), m_sections[section_id].w(), now_turn});
            crop_i++;
        };
        ll crop_i = 0;
        dfs(dfs, start, crop_i);
    }

    // 収穫ターンにすること
    void harvest_turn(ll now_turn) {
        ll start = m_i0*mW + 0;

        auto dfs = [&](auto dfs, ll section_id) {
            if (m_sections[section_id].planted_crop_id() != -1) {
                // このセクションに作物が植えられている場合
                ll cid = m_sections[section_id].planted_crop_id();
                if (m_crops[cid].d() == now_turn) {
                    // 収穫できるとき
                    m_crops[cid].is_harvested(true);
                    m_sections[section_id].planted_crop_id(-1);
                    m_available_section++;
                }
                else {
                    // 収穫できなかったとき
                    return;
                }
            }

            // 次の探索
            for(ll n_sec_id: m_sections[section_id].to()) {
                dfs(dfs, n_sec_id);
            }
        };
        dfs(dfs, start);
    }

    // 計画を立てる
    void run() {
        for(ll turn=1; turn<=100; turn++) {
            plan_greedy(turn);
            harvest_turn(turn);
        }
    }

    // 答えを出力する
    void output() {
        cout << m_history.size() << endl;
        for(Output output: m_history) {
            output.output();
        }
    }
};

void solve() {
    Solver solver = Solver();
    solver.input_and_build();
    solver.run();
    // cout << solver.calc_eval() << endl;
    solver.output();
}


int main() {
    solve();
    return 0;
}