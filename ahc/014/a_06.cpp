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
ll N, M;
ll S;
// メルセンヌ・ツイスター法による疑似乱数生成器を、ハードウェア乱数をシードにして初期化
std::random_device seed_gen;
std::mt19937 engine(seed_gen());
using RECT = tuple<ll,ll,ll,ll,ll,ll,ll,ll>;

// タイムリミット
const clock_t TIME_LIMIT_SOLVER = 4.5*CLOCKS_PER_SEC;
const clock_t TIME_LIMIT_SECOND_SOLVER = 4.8*CLOCKS_PER_SEC;
// テスト用（十分長い時間）
// const clock_t TIME_LIMIT_SOLVER = 60*CLOCKS_PER_SEC;
// const clock_t TIME_LIMIT_SECOND_SOLVER = 60*CLOCKS_PER_SEC;



/**
 * @brief 2022/09/20
 * 今度こそビームサーチ
 *
 */


/**
 * @brief 座標(x,y)がgrid内に収まっているか？
 *
 * @param x
 * @param y
 * @return true
 * @return false
 */
bool is_inside_grid(ll x, ll y) {
    return (0<=x && x<N && 0<=y && y<N);
}

void calculate_S() {
    S = 0;
    ll c = (N-1)/2;
    for(ll x=0; x<N; x++) {
        for(ll y=0; y<N; y++) {
            S += (x-c)*(x-c)+(y-c)*(y-c)+1;
        }
    }
}

/**
 * @brief 評価関数
 *
 * @param grid
 * @return ll
 */
ll evaluate_score(vector<vector<ll>> const &grid) {
    ll c = (N-1)/2;
    double q = 0;
    for(ll x=0; x<N; x++) {
        for(ll y=0; y<N; y++) {
            if (grid[x][y] != 0) q += (x-c)*(x-c)+(y-c)*(y-c)+1;
        }
    }
    return (ll)round((double)1e6 * ((double)(N*N)/M) * ((double)q/S));
}

/**
 * @brief スコアを算出
 *
 * @param XYs
 * @return ll
 */
ll evaluate_score(vector<pair<ll,ll>> &XYs) {
    ll c = (N-1)/2;
    ll q = 0;
    for(auto xy: XYs) {
        ll x = xy.first, y = xy.second;
        q += (x-c)*(x-c) + (y-c)*(y-c) + 1;
    }
    return (ll)round((double)1e6 * ((double)(N*N)/M) * ((double)q/S));
}

/**
 * @brief 暫定スコアを算出
 *
 * @param rects
 * @return ll
 */
ll evaluate_score(vector<RECT> rects) {
    ll c = (N-1)/2;
    ll q = 0;
    for(auto rect: rects) {
        ll x, y;
        tie(x, y, ignore, ignore, ignore, ignore, ignore, ignore) = rect;
        q += (x-c)*(x-c) + (y-c)*(y-c) + 1;
    }
    return (ll)round((double)1e6 * ((double)(N*N)/M) * ((double)q/S));
}

struct Line {
    public:
        ll x1, y1;
        ll x2, y2;

        Line(ll _x1, ll _y1, ll _x2, ll _y2) {
            if (_x1 < _x2) {
                this->x1 = _x1; this->y1 = _y1;
                this->x2 = _x2; this->y2 = _y2;
            }
            else if (_x2 < _x1) {
                this->x1 = _x2; this->y1 = _y2;
                this->x2 = _x1; this->y2 = _y1;
            }
            else {
                if (_y1 <= _y2) {
                    this->x1 = _x1; this->y1 = _y1;
                    this->x2 = _x2; this->y2 = _y2;
                }
                else {
                    this->x1 = _x2; this->y1 = _y2;
                    this->x2 = _x1; this->y2 = _y1;
                }
            }
        }

        bool operator<(const Line &other) const {
            if (this->x1 == other.x1) {
                if (this->y1 == other.y1) {
                    if (this->x2 == other.x2) {
                        return (this->y2 < other.y2);
                    }
                    return (this->x2 < other.x2);
                }
                return (this->y1 < other.y1);
            }
            return (this->x1 < other.x1);
        }
        bool operator==(const Line &other) const {
            return (this->x1==other.x1 && this->y1==other.y1 && this->x2==other.x2 && this->y2==other.y2);
        }
};

/**
 * @brief ビームサーチ用の状態
 *
 */
struct State {
    ll score;
    ll max_len;
    vector<pair<ll,ll>> XYs;
    vector<vector<ll>> grid;
    set<Line> line_set;
    vector<RECT> rects;
    ll last_pos;
};
bool operator<(const State &s1, const State &s2) {
    return (s1.score < s2.score);
}
bool operator>(const State &s1, const State &s2) {
    return (s1.score > s2.score);
}
bool operator==(const State &s1, const State &s2) {
    return (s1.score == s2.score);
}


// (x2,y2)---(tx,ty)
//    |         |
// (sx,sy)---(x1,y1)
bool make_rect_A1(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++;
            Line line(x,y,x-1,y);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            y++;
            Line line(x,y,x,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x1, ty=y2;
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            y++;
            Line line(x,y,x,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++;
            Line line(x,y,x-1,y);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, x1, y1, sx, sy, x2, y2};
    return true;
}

// (tx,ty)---(x2,y2)
//    |         |
// (sx,sy)---(x1,y1)
bool make_rect_A2(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++;
            Line line(x,y,x-1,y);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = x1, y = y1;
        while(len <= max_len) {
            len++;
            y++;
            Line line(x,y,x,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=sx, ty=y2;
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=sx, y=sy;
        while(!(x==tx && y==ty)) {
            y++;
            Line line(x,y,x,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--;
            Line line(x,y,x+1,y);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, sx, sy, x1, y1, x2, y2};
    return true;
}

// (x1,y1)---(x2,y2)
//    |         |
// (sx,sy)---(tx,ty)
bool make_rect_A3(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            y++;
            Line line(x,y,x,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = x1, y = y1;
        while(len <= max_len) {
            len++;
            x++;
            Line line(x,y,x-1,y);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x2, ty=sy;
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=sx, y=sy;
        while(!(x==tx && y==ty)) {
            x++;
            Line line(x,y,x-1,y);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            y--;
            Line line(x,y,x,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, x2, y2, x1, y1, sx, sy};
    return true;
}

// (sx,sy)---(x1,y1)
//    |         |
// (x2,y2)---(tx,ty)
bool make_rect_B1(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++;
            Line line(x,y,x-1,y);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            y--;
            Line line(x,y,x,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x1, ty=y2;
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            y--;
            Line line(x,y,x,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++;
            Line line(x,y,x-1,y);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, x1, y1, sx, sy, x2, y2};
    return true;
}

// (sx,sy)---(tx,ty)
//    |         |
// (x1,y1)---(x2,y2)
bool make_rect_B2(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            y--;
            Line line(x,y,x,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = x1, y = y1;
        while(len <= max_len) {
            len++;
            x++;
            Line line(x,y,x-1,y);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x2, ty=sy;
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=sx, y=sy;
        while(!(x==tx && y==ty)) {
            x++;
            Line line(x,y,x-1,y);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            y++;
            Line line(x,y,x,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, sx, sy, x1, y1, x2, y2};
    return true;
}

// (sx,sy)---(x1,y1)
//    |         |
// (tx,ty)---(x2,y2)
bool make_rect_B3(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++;
            Line line(x,y,x-1,y);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = x1, y = y1;
        while(len <= max_len) {
            len++;
            y--;
            Line line(x,y,x,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=sx, ty=y2;
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=sx, y=sy;
        while(!(x==tx && y==ty)) {
            y--;
            Line line(x,y,x,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--;
            Line line(x,y,x+1,y);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, x2, y2, x1, y1, sx, sy};
    return true;
}

// (x1,y1)---(sx,sy)
//    |         |
// (tx,ty)---(x2,y2)
bool make_rect_C1(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--;
            Line line(x,y,x+1,y);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            y--;
            Line line(x,y,x,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x1, ty=y2;
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            y--;
            Line line(x,y,x,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--;
            Line line(x,y,x+1,y);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, x1, y1, sx, sy, x2, y2};
    return true;
}

// (tx,ty)---(sx,sy)
//    |         |
// (x2,y2)---(x1,y1)
bool make_rect_C2(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            y--;
            Line line(x,y,x,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = x1, y = y1;
        while(len <= max_len) {
            len++;
            x--;
            Line line(x,y,x+1,y);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x2, ty=sy;
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=sx, y=sy;
        while(!(x==tx && y==ty)) {
            x--;
            Line line(x,y,x+1,y);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            y++;
            Line line(x,y,x,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, x2, y2, x1, y1, sx, sy};
    return true;
}

// (x1,y1)---(sx,sy)
//    |         |
// (x2,y2)---(tx,ty)
bool make_rect_C3(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--;
            Line line(x,y,x+1,y);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = x1, y = y1;
        while(len <= max_len) {
            len++;
            y--;
            Line line(x,y,x,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x2, ty=sy;
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=sx, y=sy;
        while(!(x==tx && y==ty)) {
            y--;
            Line line(x,y,x,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++;
            Line line(x,y,x-1,y);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, sx, sy, x1, y1, x2, y2};
    return true;
}

// (tx,ty)---(x1,y1)
//    |         |
// (x2,y2)---(sx,sy)
bool make_rect_D1(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            y++;
            Line line(x,y,x,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--;
            Line line(x,y,x+1,y);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x2, ty=y1;
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            x--;
            Line line(x,y,x+1,y);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            y++;
            Line line(x,y,x,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, x1, y1, sx, sy, x2, y2};
    return true;
}

// (x2,y2)---(tx,ty)
//    |         |
// (x1,y1)---(sx,sy)
bool make_rect_D2(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--;
            Line line(x,y,x+1,y);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = x1, y = y1;
        while(len <= max_len) {
            len++;
            y++;
            Line line(x,y,x,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=sx, ty=y2;
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=sx, y=sy;
        while(!(x==tx && y==ty)) {
            y++;
            Line line(x,y,x,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++;
            Line line(x,y,x-1,y);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, x2, y2, x1, y1, sx, sy};
    return true;
}

// (x2,y2)---(x1,y1)
//    |         |
// (tx,ty)---(sx,sy)
bool make_rect_D3(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            y++;
            Line line(x,y,x,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = x1, y = y1;
        while(len <= max_len) {
            len++;
            x--;
            Line line(x,y,x+1,y);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x2, ty=sy;
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=sx, y=sy;
        while(!(x==tx && y==ty)) {
            x--;
            Line line(x,y,x+1,y);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            y--;
            Line line(x,y,x,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, sx, sy, x1, y1, x2, y2};
    return true;
}

//     (x1,y1)
//     ／    ＼
// (sx,sy) (tx,ty)
//     ＼    ／
//     (x2,y2)
bool make_rect_E1(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x2+(x1-sx), ty=y2+(y1-sy);
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, x1, y1, sx, sy, x2, y2};
    return true;
}

//     (tx,ty)
//     ／    ＼
// (sx,sy) (x2,y2)
//     ＼    ／
//     (x1,y1)
bool make_rect_E2(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = x1, y = y1;
        while(len <= max_len) {
            len++;
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=sx+(x2-x1), ty=sy+(y2-y1);
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=sx, y=sy;
        while(!(x==tx && y==ty)) {
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, sx, sy, x1, y1, x2, y2};
    return true;
}

//     (x1,y1)
//     ／    ＼
// (sx,sy) (x2,y2)
//     ＼    ／
//     (tx,ty)
bool make_rect_E3(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = x1, y = y1;
        while(len <= max_len) {
            len++;
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x2-(x1-sx), ty=y2-(y1-sy);
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=sx, y=sy;
        while(!(x==tx && y==ty)) {
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, x2, y2, x1, y1, sx, sy};
    return true;
}

//     (sx,sy)
//     ／    ＼
// (x1,y1) (x2,y2)
//     ＼    ／
//     (tx,ty)
bool make_rect_F1(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x2-(sx-x1), ty=y2-(sy-y1);
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, x1, y1, sx, sy, x2, y2};
    return true;
}

//     (sx,sy)
//     ／    ＼
// (tx,ty) (x1,y1)
//     ＼    ／
//     (x2,y2)
bool make_rect_F2(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = x1, y = y1;
        while(len <= max_len) {
            len++;
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=sx-(x1-x2), ty=sy-(y1-y2);
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=sx, y=sy;
        while(!(x==tx && y==ty)) {
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, x2, y2, x1, y1, sx, sy};
    return true;
}

//     (sx,sy)
//     ／    ＼
// (x1,y1) (tx,ty)
//     ＼    ／
//     (x2,y2)
bool make_rect_F3(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = x1, y = y1;
        while(len <= max_len) {
            len++;
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=sx+(x2-x1), ty=sy-(y1-y2);
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=sx, y=sy;
        while(!(x==tx && y==ty)) {
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, sx, sy, x1, y1, x2, y2};
    return true;
}

//     (x1,y1)
//     ／    ＼
// (tx,ty) (sx,sy)
//     ＼    ／
//     (x2,y2)
bool make_rect_G1(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x2-(sx-x1), ty=y1-(sy-y2);
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, x1, y1, sx, sy, x2, y2};
    return true;
}

//     (tx,ty)
//     ／    ＼
// (x2,y2) (sx,sy)
//     ＼    ／
//     (x1,y1)
bool make_rect_G2(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = x1, y = y1;
        while(len <= max_len) {
            len++;
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=sx-(x1-x2), ty=sy+(y2-y1);
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=sx, y=sy;
        while(!(x==tx && y==ty)) {
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, x2, y2, x1, y1, sx, sy};
    return true;
}

//     (x1,y1)
//     ／    ＼
// (x2,y2) (sx,sy)
//     ＼    ／
//     (tx,ty)
bool make_rect_G3(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = x1, y = y1;
        while(len <= max_len) {
            len++;
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=sx-(x1-x2), ty=sy-(y1-y2);
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=sx, y=sy;
        while(!(x==tx && y==ty)) {
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, sx, sy, x1, y1, x2, y2};
    return true;
}

//     (tx,ty)
//     ／    ＼
// (x1,y1) (x2,y2)
//     ＼    ／
//     (sx,sy)
bool make_rect_H1(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x2-(sx-x1), ty=y2+(y1-sy);
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, x1, y1, sx, sy, x2, y2};
    return true;
}

//     (x2,y2)
//     ／    ＼
// (tx,ty) (x1,y1)
//     ＼    ／
//     (sx,sy)
bool make_rect_H2(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = x1, y = y1;
        while(len <= max_len) {
            len++;
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=sx-(x1-x2), ty=sy+(y2-y1);
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=sx, y=sy;
        while(!(x==tx && y==ty)) {
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, sx, sy, x1, y1, x2, y2};
    return true;
}

//     (x2,y2)
//     ／    ＼
// (x1,y1) (tx,ty)
//     ＼    ／
//     (sx,sy)
bool make_rect_H3(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = x1, y = y1;
        while(len <= max_len) {
            len++;
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=sx+(x2-x1), ty=sy+(y2-y1);
    if (!is_inside_grid(tx,ty)) return false;
    {
        ll x=sx, y=sy;
        while(!(x==tx && y==ty)) {
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    res = {tx, ty, x2, y2, x1, y1, sx, sy};
    return true;
}

using MAKE_POINT_FUNC = bool (*)(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res);
vector<MAKE_POINT_FUNC> make_rect_table = {
    make_rect_A1, make_rect_A2, make_rect_A3,
    make_rect_B1, make_rect_B2, make_rect_B3,
    make_rect_C1, make_rect_C2, make_rect_C3,
    make_rect_D1, make_rect_D2, make_rect_D3,
    make_rect_E1, make_rect_E2, make_rect_E3,
    make_rect_F1, make_rect_F2, make_rect_F3,
    make_rect_G1, make_rect_G2, make_rect_G3,
    make_rect_H1, make_rect_H2, make_rect_H3,
};


// (sx,sy)に印をつけれるかを探索する
//
// (x2,y2)---(tx,ty)
//    |         |
// (sx,sy)---(x1,y1)
bool make_rect_RA1(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    if (grid[sx][sy] != 0) return false;

    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++;
            Line line(x,y,x-1,y);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            y++;
            Line line(x,y,x,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x1, ty=y2;
    if (!is_inside_grid(tx,ty)) return false;
    if (grid[tx][ty] == 0) return false;
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            y++;
            Line line(x,y,x,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (x==tx && y==ty) break;
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++;
            Line line(x,y,x-1,y);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (x==tx && y==ty) break;
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[sx][sy] = 2;
    res = {sx, sy, x1, y1, tx, ty, x2, y2};
    return true;
}

// (sx,sy)---(x1,y1)
//    |         |
// (x2,y2)---(tx,ty)
bool make_rect_RB1(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    if (grid[sx][sy] != 0) return false;

    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++;
            Line line(x,y,x-1,y);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            y--;
            Line line(x,y,x,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x1, ty=y2;
    if (!is_inside_grid(tx,ty)) return false;
    if (grid[tx][ty] == 0) return false;
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            y--;
            Line line(x,y,x,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (x==tx && y==ty) break;
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++;
            Line line(x,y,x-1,y);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (x==tx && y==ty) break;
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[sx][sy] = 2;
    res = {sx, sy, x1, y1, tx, ty, x2, y2};
    return true;
}

// (x1,y1)---(sx,sy)
//    |         |
// (tx,ty)---(x2,y2)
bool make_rect_RC1(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    if (grid[sx][sy] != 0) return false;

    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--;
            Line line(x,y,x+1,y);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            y--;
            Line line(x,y,x,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x1, ty=y2;
    if (!is_inside_grid(tx,ty)) return false;
    if (grid[tx][ty] == 0) return false;
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            y--;
            Line line(x,y,x,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (x==tx && y==ty) break;
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--;
            Line line(x,y,x+1,y);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (x==tx && y==ty) break;
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[sx][sy] = 2;
    res = {sx, sy, x1, y1, tx, ty, x2, y2};
    return true;
}

// (tx,ty)---(x1,y1)
//    |         |
// (x2,y2)---(sx,sy)
bool make_rect_RD1(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    if (grid[sx][sy] != 0) return false;

    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            y++;
            Line line(x,y,x,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--;
            Line line(x,y,x+1,y);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x2, ty=y1;
    if (!is_inside_grid(tx,ty)) return false;
    if (grid[tx][ty] == 0) return false;
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            x--;
            Line line(x,y,x+1,y);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (x==tx && y==ty) break;
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            y++;
            Line line(x,y,x,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (x==tx && y==ty) break;
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[sx][sy] = 2;
    res = {sx, sy, x1, y1, tx, ty, x2, y2};
    return true;
}

//     (x1,y1)
//     ／    ＼
// (sx,sy) (tx,ty)
//     ＼    ／
//     (x2,y2)
bool make_rect_RE1(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    if (grid[sx][sy] != 0) return false;

    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x2+(x1-sx), ty=y2+(y1-sy);
    if (!is_inside_grid(tx,ty)) return false;
    if (grid[tx][ty] == 0) return false;
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (x==tx && y==ty) break;
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (x==tx && y==ty) break;
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[sx][sy] = 2;
    res = {sx, sy, x1, y1, tx, ty, x2, y2};
    return true;
}

//     (sx,sy)
//     ／    ＼
// (x1,y1) (x2,y2)
//     ＼    ／
//     (tx,ty)
bool make_rect_RF1(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    if (grid[sx][sy] != 0) return false;

    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x2-(sx-x1), ty=y2-(sy-y1);
    if (!is_inside_grid(tx,ty)) return false;
    if (grid[tx][ty] == 0) return false;
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (x==tx && y==ty) break;
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (x==tx && y==ty) break;
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[sx][sy] = 2;
    res = {sx, sy, x1, y1, tx, ty, x2, y2};
    return true;
}

//     (x1,y1)
//     ／    ＼
// (tx,ty) (sx,sy)
//     ＼    ／
//     (x2,y2)
bool make_rect_RG1(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    if (grid[sx][sy] != 0) return false;

    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x2-(sx-x1), ty=y1-(sy-y2);
    if (!is_inside_grid(tx,ty)) return false;
    if (grid[tx][ty] == 0) return false;
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (x==tx && y==ty) break;
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (x==tx && y==ty) break;
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[sx][sy] = 2;
    res = {sx, sy, x1, y1, tx, ty, x2, y2};
    return true;
}

//     (tx,ty)
//     ／    ＼
// (x1,y1) (x2,y2)
//     ＼    ／
//     (sx,sy)
bool make_rect_RH1(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    if (grid[sx][sy] != 0) return false;

    vector<Line> lines;

    // (x1,y1) を探す
    ll x1, y1;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x1 = x; y1 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (x2,y2)を探す
    ll x2, y2;
    {
        bool is_ok = false;
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (!is_inside_grid(x,y)) break;
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            is_ok = true;
            x2 = x; y2 = y;
            break;
        }
        if (!is_ok) return false;
    }

    // (tx,ty)を探す
    ll tx=x2-(sx-x1), ty=y2+(y1-sy);
    if (!is_inside_grid(tx,ty)) return false;
    if (grid[tx][ty] == 0) return false;
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (x==tx && y==ty) break;
            if (grid[x][y] != 0) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (line_set.count(line)) return false;
            lines.push_back(line);
            if (x==tx && y==ty) break;
            if (grid[x][y] != 0) return false;
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[sx][sy] = 2;
    res = {sx, sy, x1, y1, tx, ty, x2, y2};
    return true;
}

using MAKE_POINT_R_FUNC = bool (*)(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res);
vector<MAKE_POINT_R_FUNC> make_rect_r_table = {
    make_rect_RA1,
    make_rect_RB1,
    make_rect_RC1,
    make_rect_RD1,
    make_rect_RE1,
    make_rect_RF1,
    make_rect_RG1,
    make_rect_RH1,
};

bool make_rect_r(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res_rect) {
    vector<MAKE_POINT_R_FUNC> table = make_rect_r_table;
    shuffle(table.begin(), table.end(), engine);

    for(auto func: table) {
        bool is_ok = func(sx, sy, max_len, grid, line_set, res_rect);
        if (!is_ok) continue;
        return true;
    }
    return false;
}

/**
 * @brief 外側の座標順に並べる比較関数
 *
 * @param p1
 * @param p2
 * @return true
 * @return false
 */
bool comp_outer_sort(pair<ll,ll> const &p1, pair<ll,ll> const &p2) {
    ll x1 = p1.first;
    ll y1 = p1.second;
    ll x2 = p2.first;
    ll y2 = p2.second;
    ll c = (N-1)/2;
    return (abs(x1-c) + abs(y1-c)) > (abs(x2-c) + abs(y2-c));
}

bool comp_inner_sort(pair<ll,ll> const &p1, pair<ll,ll> const &p2) {
    ll x1 = p1.first;
    ll y1 = p1.second;
    ll x2 = p2.first;
    ll y2 = p2.second;
    ll c = (N-1)/2;
    return (abs(x1-c) + abs(y1-c)) < (abs(x2-c) + abs(y2-c));
}

vector<pair<ll,ll>> make_outer_xys() {
    vector<pair<ll,ll>> XYs;
    for(ll x=0; x<N; x++) {
        for(ll y=0; y<N; y++) {
            XYs.push_back({x,y});
        }
    }
    sort(XYs.begin(), XYs.end(), comp_outer_sort);
    return XYs;
}

vector<pair<ll,ll>> make_inner_xys() {
    vector<pair<ll,ll>> XYs;
    for(ll x=0; x<N; x++) {
        for(ll y=0; y<N; y++) {
            XYs.push_back({x,y});
        }
    }
    sort(XYs.begin(), XYs.end(), comp_inner_sort);
    return XYs;
}

/**
 * @brief (sx,sy)から矩形をひとつ作る。
 * 作れなかった場合、falseを返す。
 * 作れたらtrueを返し、resに値が入っている。
 *
 * @param sx
 * @param sy
 * @param max_len
 * @param grid
 * @param line_set
 * @param res
 * @return bool
 */
bool make_rect(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set, RECT &res) {
    vector<MAKE_POINT_FUNC> table = make_rect_table;
    shuffle(table.begin(), table.end(), engine);

    for(auto func: table) {
        bool is_ok = func(sx, sy, max_len, grid, line_set, res);
        if (!is_ok) continue;
        return true;
    }
    return false;
}

/**
 * @brief (sx, sy)から矩形を作っていく。新しく矩形を作れたら、新しく作った印の付いた点を始点として、さらに矩形を作っていく
 *
 * @param sx
 * @param sy
 * @param max_len
 * @param grid
 * @param line_set
 * @return vector<RECT>
 */
vector<RECT> make_rect_sequence(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set) {
    vector<RECT> rects;
    ll x = sx, y = sy;
    while(1) {
        RECT res;
        bool is_ok = make_rect(x, y, max_len, grid, line_set, res);
        if (!is_ok) { break; }

        rects.push_back(res);
        tie(x, y, ignore, ignore, ignore, ignore, ignore, ignore) = res;
    }
    return rects;
}

/**
 * @brief 四角を作るために探索する
 *
 * @param max_len
 * @param grid
 * @param line_set
 * @return vector<RECT>
 */
vector<RECT> search(ll max_len, vector<vector<ll>> &grid, set<Line> &line_set) {
    vector<RECT> ans;

    for(ll sy=0; sy<N; sy++) {
        for(ll sx=0; sx<N; sx++) {
            if (grid[sx][sy] == 0) continue;

            // 印の付いた点を作る
            RECT res;
            bool is_ok = make_rect(sx, sy, max_len, grid, line_set, res);
            if (!is_ok) continue;
            ans.push_back(res);
        }
    }

    return ans;
}

/**
 * @brief 初期解作る
 *
 * @param grid
 */
vector<RECT> initial_solver(vector<vector<ll>> &grid, set<Line> &line_set) {
    vector<RECT> ans;

    // 辺の長さをすこしずつ大きくしながら探索を繰り返す
    ll max_len = 1;
    while(1) {
        auto res = search(max_len, grid, line_set);
        if ((ll)res.size() == 0) {
            max_len++;
            if (max_len >= N) break;
        }
        for(ll i=0; i<(ll)res.size(); i++) {
            ans.push_back(res[i]);
        }
    }

    return ans;
}


vector<RECT> second_solver(clock_t start_clock, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set) {
    vector<RECT> ans;

    // x座標とy座標はランダムで決める
    vector<pair<ll,ll>> XYs;
    for(ll x=0; x<N; x++) {
        for(ll y=0; y<N; y++) {
            if (grid[x][y] == 0) continue;
            XYs.push_back({x,y});
        }
    }

    const ll TRY_COUNT = 3;
    bool do_loop = true;

    while(do_loop || max_len<N) {
        if (clock() - start_clock > TIME_LIMIT_SECOND_SOLVER) break;  // 時間切れ
        do_loop = false;

        shuffle(XYs.begin(), XYs.end(), engine);  // 処理する順番はランダムに決める
        for(ll i=0; i<(ll)XYs.size(); i++) {
            auto[x, y] = XYs[i];
            if (grid[x][y] == 0) continue;

            vector<RECT> best_rects;
            ll best_score = 0;
            vector<vector<ll>> best_grid;
            set<Line> best_line_set;
            ll best_x, best_y;

            for(ll c=0; c<TRY_COUNT; c++) {
                vector<vector<ll>> tmp_grid = grid;
                set<Line> tmp_line_set = line_set;

                auto rects = make_rect_sequence(x, y, max_len, tmp_grid, tmp_line_set);
                ll score = evaluate_score(rects);
                if (score > best_score) {
                    best_score = score;
                    best_rects = rects;
                    best_grid = tmp_grid;
                    best_line_set = tmp_line_set;
                    best_x = x;
                    best_y = y;
                }
            }

            if ((ll)best_rects.size() != 0) {
                do_loop = true;
                for(auto rect: best_rects) ans.push_back(rect);
                grid = best_grid;
                line_set = best_line_set;
                XYs.push_back({best_x, best_y});  // これ本当に大丈夫？
            }
        }

        if (!do_loop) {
            max_len = min(max_len*2, N);
        }
    }

    return ans;
}

void beam_search_main(vector<pair<ll,ll>> &XYs, vector<vector<ll>> &grid, const ll TRY_COUNT, set<Line> &line_set, bool &is_found, ll &max_len, vector<RECT> &res_rects) {
    shuffle(XYs.begin(), XYs.end(), engine);  // 処理する順番はランダムに決める
    for(ll i=0; i<(ll)XYs.size(); i++) {
        auto[x, y] = XYs[i];
        if (grid[x][y] == 0) continue;

        vector<RECT> best_rects;
        ll best_score = 0;
        vector<vector<ll>> best_grid;
        set<Line> best_line_set;

        for(ll c=0; c<TRY_COUNT; c++) {
            vector<vector<ll>> tmp_grid = grid;
            set<Line> tmp_line_set = line_set;

            auto rects = make_rect_sequence(x, y, max_len, tmp_grid, tmp_line_set);
            ll score = evaluate_score(rects);
            if (score > best_score) {
                best_score = score;
                best_rects = rects;
                best_grid = tmp_grid;
                best_line_set = tmp_line_set;
            }
        }

        if ((ll)best_rects.size() != 0) {
            is_found = true;
            for(auto rect: best_rects) {
                res_rects.push_back(rect);
                ll tx, ty;
                tie(tx, ty, ignore, ignore, ignore, ignore, ignore, ignore) = rect;
                XYs.push_back({tx, ty});  // これ本当に大丈夫？
            }
            grid = best_grid;
            line_set = best_line_set;
        }
    }

    if (!is_found) {
        max_len = min(max_len*2, N);
    }
}

void beam_search_main_simple(vector<pair<ll,ll>> &XYs, vector<vector<ll>> &grid, const ll TRY_COUNT, set<Line> &line_set, bool &is_found, ll &max_len, vector<RECT> &res_rects) {
    shuffle(XYs.begin(), XYs.end(), engine);  // 処理する順番はランダムに決める
    for(ll i=0; i<(ll)XYs.size(); i++) {
        auto[x, y] = XYs[i];
        if (grid[x][y] == 0) continue;

        auto rects = make_rect_sequence(x, y, max_len, grid, line_set);

        if ((ll)rects.size() != 0) {
            is_found = true;
            for(auto rect: rects) {
                res_rects.push_back(rect);
                ll tx, ty;
                tie(tx, ty, ignore, ignore, ignore, ignore, ignore, ignore) = rect;
                XYs.push_back({tx, ty});  // これ本当に大丈夫？
            }
        }
    }

    if (!is_found) {
        max_len = min(max_len*2, N);
    }
}

vector<RECT> beam_search_solver(clock_t start_clock, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set) {
    // 処理するx座標とy座標
    vector<pair<ll,ll>> XYs;
    for(ll x=0; x<N; x++) {
        for(ll y=0; y<N; y++) {
            if (grid[x][y] == 0) continue;
            XYs.push_back({x,y});
        }
    }

    const ll BEAM_WIDTH = 3;
    // vector<vector<State>> beam(N*N, vector<State>(BEAM_WIDTH));
    vector<vector<State>> beam;
    beam.push_back(vector<State>(BEAM_WIDTH));

    const ll TRY_COUNT = 3;

    // ビームの初期状態を作成
    {
        ll init_score = evaluate_score(XYs);

        for(ll bw=0; bw<BEAM_WIDTH; bw++) {
            vector<pair<ll,ll>> new_XYs = XYs;
            vector new_grid = grid;
            set<Line> new_line_set = line_set;
            vector<RECT> res_rects;
            ll new_max_len = max_len;
            bool is_found = false;

            // beam_search_main(new_XYs, new_grid, TRY_COUNT, new_line_set, is_found, new_max_len, res_rects);
            beam_search_main_simple(new_XYs, new_grid, TRY_COUNT, new_line_set, is_found, new_max_len, res_rects);

            ll new_score = init_score + evaluate_score(res_rects);
            beam[0][bw] = State{new_score, new_max_len, new_XYs, new_grid, new_line_set, res_rects, -1};
        }

        sort(beam[0].begin(), beam[0].end());
        reverse(beam[0].begin(), beam[0].end());
    }

    {  // ビームサーチ
        const ll SEARCH_WIDTH = 3;
        for(ll bi=0; bi<=N*N; bi++) {
            bool is_found_any = false;
            ll min_max_len = INF;  // max_lenの最小値
            priority_queue<State, vector<State>, greater<State>> beam_pq;  // ビーム用プライオリティキュー

            // 今回の状態をあらかじめ入れておく
            for(ll bw=0; bw<BEAM_WIDTH; bw++) {
                State state = beam[bi][bw];
                state.last_pos = bw;
                state.rects.resize(0);
                beam_pq.push(state);
            }

            // ビーム幅ぶん探索する
            for(ll bw=0; bw<BEAM_WIDTH; bw++) {
                State state = beam[bi][bw];
                min_max_len = min(min_max_len, state.max_len);

                // if (clock() - start_clock > TIME_LIMIT_SECOND_SOLVER) break;  // 時間切れ

                for(ll sw=0; sw<SEARCH_WIDTH; sw++) {
                    vector new_XYs = state.XYs;
                    vector new_grid = state.grid;
                    set<Line> new_line_set = state.line_set;
                    ll new_max_len = state.max_len;
                    vector<RECT> res_rects;
                    bool is_found = false;
                    // beam_search_main(new_XYs, new_grid, TRY_COUNT, new_line_set, is_found, new_max_len, res_rects);
                    beam_search_main_simple(new_XYs, new_grid, TRY_COUNT, new_line_set, is_found, new_max_len, res_rects);

                    if (is_found) { is_found_any = true; }
                    if (res_rects.size() == 0) {
                        state.max_len = new_max_len;
                        continue;
                    }

                    ll new_score = state.score + evaluate_score(res_rects);
                    State new_state = State{new_score, new_max_len, new_XYs, new_grid, new_line_set, res_rects, bw};

                    if (beam_pq.size() >= BEAM_WIDTH) {
                        auto low_state = beam_pq.top();
                        if (low_state < new_state) {
                            beam_pq.pop();
                            beam_pq.push(new_state);
                        }
                    }
                    else {
                        beam_pq.push(new_state);
                    }
                }
            }

            // 探索しきったなら、終わる
            if (!is_found_any && min_max_len>=N) break;

            // プライオリティキューの中身をbeam[i+1]に移す
            beam.push_back(vector<State>(BEAM_WIDTH));
            for(ll bw=0; bw<BEAM_WIDTH; bw++) {
                State s = beam_pq.top(); beam_pq.pop();
                beam[bi+1][bw] = s;
            }
            sort(beam[bi+1].begin(), beam[bi+1].end());
            reverse(beam[bi+1].begin(), beam[bi+1].end());
        }
    }

    // beamから最も良いスコアを復元する
    vector<RECT> ans;
    {
        ll bw = 0;
        for(ll bi=(ll)beam.size()-1; bi>=0; bi--) {
            State best_state = beam[bi][bw];
            for(ll ri=best_state.rects.size()-1; ri>=0; ri--) {
                ans.push_back(best_state.rects[ri]);
            }

            bw = best_state.last_pos;
            if (bw == -1) break;
        }
    }
    reverse(ans.begin(), ans.end());

    // 一応、grid等を更新しとく
    {
        State best_state = beam[beam.size()-1][0];
        grid = best_state.grid;
        line_set = best_state.line_set;
    }

    return ans;
}


vector<RECT> inner_second_solver(clock_t start_clock, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set) {
    vector<RECT> ans;

    // x座標とy座標はランダムで決める
    vector XYs = make_inner_xys();

    const ll TRY_COUNT = 3;
    bool do_loop = true;

    while(do_loop || max_len<N) {
        if (clock() - start_clock > TIME_LIMIT_SECOND_SOLVER) break;  // 時間切れ
        do_loop = false;

        for(auto xy: XYs) {
            ll x = xy.first, y = xy.second;
            if (grid[x][y] == 0) continue;

            vector<RECT> best_rects;
            ll best_score = 0;
            vector<vector<ll>> best_grid;
            set<Line> best_line_set;

            for(ll i=0; i<TRY_COUNT; i++) {
                vector<vector<ll>> tmp_grid = grid;
                set<Line> tmp_line_set = line_set;

                auto rects = make_rect_sequence(x, y, max_len, tmp_grid, tmp_line_set);
                ll score = evaluate_score(rects);
                if (score > best_score) {
                    best_score = score;
                    best_rects = rects;
                    best_grid = tmp_grid;
                    best_line_set = tmp_line_set;
                }
            }

            if ((ll)best_rects.size() != 0) {
                do_loop = true;
                for(auto rect: best_rects) ans.push_back(rect);
                grid = best_grid;
                line_set = best_line_set;
            }
        }

        if (!do_loop) {
            max_len = min(max_len*2, N);
        }
    }

    return ans;
}

vector<RECT> outer_second_solver(clock_t start_clock, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set) {
    vector<RECT> ans;

    // x座標とy座標はランダムで決める
    vector XYs = make_outer_xys();

    const ll TRY_COUNT = 3;
    bool do_loop = true;

    while(do_loop || max_len<N) {
        if (clock() - start_clock > TIME_LIMIT_SECOND_SOLVER) break;  // 時間切れ
        do_loop = false;

        for(auto xy: XYs) {
            ll x = xy.first, y = xy.second;
            if (grid[x][y] == 0) continue;

            vector<RECT> best_rects;
            ll best_score = 0;
            vector<vector<ll>> best_grid;
            set<Line> best_line_set;

            for(ll i=0; i<TRY_COUNT; i++) {
                vector<vector<ll>> tmp_grid = grid;
                set<Line> tmp_line_set = line_set;

                auto rects = make_rect_sequence(x, y, max_len, tmp_grid, tmp_line_set);
                ll score = evaluate_score(rects);
                if (score > best_score) {
                    best_score = score;
                    best_rects = rects;
                    best_grid = tmp_grid;
                    best_line_set = tmp_line_set;
                }
            }

            if ((ll)best_rects.size() != 0) {
                do_loop = true;
                for(auto rect: best_rects) ans.push_back(rect);
                grid = best_grid;
                line_set = best_line_set;
            }
        }

        if (!do_loop) {
            max_len = min(max_len*2, N);
        }
    }

    return ans;
}

/**
 * @brief 外側に点を作れそうなら優先的にそうするソルバー
 *
 * @param start_clock
 * @param max_len
 * @param grid
 * @param line_set
 * @return vector<RECT>
 */
vector<RECT> outer_second_solver_r(clock_t start_clock, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set) {
    vector<RECT> ans;

    // x座標とy座標はランダムで決める
    vector<pair<ll,ll>> XYs = make_outer_xys();

    // const ll TRY_COUNT = 3;
    bool do_loop = true;

    while(do_loop || max_len<N) {
        if (clock() - start_clock > TIME_LIMIT_SECOND_SOLVER) break;  // 時間切れ
        do_loop = false;

        for(auto xy: XYs) {
            ll x = xy.first;
            ll y = xy.second;
            if (grid[x][y] != 0) continue;
            // if (grid[x][y] != 0) break;  // 外側にだけ作りたい

            RECT res_rect;
            bool is_ok = make_rect_r(x, y, max_len, grid, line_set, res_rect);
            if (!is_ok) continue;

            do_loop = true;
            ans.push_back(res_rect);
            break; //////////////////////////// TODO
        }

        if (!do_loop) {
            max_len = min(max_len*2, N);
        }
    }

    return ans;
}

/**
 * @brief 内側に点を作れそうなら優先的にそうするソルバー
 *
 * @param start_clock
 * @param max_len
 * @param grid
 * @param line_set
 * @return vector<RECT>
 */
vector<RECT> inner_second_solver_r(clock_t start_clock, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set) {
    vector<RECT> ans;

    // x座標とy座標はランダムで決める
    vector<pair<ll,ll>> XYs = make_inner_xys();

    // const ll TRY_COUNT = 3;
    bool do_loop = true;

    while(do_loop || max_len<N) {
        if (clock() - start_clock > TIME_LIMIT_SECOND_SOLVER) break;  // 時間切れ
        do_loop = false;

        for(auto xy: XYs) {
            ll x = xy.first;
            ll y = xy.second;
            if (grid[x][y] != 0) continue;
            // if (grid[x][y] != 0) break;  // 内側にだけ作りたい

            RECT res_rect;
            bool is_ok = make_rect_r(x, y, max_len, grid, line_set, res_rect);
            if (!is_ok) continue;

            do_loop = true;
            ans.push_back(res_rect);
            break; //////////////////////////// TODO
        }

        if (!do_loop) {
            max_len = min(max_len*2, N);
        }
    }

    return ans;
}

void solve() {
    cin >> N >> M;
    vector grid(N, vector<ll>(N, 0));  // 0:印のない格子点, 1:印のある格子点, 2: 追加した印のある格子点
    vector<pair<ll,ll>> XY(M);
    for(ll i=0; i<M; i++) {
        ll x, y; cin >> x >> y;
        XY.push_back({x,y});
        grid[x][y] = 1;
    }
    calculate_S();

    // クロックスタート
    clock_t start_clock = clock();

    // 貪欲に初期解を作る
    vector<RECT> best_history;
    ll best_score = -1;
    ll count = 0;/////////////////////////////TODO
    // vector<ll> max_len_table = {1, N/5, N/2, N};  // N/2 とかが良さそう
    // vector<ll> max_len_table = {N, 1};
    vector<ll> max_len_table = {1, N/2, N/5};
    // vector<ll> max_len_table = {N};

    for(auto max_len: max_len_table) {
        while(clock() - start_clock <= TIME_LIMIT_SOLVER) {
            count++;
            // {
            //     vector new_grid = grid;
            //     set<Line> line_set;  // ((x1,y1) (x2,y2)) を結ぶ線が存在する
            //     vector history = second_solver(start_clock, max_len, new_grid, line_set);
            //     ll score = evaluate_score(new_grid);
            //     if (score > best_score) {
            //         best_history = history;
            //         best_score = score;
            //     }
            // }

            // {
            //     vector new_grid = grid;
            //     set<Line> line_set;  // ((x1,y1) (x2,y2)) を結ぶ線が存在する
            //     vector history = second_solver(start_clock, max_len, new_grid, line_set);
            //     ll score = evaluate_score(new_grid);
            //     if (score > best_score) {
            //         best_history = history;
            //         best_score = score;
            //     }
            // }

            {
                vector new_grid = grid;
                set<Line> line_set;  // ((x1,y1) (x2,y2)) を結ぶ線が存在する
                vector history = beam_search_solver(start_clock, max_len, new_grid, line_set);
                ll score = evaluate_score(new_grid);
                if (score > best_score) {
                    best_history = history;
                    best_score = score;
                }
            }

            // if (clock() - start_clock >= TIME_LIMIT_SOLVER) break;
            // {
            //     vector new_grid = grid;
            //     set<Line> line_set;  // ((x1,y1) (x2,y2)) を結ぶ線が存在する
            //     vector history = outer_second_solver(start_clock, max_len, new_grid, line_set);
            //     ll score = evaluate_score(new_grid);
            //     if (score > best_score) {
            //         best_history = history;
            //         best_score = score;
            //     }
            // }

            // if (clock() - start_clock >= TIME_LIMIT_SOLVER) break;
            // {
            //     vector new_grid = grid;
            //     set<Line> line_set;  // ((x1,y1) (x2,y2)) を結ぶ線が存在する
            //     vector history = inner_second_solver(start_clock, max_len, new_grid, line_set);
            //     ll score = evaluate_score(new_grid);
            //     if (score > best_score) {
            //         best_history = history;
            //         best_score = score;
            //     }
            // }
        }
    }

    // テスト用出力
    cout << "best-score: " << best_score << endl;
    cout << "count: " << count << endl;
    cout << "elapsed-time: " << (double)(clock() - start_clock)/CLOCKS_PER_SEC << endl;

    // 出力
    printf("%lld\n", (ll)best_history.size());
    for(ll i=0; i<(ll)best_history.size(); i++) {
        auto[x1, y1, x2, y2, x3, y3, x4, y4] = best_history[i];
        printf("%lld %lld %lld %lld %lld %lld %lld %lld\n", x1, y1, x2, y2, x3, y3, x4, y4);
    }
}


void test() {
    set<Line> line_set;
    Line line1(24,26,25,27);
    Line line2(25,27,24,26);
    line_set.insert(line1);
    if (line_set.count(line2)) {
        cout << "Yes" << endl;
        line_set.insert(line2);
    }
    cout << "END" << endl;
}

int main() {
    // test();
    solve();
    return 0;
}