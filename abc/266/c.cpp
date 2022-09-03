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

/* 分数 */
template<typename T>
struct frac {
    private:
        T a;  // 分子
        T b;  // 分母
    public:
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


ll cross(vector<ll> &a, vector<ll> &b) {
    ll g = a[0]*b[1] - a[1]*b[0];  // 外積
    return g;
}

// 外積で判定
void solve() {
    ll Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
    cin >> Ax >> Ay >> Bx >> By >> Cx >> Cy >> Dx >> Dy;

    vector<ll> a, b;
    // 角度A
    a.push_back(Bx-Ax);
    a.push_back(By-Ay);
    b.push_back(Dx-Ax);
    b.push_back(Dy-Ay);
    if (cross(a, b) <= 0) {
        cout << "No" << endl;
        return;
    }
    a.resize(0);
    b.resize(0);

    // 角度B
    a.push_back(Cx-Bx);
    a.push_back(Cy-By);
    b.push_back(Ax-Bx);
    b.push_back(Ay-By);
    if (cross(a, b) <= 0) {
        cout << "No" << endl;
        return;
    }
    a.resize(0);
    b.resize(0);

    // 角度C
    a.push_back(Dx-Cx);
    a.push_back(Dy-Cy);
    b.push_back(Bx-Cx);
    b.push_back(By-Cy);
    if (cross(a, b) <= 0) {
        cout << "No" << endl;
        return;
    }
    a.resize(0);
    b.resize(0);

    // 角度D
    a.push_back(Ax-Dx);
    a.push_back(Ay-Dy);
    b.push_back(Cx-Dx);
    b.push_back(Cy-Dy);
    if (cross(a, b) <= 0) {
        cout << "No" << endl;
        return;
    }
    a.resize(0);
    b.resize(0);

    cout << "Yes" << endl;
    return;
}


int main() {
    solve();
    return 0;
}