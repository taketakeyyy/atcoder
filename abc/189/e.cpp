#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
const int INF = 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
struct mint {
    ll x; // typedef long long ll;
    mint(ll x=0):x((x%MOD+MOD)%MOD){}
    mint operator-() const { return mint(-x);}
    mint& operator+=(const mint a) {
        if ((x += a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += MOD-a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator*=(const mint a) { (x *= a.x) %= MOD; return *this;}
    mint operator+(const mint a) const { return mint(*this) += a;}
    mint operator-(const mint a) const { return mint(*this) -= a;}
    mint operator*(const mint a) const { return mint(*this) *= a;}
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }

    // for prime MOD
    mint inv() const { return pow(MOD-2);}
    mint& operator/=(const mint a) { return *this *= a.inv();}
    mint operator/(const mint a) const { return mint(*this) /= a;}
};
istream& operator>>(istream& is, mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}


class Affine {
    private:
        vector<vector<double>> A;
    public:
        Affine() {
            A.resize(3);
            for (int i=0; i<3; i++) A[i].resize(3);

            this->A[0][0]=1.0; this->A[1][1]=1.0; this->A[2][2]=1.0;  // 単位行列
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


void solve(){
    string line; getline(cin, line);
    int N = stoi(line);
    vector<pair<int, int>> XYs;
    for (int i=0; i<N; i++) {
        getline(cin, line);
        int pos = line.find(" ");
        int X, Y;
        X = stoi(line.substr(0, pos));
        Y = stoi(line.substr(pos));
        XYs.emplace_back(make_pair(X, Y));
    }

    getline(cin, line);
    int M = stoi(line);
    vector<Affine> r_A;  // 行列の累積積みたいなやつ
    r_A.emplace_back(Affine());
    for(int i=0; i<M; i++) {
        string op; getline(cin, op);
        if (op == "2") {
            // 反時計回りに90回転
            Affine A = r_A.back();
            A.rotate_deg(90);
            r_A.emplace_back(A);
        }
        else if (op == "1") {
            // 時計回りに90回転
            Affine A = r_A.back();
            A.rotate_deg(-90);
            r_A.emplace_back(A);
        }
        else {
            int op1 = op[0] - '0';
            int p = stoi(op.substr(2));
            if (op1 == 3) {
                // x = pで対称移動
                Affine A = r_A.back();
                A.reflectX(p);
                r_A.emplace_back(A);
            }
            else if (op1 == 4) {
                // y = pで対称移動
                Affine A = r_A.back();
                A.reflectY(p);
                r_A.emplace_back(A);
            }
        }
    }

    int Q; cin >> Q;
    for (int i=0; i<Q; i++) {
        int A, B; cin >> A >> B;
        B--;
        int x, y;
        tie(x,y) = XYs[B];

        double nx, ny;
        tie(nx, ny) = r_A[A].calc(x, y);

        printf("%.0lf %.0lf\n", nx, ny);
    }

}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}