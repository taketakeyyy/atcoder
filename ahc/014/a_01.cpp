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


/**
 * @brief 2022/09/20
 * とりあえず初期解のみ実装
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


/**
 * @brief 評価関数
 *
 * @param grid
 * @return ll
 */
ll evaluate_score(vector<vector<ll>> const &grid) {
    ll c = (N-1)/2;
    double s = 0;
    double q = 0;
    for(ll x=0; x<N; x++) {
        for(ll y=0; y<N; y++) {
            s += (x-c)*(x-c)+(y-c)*(y-c)+1;
            if (grid[x][y] != 0) q += (x-c)*(x-c)+(y-c)*(y-c)+1;
        }
    }
    return (ll)round((double)1e6 * ((double)(N*N)/M) * ((double)q/s));
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


// (x2,y2)---(tx,ty)
//    |         |
// (sx,sy)---(x1,y1)
tuple<ll,ll,ll,ll,ll,ll,ll,ll> make_point_RU(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set) {
    vector<Line> lines;

    // (x1, y1) を探す
    ll x1 = -1, y1 = sy;
    ll len = -1;
    for(ll x=sx+1; x<N; x++) {
        len++;
        if (len >= max_len) break;
        Line line(x-1,y1,x,y1);
        if (line_set.count(line)) break;
        lines.push_back(line);
        if (grid[x][y1] == 0) continue;
        x1 = x; break;
    }
    if (x1 == -1) {
        return {-1, -1, -1, -1, -1, -1, -1, -1};
    }

    // (x2, y2) を探す
    ll x2 = sx, y2 = -1;
    len = -1;
    for(ll y=sy+1; y<N; y++) {
        len++;
        if (len >= max_len) break;
        Line line(x2,y-1,x2,y);
        if (line_set.count(line)) break;
        lines.push_back(line);
        if (grid[x2][y] == 0) continue;
        y2 = y; break;
    }
    if (y2 == -1) {
        return {-1, -1, -1, -1, -1, -1, -1, -1};
    }

    // (tx, ty) を探す
    ll tx = x1, ty = y2;
    for(ll x=x2+1; x<=tx; x++) {
        Line line(x-1,ty,x,ty);
        if (line_set.count(line)) return {-1, -1, -1, -1, -1, -1, -1, -1};
        lines.push_back(line);
        if (grid[x][ty] != 0) return {-1, -1, -1, -1, -1, -1, -1, -1};
    }
    for(ll y=y1+1; y<=ty; y++) {
        Line line(tx,y-1,tx,y);
        if (line_set.count(line)) return {-1, -1, -1, -1, -1, -1, -1, -1};
        lines.push_back(line);
        if (grid[tx][y] != 0) return {-1, -1, -1, -1, -1, -1, -1, -1};
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    return {tx, ty, x2, y2, sx, sy, x1, y1};
}

// (tx,ty)---(x2,y2)
//    |         |
// (x1,y1)---(sx,sy)
tuple<ll,ll,ll,ll,ll,ll,ll,ll> make_point_LU(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set) {
    vector<Line> lines;

    // (x1, y1) を探す
    ll x1 = -1, y1 = sy;
    ll len = -1;
    for(ll x=sx-1; x>=0; x--) {
        len++;
        if (len >= max_len) break;
        Line line(x,y1,x+1,y1);
        if (line_set.count(line)) break;
        lines.push_back(line);
        if (grid[x][y1] == 0) continue;
        x1 = x; break;
    }
    if (x1 == -1) {
        return {-1, -1, -1, -1, -1, -1, -1, -1};
    }

    // (x2, y2) を探す
    ll x2 = sx, y2 = -1;
    len = -1;
    for(ll y=sy+1; y<N; y++) {
        len++;
        if (len >= max_len) break;
        Line line(x2,y-1,x2,y);
        if (line_set.count(line)) break;
        lines.push_back(line);
        if (grid[x2][y] == 0) continue;
        y2 = y; break;
    }
    if (y2 == -1) {
        return {-1, -1, -1, -1, -1, -1, -1, -1};
    }

    // (tx, ty) を探す
    ll tx = x1, ty = y2;
    for(ll x=x2-1; x>=tx; x--) {
        Line line(x,ty,x+1,ty);
        if (line_set.count(line)) return {-1, -1, -1, -1, -1, -1, -1, -1};
        lines.push_back(line);
        if (grid[x][ty] != 0) return {-1, -1, -1, -1, -1, -1, -1, -1};
    }
    for(ll y=y1+1; y<=ty; y++) {
        Line line(tx,y-1,tx,y);
        if (line_set.count(line)) return {-1, -1, -1, -1, -1, -1, -1, -1};
        lines.push_back(line);
        if (grid[tx][y] != 0) return {-1, -1, -1, -1, -1, -1, -1, -1};
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    return {tx, ty, x1, y1, sx, sy, x2, y2};
}

// (x1,y1)---(sx,sy)
//    |         |
// (tx,ty)---(x2,y2)
tuple<ll,ll,ll,ll,ll,ll,ll,ll> make_point_LD(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set) {
    vector<Line> lines;

    // (x1, y1) を探す
    ll x1 = -1, y1 = sy;
    ll len = -1;
    for(ll x=sx-1; x>=0; x--) {
        len++;
        if (len >= max_len) break;
        Line line(x,sy,x+1,sy);
        if (line_set.count(line)) break;
        lines.push_back(line);
        if (grid[x][y1] == 0) continue;
        x1 = x; break;
    }
    if (x1 == -1) {
        return {-1, -1, -1, -1, -1, -1, -1, -1};
    }

    // (x2, y2) を探す
    ll x2 = sx, y2 = -1;
    len = -1;
    for(ll y=sy-1; y>=0; y--) {
        len++;
        if (len >= max_len) break;
        Line line(sx,y,sx,y+1);
        if (line_set.count(line)) break;
        lines.push_back(line);
        if (grid[x2][y] == 0) continue;
        y2 = y; break;
    }
    if (y2 == -1) {
        return {-1, -1, -1, -1, -1, -1, -1, -1};
    }

    // (tx, ty) を探す
    ll tx = x1, ty = y2;
    for(ll x=x2-1; x>=tx; x--) {
        Line line(x,ty,x+1,ty);
        if (line_set.count(line)) return {-1, -1, -1, -1, -1, -1, -1, -1};
        lines.push_back(line);
        if (grid[x][ty] != 0) return {-1, -1, -1, -1, -1, -1, -1, -1};
    }
    for(ll y=y1-1; y>=ty; y--) {
        Line line(tx,y,tx,y+1);
        if (line_set.count(line)) return {-1, -1, -1, -1, -1, -1, -1, -1};
        lines.push_back(line);
        if (grid[tx][y] != 0) return {-1, -1, -1, -1, -1, -1, -1, -1};
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    return {tx, ty, x2, y2, sx, sy, x1, y1};
}

// (sx,sy)---(x1,y1)
//    |         |
// (x2,y2)---(tx,ty)
tuple<ll,ll,ll,ll,ll,ll,ll,ll> make_point_RD(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set) {
    vector<Line> lines;

    // (x1, y1) を探す
    ll x1 = -1, y1 = sy;
    ll len = -1;
    for(ll x=sx+1; x<N; x++) {
        len++;
        if (len >= max_len) break;
        Line line(x-1,sy,x,sy);
        if (line_set.count(line)) break;
        lines.push_back(line);
        if (grid[x][y1] == 0) continue;
        x1 = x; break;
    }
    if (x1 == -1) {
        return {-1, -1, -1, -1, -1, -1, -1, -1};
    }

    // (x2, y2) を探す
    ll x2 = sx, y2 = -1;
    len = -1;
    for(ll y=sy-1; y>=0; y--) {
        len++;
        if (len >= max_len) break;
        Line line(sx,y,sx,y+1);
        if (line_set.count(line)) break;
        lines.push_back(line);
        if (grid[x2][y] == 0) continue;
        y2 = y; break;
    }
    if (y2 == -1) {
        return {-1, -1, -1, -1, -1, -1, -1, -1};
    }

    // (tx, ty) を探す
    ll tx = x1, ty = y2;
    for(ll x=x2+1; x<=tx; x++) {
        Line line(x-1,ty,x,ty);
        if (line_set.count(line)) return {-1, -1, -1, -1, -1, -1, -1, -1};
        lines.push_back(line);
        if (grid[x][ty] != 0) return {-1, -1, -1, -1, -1, -1, -1, -1};
    }
    for(ll y=y1-1; y>=ty; y--) {
        Line line(tx,y,tx,y+1);
        if (line_set.count(line)) return {-1, -1, -1, -1, -1, -1, -1, -1};
        lines.push_back(line);
        if (grid[tx][y] != 0) return {-1, -1, -1, -1, -1, -1, -1, -1};
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    return {tx, ty, x1, y1, sx, sy, x2, y2};
}

//     (x1,y1)
//     ／    ＼
// (sx,sy) (tx,ty)
//     ＼    ／
//     (x2,y2)
tuple<ll,ll,ll,ll,ll,ll,ll,ll> make_point_45_R(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1=-1, y1=-1;
    {
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++; y++;
            if (!is_inside_grid(x,y)) break;
            Line line(x,y,x-1,y-1);
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            x1 = x; y1 = y;
            break;
        }
        if (x1 == -1) return {-1,-1,-1,-1,-1,-1,-1,-1};
    }

    // (x2,y2)を探す
    ll x2=-1, y2=-1;
    {
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++; y--;
            if (!is_inside_grid(x,y)) break;
            Line line(x,y,x-1,y+1);
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            x2 = x; y2 = y;
            break;
        }
        if (x2 == -1) return {-1,-1,-1,-1,-1,-1,-1,-1};
    }

    // (tx,ty)を探す
    ll tx=x2+(x1-sx), ty=y2+(y1-sy);
    if (!is_inside_grid(tx,ty)) return {-1,-1,-1,-1,-1,-1,-1,-1};
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (line_set.count(line)) return {-1,-1,-1,-1,-1,-1,-1,-1};
            lines.push_back(line);
            if (grid[x][y] != 0) return {-1,-1,-1,-1,-1,-1,-1,-1};
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (line_set.count(line)) return {-1,-1,-1,-1,-1,-1,-1,-1};
            lines.push_back(line);
            if (grid[x][y] != 0) return {-1,-1,-1,-1,-1,-1,-1,-1};
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    return {tx, ty, x1, y1, sx, sy, x2, y2};
}

//     (tx,ty)
//     ／    ＼
// (x1,y1) (x2,y2)
//     ＼    ／
//     (sx,sy)
tuple<ll,ll,ll,ll,ll,ll,ll,ll> make_point_45_U(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1=-1, y1=-1;
    {
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--; y++;
            if (!is_inside_grid(x,y)) break;
            Line line(x,y,x+1,y-1);
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            x1 = x; y1 = y;
            break;
        }
        if (x1 == -1) return {-1,-1,-1,-1,-1,-1,-1,-1};
    }

    // (x2,y2)を探す
    ll x2=-1, y2=-1;
    {
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++; y++;
            if (!is_inside_grid(x,y)) break;
            Line line(x,y,x-1,y-1);
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            x2 = x; y2 = y;
            break;
        }
        if (x2 == -1) return {-1,-1,-1,-1,-1,-1,-1,-1};
    }

    // (tx,ty)を探す
    ll tx=x1+(x2-sx), ty=y1+(y2-sy);
    if (!is_inside_grid(tx,ty)) return {-1,-1,-1,-1,-1,-1,-1,-1};
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            x++; y++;
            Line line(x,y,x-1,y-1);
            if (line_set.count(line)) return {-1,-1,-1,-1,-1,-1,-1,-1};
            lines.push_back(line);
            if (grid[x][y] != 0) return {-1,-1,-1,-1,-1,-1,-1,-1};
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (line_set.count(line)) return {-1,-1,-1,-1,-1,-1,-1,-1};
            lines.push_back(line);
            if (grid[x][y] != 0) return {-1,-1,-1,-1,-1,-1,-1,-1};
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    return {tx, ty, x1, y1, sx, sy, x2, y2};
}

//     (x2,y2)
//     ／    ＼
// (tx,ty) (sx,sy)
//     ＼    ／
//     (x1,y1)
tuple<ll,ll,ll,ll,ll,ll,ll,ll> make_point_45_L(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1=-1, y1=-1;
    {
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--; y--;
            if (!is_inside_grid(x,y)) break;
            Line line(x,y,x+1,y+1);
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            x1 = x; y1 = y;
            break;
        }
        if (x1 == -1) return {-1,-1,-1,-1,-1,-1,-1,-1};
    }

    // (x2,y2)を探す
    ll x2=-1, y2=-1;
    {
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x--; y++;
            if (!is_inside_grid(x,y)) break;
            Line line(x,y,x+1,y-1);
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            x2 = x; y2 = y;
            break;
        }
        if (x2 == -1) return {-1,-1,-1,-1,-1,-1,-1,-1};
    }

    // (tx,ty)を探す
    ll tx=x2-(sx-x1), ty=y2-(sy-y1);
    if (!is_inside_grid(tx,ty)) return {-1,-1,-1,-1,-1,-1,-1,-1};
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            x--; y++;
            Line line(x,y,x+1,y-1);
            if (line_set.count(line)) return {-1,-1,-1,-1,-1,-1,-1,-1};
            lines.push_back(line);
            if (grid[x][y] != 0) return {-1,-1,-1,-1,-1,-1,-1,-1};
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (line_set.count(line)) return {-1,-1,-1,-1,-1,-1,-1,-1};
            lines.push_back(line);
            if (grid[x][y] != 0) return {-1,-1,-1,-1,-1,-1,-1,-1};
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    return {tx, ty, x1, y1, sx, sy, x2, y2};
}

//     (sx,sy)
//     ／    ＼
// (x1,y1) (x2,y2)
//     ＼    ／
//     (tx,ty)
tuple<ll,ll,ll,ll,ll,ll,ll,ll> make_point_45_D(ll sx, ll sy, ll max_len, vector<vector<ll>> &grid, set<Line> &line_set) {
    vector<Line> lines;

    // (x1,y1) を探す
    ll x1=-1, y1=-1;
    {
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            x--; y--;
            if (!is_inside_grid(x,y)) break;
            len++;
            Line line(x,y,x+1,y+1);
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            x1 = x; y1 = y;
            break;
        }
        if (x1 == -1) return {-1,-1,-1,-1,-1,-1,-1,-1};
    }

    // (x2,y2)を探す
    ll x2=-1, y2=-1;
    {
        ll len = 1;
        ll x = sx, y = sy;
        while(len <= max_len) {
            len++;
            x++; y--;
            if (!is_inside_grid(x,y)) break;
            Line line(x,y,x-1,y+1);
            if (line_set.count(line)) break;
            lines.push_back(line);
            if (grid[x][y] == 0) continue;
            x2 = x; y2 = y;
            break;
        }
        if (x2 == -1) return {-1,-1,-1,-1,-1,-1,-1,-1};
    }

    // (tx,ty)を探す
    ll tx=x2-(sx-x1), ty=y2-(sy-y1);
    if (!is_inside_grid(tx,ty)) return {-1,-1,-1,-1,-1,-1,-1,-1};
    {
        ll x=x1, y=y1;
        while(!(x==tx && y==ty)) {
            x++; y--;
            Line line(x,y,x-1,y+1);
            if (line_set.count(line)) return {-1,-1,-1,-1,-1,-1,-1,-1};
            lines.push_back(line);
            if (grid[x][y] != 0) return {-1,-1,-1,-1,-1,-1,-1,-1};
        }
    }
    {
        ll x=x2, y=y2;
        while(!(x==tx && y==ty)) {
            x--; y--;
            Line line(x,y,x+1,y+1);
            if (line_set.count(line)) return {-1,-1,-1,-1,-1,-1,-1,-1};
            lines.push_back(line);
            if (grid[x][y] != 0) return {-1,-1,-1,-1,-1,-1,-1,-1};
        }
    }

    // 線を引く
    for(auto line: lines) {
        line_set.insert(line);
    }

    grid[tx][ty] = 2;
    return {tx, ty, x1, y1, sx, sy, x2, y2};
}

vector<tuple<ll,ll,ll,ll,ll,ll,ll,ll>> make_rectangle_if_possible(ll max_len, vector<vector<ll>> &grid, set<Line> &line_set) {
    vector<tuple<ll,ll,ll,ll,ll,ll,ll,ll>> ans;

    for(ll sy=0; sy<N; sy++) {
        for(ll sx=0; sx<N; sx++) {
            if (grid[sx][sy] == 0) continue;
            tuple<ll,ll,ll,ll,ll,ll,ll,ll> res;

            res = make_point_LD(sx, sy, max_len, grid, line_set);
            {
                ll& flag = get<0>(res);
                if (flag != -1) {
                    ans.push_back(res);
                }
            }

            res = make_point_LU(sx, sy, max_len, grid, line_set);
            {
                ll& flag = get<0>(res);
                if (flag != -1) {
                    ans.push_back(res);
                }
            }

            res = make_point_RD(sx, sy, max_len, grid, line_set);
            {
                ll& flag = get<0>(res);
                if (flag != -1) {
                    ans.push_back(res);
                }
            }

            res = make_point_RU(sx, sy, max_len, grid, line_set);
            {
                ll& flag = get<0>(res);
                if (flag != -1) {
                    ans.push_back(res);
                }
            }

            res = make_point_45_U(sx, sy, max_len, grid, line_set);
            {
                ll& flag = get<0>(res);
                if (flag != -1) {
                    ans.push_back(res);
                }
            }

            res = make_point_45_L(sx, sy, max_len, grid, line_set);
            {
                ll& flag = get<0>(res);
                if (flag != -1) {
                    ans.push_back(res);
                }
            }

            res = make_point_45_D(sx, sy, max_len, grid, line_set);
            {
                ll& flag = get<0>(res);
                if (flag != -1) {
                    ans.push_back(res);
                }
            }

            res = make_point_45_R(sx, sy, max_len, grid, line_set);
            {
                ll& flag = get<0>(res);
                if (flag != -1) {
                    ans.push_back(res);
                }
            }
        }
    }

    return ans;
}

/**
 * @brief 初期解作る
 *
 * @param grid
 */
vector<tuple<ll,ll,ll,ll,ll,ll,ll,ll>> initial_solver(vector<vector<ll>> &grid, set<Line> &line_set) {
    vector<tuple<ll,ll,ll,ll,ll,ll,ll,ll>> ans;

    ll max_len = 1;
    while(1) {
        auto res = make_rectangle_if_possible(max_len, grid, line_set);
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

void solve() {
    cin >> N >> M;
    vector grid(N, vector<ll>(N, 0));  // 0:印のない格子点, 1:印のある格子点, 2: 追加した印のある格子点
    vector<pair<ll,ll>> XY(M);
    for(ll i=0; i<M; i++) {
        ll x, y; cin >> x >> y;
        XY.push_back({x,y});
        grid[x][y] = 1;
    }

    set<Line> line_set;  // ((x1,y1) (x2,y2)) を結ぶ線が存在する
    // 貪欲に初期解を作る
    vector ini_ans = initial_solver(grid, line_set);

    // 出力
    printf("%lld\n", (ll)ini_ans.size());
    for(ll i=0; i<(ll)ini_ans.size(); i++) {
        auto[x1, y1, x2, y2, x3, y3, x4, y4] = ini_ans[i];
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