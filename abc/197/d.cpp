#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

class Affine {
    private:
        vector<vector<double>> A;
    public:
        Affine() {
            A.resize(3);
            for (int i=0; i<3; i++) A[i].resize(3);

            this->A[0][0]=1.0; this->A[1][1]=1.0; this->A[2][2]=1.0;  // 単位行列
        }

        void zoom(double sx, double sy) {
            /***拡大縮小
             * Args:
             *   sx(double): X軸方向の拡大率
             *   sy(double): Y軸方向の拡大率
             ***/
            vector<vector<double>> B(3, vector<double>(3, 0.0));
            vector<vector<double>> C(3, vector<double>(3, 0.0));
            B[0][0]=sx; B[1][1]=sy; B[2][2]=1.0;
            for (int i=0; i<3; i++) {
                for(int j=0; j<3; j++) {
                    for (int k=0; k<3; k++) {
                        C[i][j] += B[i][k]*this->A[k][j];
                    }
                }
            }
            this->A = C;
        }

        void translate(double tx, double ty) {
            /*** 平行移動
             * Args:
             *  tx(double): X軸方向にtx移動
             *  ty(double): Y軸方向にty移動
             ***/
            vector<vector<double>> B(3, vector<double>(3, 0.0));
            vector<vector<double>> C(3, vector<double>(3, 0.0));
            B[0][0]=1.0; B[1][1]=1.0; B[2][2]=1.0;
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

        void rotate_rad(double rad) {
            /*** 回転
             * Args:
             *  rad: 角度（ラジアン）
             *
             * Notes:
             *  反時計回りに回転する
             ***/
            vector<vector<double>> B(3, vector<double>(3, 0.0));
            vector<vector<double>> C(3, vector<double>(3, 0.0));
            B[0][0]=cos(rad); B[0][1]=-sin(rad);
            B[1][0]=sin(rad); B[1][1]=cos(rad);
            B[2][2]=1.0;
            for (int i=0; i<3; i++) {
                for(int j=0; j<3; j++) {
                    for (int k=0; k<3; k++) {
                        C[i][j] += B[i][k]*this->A[k][j];
                    }
                }
            }
            this->A = C;
        }

        void rotate_deg(double deg) {
            /*** 回転
             * Args:
             *  deg(double): 角度（度数法）
             *
             * Notes:
             *  反時計回りに回転する
             ***/
            static const double PI = 3.141592653589793;
            this->rotate_rad(deg*PI/180);
        }

        void reflectX(double p) {
            /*** x=pで対称移動
             * Args:
             *  p(double): x=pで対称移動
             ***/
            vector<vector<double>> B(3, vector<double>(3, 0.0));
            vector<vector<double>> C(3, vector<double>(3, 0.0));
            B[0][0]=-1.0; B[0][2]=2*p;
            B[1][1]=1.0;
            B[2][2]=1.0;
            for (int i=0; i<3; i++) {
                for(int j=0; j<3; j++) {
                    for (int k=0; k<3; k++) {
                        C[i][j] += B[i][k]*this->A[k][j];
                    }
                }
            }
            this->A = C;
        }

        void reflectY(double p) {
            /*** y=pで対称移動
             * Args:
             *  p(double): y=pで対称移動
             ***/
            vector<vector<double>> B(3, vector<double>(3, 0.0));
            vector<vector<double>> C(3, vector<double>(3, 0.0));
            B[0][0]=1.0;
            B[1][1]=-1.0; B[1][2]=2*p;
            B[2][2]=1.0;
            for (int i=0; i<3; i++) {
                for(int j=0; j<3; j++) {
                    for (int k=0; k<3; k++) {
                        C[i][j] += B[i][k]*this->A[k][j];
                    }
                }
            }
            this->A = C;
        }

        pair<double, double> calc(double x, double y) {
            /*** 座標計算する
             * Args:
             *  x(double): 変換前のx座標
             *  y(double): 変換前のy座標
             *
             * Returns (pair):
             *  nx(double): 変換後のx座標
             *  ny(double): 変換後のy座標
             ***/
            double nx = this->A[0][0]*x + this->A[0][1]*y + this->A[0][2];
            double ny = this->A[1][0]*x + this->A[1][1]*y + this->A[1][2];
            return make_pair(nx, ny);
        }
};

void solve() {
    ll N; cin >> N;
    double x0, y0; cin >> x0 >> y0;
    double xh, yh; cin >> xh >> yh;
    // 中点は求まる。中点は正N角形の外接円の中心点なので、その中心点をもとに、(x0,y0)から角度Θ回転させればよい。Θ=360/N
    // 回転操作はアフィン変換をつかえばいいじゃん
    double xm = (x0+xh)/2;
    double ym = (y0+yh)/2;
    // 原点座標で考えたいので、中心点が原点に来るように全体を平行移動させる
    double nx, ny;
    Affine A = Affine();
    A.translate(-xm, -ym);
    tie(nx,ny) = A.calc(x0,y0);
    // 原点を中心に考えて、360/N回転させる
    A = Affine();
    A.rotate_deg((double)360/N);
    tie(nx,ny) = A.calc(nx,ny);
    // 平行移動した分を元に戻す
    A = Affine();
    A.translate(xm, ym);
    tie(nx,ny) = A.calc(nx,ny);
    printf("%.10lf %.10lf\n",nx, ny);
}


int main() {
    solve();
    return 0;
}