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

/***
 *
 * 2次元座標のアフィン変換
 *
 * Usage:
 *   // Affine変換用の行列を作成
 *   Affine<double> A = Affine<double>();
 *
 *   // 最初はx=1, y=2
 *   double x=1.0, y=2.0;  // 変換前の座標
 *   double nx, ny;        // 変換後の座標
 *   cout << x << " " << y << endl;  // 1 2
 *
 *   // 時計回りに90度回転
 *   A.rotate_deg(-90);
 *   tie(nx, ny) = A.calc(x, y);
 *   cout << nx << " " << ny << endl;  // 2 -1
 *
 *   // x=3で対称な位置に移動
 *   A.reflectX(3);
 *   tie(nx, ny) = A.calc(x, y);
 *   cout << nx << " " << ny << endl;  // 4 -1
 *
 *   // 反時計回りに90度回転
 *   A.rotate_deg(90);
 *   tie(nx, ny) = A.calc(x, y);
 *   cout << nx << " " << ny << endl;  // 1 4
 *
 *   // y=2で対称な位置に移動
 *   A.reflectY(2);
 *   tie(nx, ny) = A.calc(x, y);
 *   cout << nx << " " << ny << endl;  // 1 0
 *
 **/
template <typename T>
class Affine {
    private:
        vector<vector<T>> A;
    public:
        Affine() {
            A.resize(3);
            for (int i=0; i<3; i++) A[i].resize(3);

            this->A[0][0]=1; this->A[1][1]=1; this->A[2][2]=1;  // 単位行列
        }

        void zoom(T sx, T sy) {
            /***拡大縮小
             * Args:
             *   sx(T): X軸方向の拡大率
             *   sy(T): Y軸方向の拡大率
             ***/
            vector<vector<T>> B(3, vector<T>(3, 0));
            vector<vector<T>> C(3, vector<T>(3, 0));
            B[0][0]=sx; B[1][1]=sy; B[2][2]=1;
            for (int i=0; i<3; i++) {
                for(int j=0; j<3; j++) {
                    for (int k=0; k<3; k++) {
                        C[i][j] += B[i][k]*this->A[k][j];
                    }
                }
            }
            this->A = C;
        }

        void translate(T tx, T ty) {
            /*** 平行移動
             * Args:
             *  tx(T): X軸方向にtx移動
             *  ty(T): Y軸方向にty移動
             ***/
            vector<vector<T>> B(3, vector<T>(3, 0));
            vector<vector<T>> C(3, vector<T>(3, 0));
            B[0][0]=1; B[1][1]=1; B[2][2]=1;
            B[0][2]=tx; B[1][2]=ty;
            for (int i=0; i<3; i++) {
                for(int j=0; j<3; j++) {
                    for (int k=0; k<3; k++) {
                        C[i][j] += B[i][k]*this->A[k][j];
                    }
                }
            }
            this->A = C;
        }

        void rotate_rad(T rad) {
            /*** 回転
             * Args:
             *  rad: 角度（ラジアン）
             *
             * Notes:
             *  反時計回りに回転する
             ***/
            vector<vector<T>> B(3, vector<T>(3, 0));
            vector<vector<T>> C(3, vector<T>(3, 0));
            B[0][0]=cos(rad); B[0][1]=-sin(rad);
            B[1][0]=sin(rad); B[1][1]=cos(rad);
            B[2][2]=1;
            for (int i=0; i<3; i++) {
                for(int j=0; j<3; j++) {
                    for (int k=0; k<3; k++) {
                        C[i][j] += B[i][k]*this->A[k][j];
                    }
                }
            }
            this->A = C;
        }

        void rotate_deg(T deg) {
            /*** 回転
             * Args:
             *  deg(T): 角度（度数法）
             *
             * Notes:
             *  反時計回りに回転する
             ***/
            static const double PI = 3.141592653589793;
            this->rotate_rad(deg*PI/180);
        }

        void reflectX(T p) {
            /*** x=pで対称移動
             * Args:
             *  p(T): x=pで対称移動
             ***/
            vector<vector<T>> B(3, vector<T>(3, 0));
            vector<vector<T>> C(3, vector<T>(3, 0));
            B[0][0]=-1; B[0][2]=2*p;
            B[1][1]=1;
            B[2][2]=1;
            for (int i=0; i<3; i++) {
                for(int j=0; j<3; j++) {
                    for (int k=0; k<3; k++) {
                        C[i][j] += B[i][k]*this->A[k][j];
                    }
                }
            }
            this->A = C;
        }

        void reflectY(T p) {
            /*** y=pで対称移動
             * Args:
             *  p(T): y=pで対称移動
             ***/
            vector<vector<T>> B(3, vector<T>(3, 0));
            vector<vector<T>> C(3, vector<T>(3, 0));
            B[0][0]=1;
            B[1][1]=-1; B[1][2]=2*p;
            B[2][2]=1;
            for (int i=0; i<3; i++) {
                for(int j=0; j<3; j++) {
                    for (int k=0; k<3; k++) {
                        C[i][j] += B[i][k]*this->A[k][j];
                    }
                }
            }
            this->A = C;
        }

        pair<T, T> calc(T x, T y) {
            /*** 座標計算する
             * Args:
             *  x(T): 変換前のx座標
             *  y(T): 変換前のy座標
             *
             * Returns (pair):
             *  nx(T): 変換後のx座標
             *  ny(T): 変換後のy座標
             ***/
            T nx = this->A[0][0]*x + this->A[0][1]*y + this->A[0][2];
            T ny = this->A[1][0]*x + this->A[1][1]*y + this->A[1][2];
            return make_pair(nx, ny);
        }
};

void solve() {
    ll a, b, d; cin >> a >> b >> d;
    Affine<double> A = Affine<double>();

    A.rotate_deg(d);
    double na, nb;
    tie(na, nb) = A.calc(a, b);
    printf("%.6f %.6f\n",na, nb);
}


int main() {
    solve();
    return 0;
}