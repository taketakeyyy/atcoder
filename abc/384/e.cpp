#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// 初項a, 末項l, 項数n のときの等差数列の和
ll tousa1(const ll &a, const ll &l, const ll &n) { return ((a+l)*n)/2; }
// 初項a, 公差d, 項数n のときの等差数列の和
ll tousa2(const ll &a, const ll &d, const ll &n) { return ((2*a+(n-1)*d)*n)/2; }

/* 分数 */
template<typename T>
struct frac {
    private:
    public:
        T a;  // 分子
        T b;  // 分母
        frac(T a=0, T b=1) {
            this->a = a; this->b = b;
            // 分母が0のときは、無限大扱いにしたい
            if (this->b == 0) {
                this->a = 1;
                return;
            }
            // マイナスは分子につける
            if (b < 0) { this->a=-this->a; this->b=-this->b; }
            // 約分しておく
            T g = gcd<T>(this->a, this->b);
            this->a /= g;
            this->b /= g;
        }
        bool operator<(const frac &other) const {
            return this->a*other.b < other.a*this->b;
        }
        bool operator<=(const frac &other) const {
            return this->a*other.b <= other.a*this->b;
        }
        bool operator>(const frac &other) const {
            return this->a*other.b > other.a*this->b;
        }
        bool operator>=(const frac &other) const {
            return this->a*other.b >= other.a*this->b;
        }
        bool operator==(const frac &other) const {
            return (this->a == other.a) && (this->b == other.b);
        }
        frac operator*(const frac &other) const {
            T na = this->a*other.a;
            T nb = this->b*other.b;
            return frac(na, nb);
        }
        frac operator/(const frac &other) const {
            T na = this->a*other.b;
            T nb = this->b*other.a;
            return frac(na, nb);
        }
        frac operator+(const frac &other) const {
            T l = lcm(this->b, other.b);
            T na1 = this->a*(l/this->b);
            T na2 = other.a*(l/other.b);
            T na = na1 + na2;
            T nb = l;
            return frac(na, nb);
        }
        frac operator-(const frac &other) const {
            T l = lcm(b, other.b);
            T na1 = this->a*(l/this->b);
            T na2 = other.a*(l/other.b);
            T na = na1 - na2;
            T nb = l;
            return frac(na, nb);
        }
        void print() const {
            cout << this->a << "/" << this->b << endl;
        }
};


void solve() {
    ll H, W, X; cin >> H >> W >> X;
    ll P, Q; cin >> P >> Q;
    P--; Q--;
    vector grid(H, vector(W, 0LL));
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            cin >> grid[h][w];
        }
    }

    // 座標(h,w)はグリッドの内側に収まっているか？
    auto is_inside = [&](const ll &h, const ll &w) -> bool {
        return h>=0 and h<H and w>=0 and w<W;
    };

    priority_queue<tuple<ll,ll,ll>, vector<tuple<ll,ll,ll>>, greater<tuple<ll,ll,ll>>> pq;  // 小さい順を維持する優先度付きキュー
    vector visited(H, vector(W, false));
    visited[P][Q] = true;
    ll taka = grid[P][Q]; // 高橋の強さ
    for(ll vi=0; vi<4; vi++) {
        ll nh = P+vy[vi];
        ll nw = Q+vx[vi];
        if (is_inside(nh, nw) == false) continue;
        if (visited[nh][nw]) continue;
        visited[nh][nw] = true;
        pq.push({grid[nh][nw], nh, nw});
    }
    while(!pq.empty()) {
        auto[power, h, w] = pq.top(); pq.pop();

        // 終了条件
        if (power >= intceil(taka, X)) break;

        // 次の探索
        taka += power;
        for(ll vi=0; vi<4; vi++) {
            ll nh = h + vy[vi];
            ll nw = w + vx[vi];
            if (is_inside(nh,nw) == false) continue;
            if (visited[nh][nw]) continue;
            visited[nh][nw] = true;
            pq.emplace(grid[nh][nw], nh, nw);
        }
    }

    cout << taka << endl;
}


int main() {
    solve();
    return 0;
}