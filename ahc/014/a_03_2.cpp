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
ll S;  // 評価関数のS
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
ll g_count;  // debug



/**
 * @brief 2022/09/20
 * 【メモ】
 * 重心から近い点をたくさん作るより、少なくても重心から遠い点を作れたほうが良さそう?
 * 外側の点から処理して、なるべく外側に広がっていくように点を作っていけば良さそう。
 *
 * 【方針】
 * ビームサーチの実装
 * データ構造を変えたり、関数の返り値を変えたりした。
 * ビームサーチがTLEするのでお蔵入り
 *
 */

struct Point {
    ll x, y;
};
bool operator< (const Point& p1, const Point& p2) {
    if (p1.x == p2.x) {
        return (p1.y < p2.y);
    }
    return (p1.x < p2.x);
}
bool operator== (const Point& p1, const Point& p2) {
    return ((p1.x==p2.x) && (p1.y==p2.y));
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
 * @brief ビームサーチで保持する状態
 *
 */
struct State {
    ll score;  // 暫定スコア
    set<Point> point_set;  // 印のある点集合
    set<Line> line_set;  // 辺の集合
    vector<RECT> rects;  // 作成した矩形
    ll last_pos;  // beam[i-1][どこ]から遷移したか
};
bool operator< (const State& s1, const State& s2) {
    return s1.score < s2.score;
}
bool operator> (const State& s1, const State& s2) {
    return s1.score > s2.score;
}


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


/**
 * @brief 評価関数
 *
 * @param grid
 * @return ll
 */
ll evaluate_score(const set<Point> &point_set) {
    ll c = (N-1)/2;
    double q = 0;
    for(auto point: point_set) {
        ll x = point.x;
        ll y = point.y;
        q += (x-c)*(x-c)+(y-c)*(y-c)+1;
    }
    return (ll)round((double)1e6 * ((double)(N*N)/M) * ((double)q/S));
}


// (x2,y2)---(tx,ty)
//    |         |
// (sx,sy)---(x1,y1)
bool make_rect_A1(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++;
            Line line(x,y,x-1,y);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, x1, y1, sx, sy, x2, y2};
    return true;
}

// (tx,ty)---(x2,y2)
//    |         |
// (sx,sy)---(x1,y1)
bool make_rect_A2(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--;
            Line line(x,y,x+1,y);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, sx, sy, x1, y1, x2, y2};
    return true;
}

// (x1,y1)---(x2,y2)
//    |         |
// (sx,sy)---(tx,ty)
bool make_rect_A3(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            y--;
            Line line(x,y,x,y+1);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, x2, y2, x1, y1, sx, sy};
    return true;
}

// (sx,sy)---(x1,y1)
//    |         |
// (x2,y2)---(tx,ty)
bool make_rect_B1(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++;
            Line line(x,y,x-1,y);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, x1, y1, sx, sy, x2, y2};
    return true;
}

// (sx,sy)---(tx,ty)
//    |         |
// (x1,y1)---(x2,y2)
bool make_rect_B2(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            y++;
            Line line(x,y,x,y-1);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, sx, sy, x1, y1, x2, y2};
    return true;
}

// (sx,sy)---(x1,y1)
//    |         |
// (tx,ty)---(x2,y2)
bool make_rect_B3(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--;
            Line line(x,y,x+1,y);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, x2, y2, x1, y1, sx, sy};
    return true;
}

// (x1,y1)---(sx,sy)
//    |         |
// (tx,ty)---(x2,y2)
bool make_rect_C1(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--;
            Line line(x,y,x+1,y);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, x1, y1, sx, sy, x2, y2};
    return true;
}

// (tx,ty)---(sx,sy)
//    |         |
// (x2,y2)---(x1,y1)
bool make_rect_C2(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            y++;
            Line line(x,y,x,y-1);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, x2, y2, x1, y1, sx, sy};
    return true;
}

// (x1,y1)---(sx,sy)
//    |         |
// (x2,y2)---(tx,ty)
bool make_rect_C3(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++;
            Line line(x,y,x-1,y);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, sx, sy, x1, y1, x2, y2};
    return true;
}

// (tx,ty)---(x1,y1)
//    |         |
// (x2,y2)---(sx,sy)
bool make_rect_D1(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            y++;
            Line line(x,y,x,y-1);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, x1, y1, sx, sy, x2, y2};
    return true;
}

// (x2,y2)---(tx,ty)
//    |         |
// (x1,y1)---(sx,sy)
bool make_rect_D2(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++;
            Line line(x,y,x-1,y);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, x2, y2, x1, y1, sx, sy};
    return true;
}

// (x2,y2)---(x1,y1)
//    |         |
// (tx,ty)---(sx,sy)
bool make_rect_D3(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            y--;
            Line line(x,y,x,y+1);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, sx, sy, x1, y1, x2, y2};
    return true;
}

//     (x1,y1)
//     ／    ＼
// (sx,sy) (tx,ty)
//     ＼    ／
//     (x2,y2)
bool make_rect_E1(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, x1, y1, sx, sy, x2, y2};
    return true;
}

//     (tx,ty)
//     ／    ＼
// (sx,sy) (x2,y2)
//     ＼    ／
//     (x1,y1)
bool make_rect_E2(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, sx, sy, x1, y1, x2, y2};
    return true;
}

//     (x1,y1)
//     ／    ＼
// (sx,sy) (x2,y2)
//     ＼    ／
//     (tx,ty)
bool make_rect_E3(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, x2, y2, x1, y1, sx, sy};
    return true;
}

//     (sx,sy)
//     ／    ＼
// (x1,y1) (x2,y2)
//     ＼    ／
//     (tx,ty)
bool make_rect_F1(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, x1, y1, sx, sy, x2, y2};
    return true;
}

//     (sx,sy)
//     ／    ＼
// (tx,ty) (x1,y1)
//     ＼    ／
//     (x2,y2)
bool make_rect_F2(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, x2, y2, x1, y1, sx, sy};
    return true;
}

//     (sx,sy)
//     ／    ＼
// (x1,y1) (tx,ty)
//     ＼    ／
//     (x2,y2)
bool make_rect_F3(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, sx, sy, x1, y1, x2, y2};
    return true;
}

//     (x1,y1)
//     ／    ＼
// (tx,ty) (sx,sy)
//     ＼    ／
//     (x2,y2)
bool make_rect_G1(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, x1, y1, sx, sy, x2, y2};
    return true;
}

//     (tx,ty)
//     ／    ＼
// (x2,y2) (sx,sy)
//     ＼    ／
//     (x1,y1)
bool make_rect_G2(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, x2, y2, x1, y1, sx, sy};
    return true;
}

//     (x1,y1)
//     ／    ＼
// (x2,y2) (sx,sy)
//     ＼    ／
//     (tx,ty)
bool make_rect_G3(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, sx, sy, x1, y1, x2, y2};
    return true;
}

//     (tx,ty)
//     ／    ＼
// (x1,y1) (x2,y2)
//     ＼    ／
//     (sx,sy)
bool make_rect_H1(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, x1, y1, sx, sy, x2, y2};
    return true;
}

//     (x2,y2)
//     ／    ＼
// (tx,ty) (x1,y1)
//     ＼    ／
//     (sx,sy)
bool make_rect_H2(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, sx, sy, x1, y1, x2, y2};
    return true;
}

//     (x2,y2)
//     ／    ＼
// (x1,y1) (tx,ty)
//     ＼    ／
//     (sx,sy)
bool make_rect_H3(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (!point_set.count(Point{x,y})) continue;
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
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (line_set.count(line)) return false;
            res_line_set.insert(line);
            if (point_set.count(Point{x,y})) return false;
        }
    }

    res_rect = {tx, ty, x2, y2, x1, y1, sx, sy};
    return true;
}

using MAKE_POINT_FUNC = bool (*)(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set);
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
bool make_rect(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set, RECT &res_rect, set<Line> &res_line_set) {
    vector<MAKE_POINT_FUNC> func_table = make_rect_table;
    shuffle(func_table.begin(), func_table.end(), engine);  // TODO シャッフルオフ

    for(auto func: func_table) {
        bool is_ok = func(sx, sy, max_len, point_set, line_set, res_rect, res_line_set);
        if (is_ok) return true;
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
 * @return vector<pair<RECT, set<Line>>>
 */
vector<pair<RECT, set<Line>>> make_rect_sequence(ll sx, ll sy, ll max_len, const set<Point> &point_set, const set<Line> &line_set) {
    vector<pair<RECT, set<Line>>> ans;

    ll x = sx, y = sy;
    set<Point> proc_point_set = point_set;  // 処理用
    set<Line> proc_line_set = line_set;  // 処理用

    while(1) {
        RECT res_rect;
        set<Line> res_line_set;
        bool is_ok = make_rect(x, y, max_len, proc_point_set, proc_line_set, res_rect, res_line_set);
        if (!is_ok) { break; }

        ans.push_back({res_rect, res_line_set});

        // 処理用の点集合と線集合に反映させる
        tie(x, y, ignore, ignore, ignore, ignore, ignore, ignore) = res_rect;
        proc_point_set.insert(Point{x,y});
        for(auto line: res_line_set) { proc_line_set.insert(line); }
    }

    return ans;
}

/**
 * @brief (sx,sy)からすべての方向に矩形を作れるか試し、作成可能な矩形候補を返す
 *
 * @param sx
 * @param sy
 * @param max_len
 * @param grid
 * @param line_set
 * @return pair<vector<RECT>, vector<set<Line>>>
 */
pair<vector<RECT>, vector<set<Line>>> makable_rects_and_line_sets(ll sx, ll sy, ll max_len, const set<Point> &point_set, set<Line> &line_set) {
    vector<RECT> makable_rects;
    vector<set<Line>> makable_line_sets;

    vector<MAKE_POINT_FUNC> func_table = make_rect_table;

    for(auto func: func_table) {
        RECT new_rect;
        set<Line> new_line_set;
        bool is_ok = func(sx, sy, max_len, point_set, line_set, new_rect, new_line_set);
        if (is_ok) {
            makable_rects.push_back(new_rect);
            makable_line_sets.push_back(new_line_set);
        }
    }

    return {makable_rects, makable_line_sets};
}


/**
 * @brief rects から、暫定的な良さを計算する
 *
 * @param rects
 * @return ll
 */
ll evaluate_rects(vector<RECT> const &rects) {
    ll score = 0;
    ll c = (N-1)/2;
    for(auto rect: rects) {
        ll tx, ty;
        tie(tx, ty, ignore, ignore, ignore, ignore, ignore, ignore) = rect;
        score += (tx-c)*(tx-c) + (ty-c)*(ty-c) + 1;
    }
    return score;
}


/**
 * @brief 外側にある点順にソートする用の比較関数
 *
 * @return true
 * @return false
 */
bool comp_outer_order(const pair<ll,ll> &a, const pair<ll,ll> &b) {
    ll c = (N+1)/2;
    ll d1 = abs(a.first-c) + abs(a.second-c);
    ll d2 = abs(b.first-c) + abs(b.second-c);
    return d1 > d2;
}

/**
 * @brief 内側にある点順にソートする用の比較関数
 *
 * @return true
 * @return false
 */
bool comp_inner_order(const pair<ll,ll> &a, const pair<ll,ll> &b) {
    ll c = (N+1)/2;
    ll d1 = abs(a.first-c) + abs(a.second-c);
    ll d2 = abs(b.first-c) + abs(b.second-c);
    return d1 < d2;
}


/**
 * @brief ビームサーチ用のRECTのスコア計算
 *
 * @param rect
 * @return ll
 */
ll calculate_rect_score(const RECT &rect) {
    ll tx, ty;
    tie(tx, ty, ignore, ignore, ignore, ignore, ignore, ignore) = rect;
    ll c = (N-1)/2;
    return (tx-c)*(tx-c) + (ty-c)*(ty-c) + 1;
}

/**
 * @brief ビームサーチ用の点集合のスコア計算
 *
 * @param point_set
 * @return ll
 */
ll calculate_state_score(const set<Point> &point_set) {
    ll total = 0;
    ll c = (N-1)/2;
    for(auto point: point_set) {
        ll x = point.x;
        ll y = point.y;
        total += (x-c)*(x-c) + (y-c)*(y-c) + 1;
    }
    return total;
}

/**
 * @brief ビームサーチ
 *
 * @param start_clock
 * @param max_len
 * @param grid
 * @param line_set
 * @param points
 * @return vector<RECT>
 */
vector<RECT> beam_search_solver(clock_t start_clock, ll max_len, const set<Point> &point_set, ll &res_score) {
    vector<vector<State>> beam(N*N+5);  // beam[i][j] := i手目終了時点での第j位の状態
    ll BEAM_WIDTH = 10;  // ビーム幅

    // beamの初期状態を作成する
    {
        set<Line> init_line_set;  // ((x1,y1) (x2,y2)) を結ぶ線が存在する
        ll init_score = calculate_state_score(point_set);
        priority_queue<State, vector<State>, greater<State>> candidate_pq;  // ビーム幅分だけ確保したい
        for(auto point: point_set) {
            ll sx = point.x;
            ll sy = point.y;

            auto rects_and_line_sets = make_rect_sequence(sx, sy, max_len, point_set, init_line_set);
            if (rects_and_line_sets.size() == 0) continue;

            // このときの状態を作成する
            ll beam_score = init_score;
            set<Point> beam_point_set = point_set;
            set<Line> beam_line_set;
            vector<RECT> beam_rects;
            for(auto [rect, lin_st]: rects_and_line_sets) {
                beam_score += calculate_rect_score(rect);
                ll tx, ty;
                tie(tx, ty, ignore, ignore, ignore, ignore, ignore, ignore) = rect;
                beam_point_set.insert(Point{tx,ty});
                for(auto lin: lin_st) { beam_line_set.insert(lin); }
                beam_rects.push_back(rect);
            }

            State new_state = State{beam_score, beam_point_set, beam_line_set, beam_rects, -1};
            if ((ll)candidate_pq.size() < BEAM_WIDTH) {
                candidate_pq.push(new_state);
            }
            else {
                State last_state = candidate_pq.top();
                if (last_state.score < new_state.score) {
                    candidate_pq.pop();
                    candidate_pq.push(new_state);
                }
            }
        }

        // 上位陣をbeam[0]に入れる
        while(!candidate_pq.empty()) {
            State state = candidate_pq.top(); candidate_pq.pop();
            beam[0].push_back(state);
        }
        sort(beam[0].begin(), beam[0].end());
        reverse(beam[0].begin(), beam[0].end());
    }

    // ビームサーチ
    {
        for(ll i=1; i<=N*N; i++) {
            // 前回の上位陣を追加しておく（最高得点の場合があるので）
            for(ll j=0; j<(ll)beam[i-1].size(); j++) {
                beam[i].push_back(beam[i-1][j]);
            }

            // 前回の状態から遷移させ、候補を探す
            bool is_found = false;  // 新しい遷移状態が見つかったか？
            priority_queue<State, vector<State>, greater<State>> candidate_pq;  // ビーム幅分だけ確保したい
            for(ll j=0; j<(ll)beam[i-1].size(); j++) {
                State state = beam[i-1][j];

                // 各点で矩形を作り、候補リストに追加する
                for(auto point: state.point_set) {
                    ll sx = point.x;
                    ll sy = point.y;
                    auto rects_and_line_sets = make_rect_sequence(sx, sy, max_len, state.point_set, state.line_set);
                    if ((ll)rects_and_line_sets.size() == 0) continue;

                    // このときの状態を作成し、ビームリストに追加する
                    is_found = true;
                    ll new_score = state.score;
                    set<Point> new_point_set = state.point_set;
                    set<Line> new_line_set = state.line_set;
                    vector<RECT> new_rects;
                    for(auto [rect, lin_st]: rects_and_line_sets) {
                        new_score += calculate_rect_score(rect);
                        ll tx, ty;
                        tie(tx, ty, ignore, ignore, ignore, ignore, ignore, ignore) = rect;
                        new_point_set.insert(Point{tx,ty});
                        for(auto lin: lin_st) new_line_set.insert(lin);
                        new_rects.push_back(rect);
                    }

                    State new_state = State{new_score, new_point_set, new_line_set, new_rects, j};
                    if ((ll)candidate_pq.size() < BEAM_WIDTH) {
                        candidate_pq.push(new_state);
                    }
                    else {
                        State last_state = candidate_pq.top();
                        if (last_state.score < new_state.score) {
                            candidate_pq.pop();
                            candidate_pq.push(new_state);
                        }
                    }
                }
            }

            // 上位陣をbeam[0]に入れる
            while(!candidate_pq.empty()) {
                State state = candidate_pq.top(); candidate_pq.pop();
                beam[i].push_back(state);
            }
            sort(beam[i].begin(), beam[i].end());
            reverse(beam[i].begin(), beam[i].end());

            if (!is_found) break;
        }
    }

    // ビームサーチ終了。最も高いスコアの状態を探す
    ll end_i = -1;
    for(ll i=N*N; i>=0; i--) {
        if (beam[i].size() >= 1) {
            end_i = i;
            break;
        }
    }

    // ベストスコアをセットする
    res_score = evaluate_score(beam[end_i][0].point_set);

    // 出力用の履歴を作成する
    vector<RECT> ans;
    {
        ll j = 0;
        for(ll i=end_i; i>=0; i--) {
            State best_state = beam[i][j];
            for(ll k=(ll)best_state.rects.size()-1; k>=0; k--) {
                ans.push_back(best_state.rects[k]);
            }
            j = best_state.last_pos;
            if (j == -1) break;
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}


vector<RECT> second_solver(clock_t start_clock, ll max_len, set<Point> &point_set, set<Line> &line_set) {
    vector<RECT> ans;

    // x座標とy座標はランダムで決める
    // vector<ll> xs(N);
    // vector<ll> ys(N);
    // for(ll i=0; i<N; i++) xs[i] = i;
    // for(ll i=0; i<N; i++) ys[i] = i;
    // shuffle(xs.begin(), xs.end(), engine);
    // shuffle(ys.begin(), ys.end(), engine);

    const ll TRY_COUNT = 3;
    bool do_loop = true;

    while(do_loop || max_len<N) {
        if (clock() - start_clock > TIME_LIMIT_SECOND_SOLVER) break;  // 時間切れ
        do_loop = false;

        for(auto point: point_set) {
            ll x = point.x, y = point.y;

            vector<RECT> best_rects;
            ll best_score = 0;
            vector<vector<ll>> best_grid;
            set<Line> best_line_set;

            for(ll i=0; i<TRY_COUNT; i++) {

                auto rects_and_line_sets = make_rect_sequence(x, y, max_len, point_set, line_set);
                if (rects_and_line_sets.size() == 0) break;

                ll score = evaluate_rects(rects);
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


void solve() {
    // 入力
    cin >> N >> M;
    set<Point> init_point_set;  // 印のある点集合
    for(ll i=0; i<M; i++) {
        ll x, y; cin >> x >> y;
        init_point_set.insert(Point{x,y});
    }

    // 評価関数のパラメータSを作成
    for(ll x=0; x<N; x++) {
        for(ll y=0; y<N; y++) {
            ll c = (N-1)/2;
            S += (x-c)*(x-c) + (y-c)*(y-c) + 1;
        }
    }

    // クロックスタート
    clock_t start_clock = clock();

    // 貪欲に初期解を作る
    vector<RECT> best_history;
    ll best_score = -1;
    ll count = 0;
    // vector<ll> max_len_table = {1, N/5, N/2, N};  // N/2 とかが良さそう
    // vector<ll> max_len_table = {N, 1};
    // vector<ll> max_len_table = {1, N/2, N/5};
    vector<ll> max_len_table = {1};

    for(auto max_len: max_len_table) {
        while(clock() - start_clock <= TIME_LIMIT_SOLVER) {
            count++;
            ll res_score;
            // vector history = beam_search_solver(start_clock, max_len, init_point_set, res_score);
            vector history = naive_search_solver(start_clock, 1, init_point_set, res_score);
            best_score = res_score;
            best_history = history;
            break;
            // ll score = evaluate_score(point_set);
            // if (score > best_score) {
            //     best_history = history;
            //     best_score = score;
            // }
        }
        break;
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
    set<Point> point_set;
    Point p1{1, 1};
    Point p2{1, 2};
    Point p3{2, 1};
    Point p4{1, 1};
    Point p5{1, 2};
    point_set.insert(p1);
    point_set.insert(p2);
    point_set.insert(p3);
    point_set.insert(p4);
    if (point_set.count(p5)) {
        cout << "Yes" << endl;
    }
    cout << "END" << endl;
}

int main() {
    // test();
    solve();
    return 0;
}