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


/**
 * @brief 3次元点
 * @example
 * // 点A(1,2,0)を作成
 * Point3D<ll> A(1,2,0);
 */
template<typename T>
struct Point3D {
    T x, y, z;

    bool operator<(const Point3D<T> &other) const {
        if (this->x < other.x) return true;
        if (this->x == other.x) {
            if (this->y < other.y) return true;
            if (this->y == other.y) {
                return this->z < other.z;
            }
        }
        return false;
    }
    bool operator>(const Point3D<T>& other) const {
        return other < *this;
    }
    bool operator==(const Point3D<T> &other) const {
        return (this->x==other.x) and (this->y==other.y) and (this->z==other.z);
    }
    bool operator<=(const Point3D<T>& other) const {
        return !(*this > other);
    }
    bool operator>=(const Point3D<T>& other) const {
        return !(*this < other);
    }
};
/**
 * @brief 3次元ベクトル
 * @example
 * // ベクトルv(1,2,0)を作成
 * Vector3D<ll> v(1,2,0);
 *
 * // 点A,BからベクトルABを作成
 * Point3D<ll> A(0,0,0);
 * Point3D<ll> B(1,0,0);
 * Vector3D<ll> AB(A,B);
 *
 * // ベクトルvとベクトルABの外積を求める
 * Vector3D<ll> cp = v.cross(AB); // 外積
 *
 */
template<typename T>
class Vector3D {
public:
    T x, y, z;

    Vector3D(T _x, T _y, T _z): x(_x), y(_y), z(_z) {}
    Vector3D(const Point3D<T> &p1, const Point3D<T> &p2): x(p2.x-p1.x), y(p2.y-p1.y), z(p2.z-p1.z) {}

    /**
     * @brief ベクトルの大きさ（L2ノルム）を返す
     *
     * @return double
     */
    double magnitude() const {
        return sqrt(this->magnitude_pow2());
    }

    /**
     * @brief ベクトルの大きさ（L2ノルム）の2乗を返す
     *
     * @return T
     */
    T magnitude_pow2() const {
        return x*x + y*y + z*z;
    }

    /**
     * @brief 内積を計算する
     *
     * @param other
     * @return T
     */
    T inner(const Vector3D &other) const {
        return this->x*other.x + this->y*other.y + this->z*other.z;
    }

    /**
     * @brief 外積を計算する
     *
     * @param other
     * @return Vector3D
     */
    Vector3D cross(const Vector3D &other) const {
        return Vector3D (
            this->y*other.z - this->z*other.y,
            this->z*other.x - this->x*other.z,
            this->x*other.y - this->y*other.x
        );
    }

    bool operator<(const Vector3D &other) const {
        if (this->x < other.x) return true;
        if (this->x == other.x) {
            if (this->y < other.y) return true;
            if (this->y == other.y) {
                return this->z < other.z;
            }
        }
        return false;
    }
    bool operator>(const Vector3D &other) const {
        return other<(*this);
    }
    bool operator==(const Vector3D &other) const {
        return (this->x==other.x) and (this->y==other.y) and (this->z==other.z);
    }
    bool operator<=(const Vector3D &other) const {
        return !(*this > other);
    }
    bool operator>=(const Vector3D &other) const {
        return !(*this < other);
    }
};

void solve2() {
    ll Ax, Ay; cin >> Ax >> Ay;
    ll Bx, By; cin >> Bx >> By;
    ll Cx, Cy; cin >> Cx >> Cy;
    ll Dx, Dy; cin >> Dx >> Dy;

    // 点を作成
    Point3D<ll> A(Ax,Ay,0);
    Point3D<ll> B(Bx,By,0);
    Point3D<ll> C(Cx,Cy,0);
    Point3D<ll> D(Dx,Dy,0);

    // ベクトルABとACの外積が、z軸上向きか調べる
    auto is_z_plus = [&](Point3D<ll> &A, Point3D<ll> &B, Point3D<ll> &C) -> bool {
        Vector3D<ll> AB(A,B);
        Vector3D<ll> AC(A,C);
        auto cp = AB.cross(AC);
        return cp.z > 0; // 内角180度未満なら凸なので、>=じゃない
    };

    // 答え
    bool ans = true;
    ans &= is_z_plus(A,B,C);
    ans &= is_z_plus(B,C,D);
    ans &= is_z_plus(C,D,A);
    ans &= is_z_plus(D,A,B);
    if (ans) cout << "Yes" << endl;
    else cout << "No" << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}