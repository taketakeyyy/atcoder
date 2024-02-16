#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };

namespace MatrixLib {
    class print_format_error: public std::exception {
        virtual const char* what() const noexcept { return "Error: print() method cannot print these values because of unsupported!"; }
    };
    class matrix_product_error: public std::exception {
        virtual const char* what() const noexcept { return "Error: Impossible to calculate matrix product!"; }
    };
    class determinant_error: public std::exception {
        virtual const char* what() const noexcept { return "Error: Impossible to calculate determinant!"; }
    };
    class inversion_error: public std::exception {
        virtual const char* what() const noexcept { return "Error: Impossible to calculate inversion!"; }
    };
    class no_square_matrix_error: public std::exception {
        virtual const char* what() const noexcept { return "Error: Impossible to calculate because of no-square matrix."; }
    };


    /*** 二次元行列のライブラリMatrix ***/
    template <typename T>
    class Matrix {
        private:
            vector<vector<T>> A;

            T __cofactor(const vector<vector<T>>& coA) const {
                /* 各余因子の計算を再帰的にする */
                if (coA.size() == 1) return coA[0][0];
                if (coA.size() == 2) {
                    return coA[0][0]*coA[1][1]-coA[0][1]*coA[1][0];
                }

                T res = 0;
                for (size_t col2=0; col2<coA.size(); col2++) {
                    vector<vector<T>> cocoA(coA.size()-1);
                    for (size_t row=1; row<coA.size(); row++) {
                        for (size_t col=0; col<coA.size(); col++) {
                            if (col2==col) continue;
                            cocoA[row-1].emplace_back(coA[row][col]);
                        }
                    }
                    if (!(col2&1)) res += coA[0][col2] * __cofactor(cocoA);
                    else res -= coA[0][col2] * __cofactor(cocoA);
                }
                return res;
            }
        public:
            size_t row;
            size_t col;
            Matrix(size_t row=1, size_t col=1) {
                this->row = row;
                this->col = col;
                this->A.resize(row);
                for(size_t i=0; i<row; i++) this->A[i].resize(col);
            }

            vector<T>& operator[](const size_t i) {
                return this->A[i];
            }

            bool operator==(Matrix other) {
                if (!(this->row==other.row and this->col==other.col)) return false;

                for(size_t i=0; i<this->row; i++) {
                    for(size_t j=0; j<this->col; j++) {
                        if (this->A[i][j] == other[i][j]) continue;
                        return false;
                    }
                }
                return true;
            }

            Matrix& operator+=(Matrix other) {
                for(size_t i=0; i<this->row; i++) {
                    for(size_t j=0; j<this->col; j++) {
                        this->A[i][j] += other[i][j];
                    }
                }
                return *this;
            }
            Matrix operator+(const Matrix other) const {
                return Matrix(*this) += other;
            }
            Matrix& operator+=(const double a) {
                /* 各要素にaを足す */
                for (size_t i=0; i<this->row; i++) {
                    for (size_t j=0; j<this->col; j++) {
                        this->A[i][j] += a;
                    }
                }
                return *this;
            }
            Matrix operator+(const double a) const {
                return Matrix(*this) += a;
            }

            Matrix& operator-=(Matrix other) {
                for(size_t i=0; i<this->row; i++) {
                    for(size_t j=0; j<this->col; j++) {
                        this->A[i][j] -= other[i][j];
                    }
                }
                return *this;
            }
            Matrix operator-(const Matrix other) const {
                return Matrix(*this) -= other;
            }
            Matrix operator-() const {
                Matrix res(this->row, this->col);
                for (size_t i=0; i<this->row; i++) {
                    for (size_t j=0; j<this->col; j++) {
                        res[i][j] = -this->A[i][j];
                    }
                }
                return res;
            }
            Matrix& operator-=(const double a) {
                /* 各要素にaを引く */
                for (size_t i=0; i<this->row; i++) {
                    for (size_t j=0; j<this->col; j++) {
                        this->A[i][j] -= a;
                    }
                }
                return *this;
            }
            Matrix operator-(const double a) const {
                return Matrix(*this) -= a;
            }

            Matrix& operator*=(Matrix other) {
                /* NxN行列 x NxN行列 の積を求める */
                if (!(this->row==this->col && other.row==other.col && this->row==other.row)) throw matrix_product_error();

                vector<vector<T>> res(this->row, vector<T>(this->col, 0));
                for(size_t i=0; i<other.row; i++) {
                    for (size_t j=0; j<this->col; j++) {
                        for (size_t k=0; k<this->col; k++) {
                            res[i][j] += this->A[i][k]*other[k][j];
                        }
                    }
                }
                this->A = res;
                return *this;
            }
            Matrix operator*(Matrix other) const {
                /* ixk行列 * kxj行列 の積を求める */
                if (this->col!=other.row) throw matrix_product_error();

                Matrix<T> res(this->row, other.col);
                for (size_t i=0; i<this->row; i++) {
                    for (size_t j=0; j<other.col; j++) {
                        for (size_t k=0; k<this->col; k++) {
                            res[i][j] += this->A[i][k]*other[k][j];
                        }
                    }
                }
                return res;
            }

            Matrix& operator*=(const double a) {
                /* 各要素にaをかける */
                for (size_t i=0; i<this->row; i++) {
                    for (size_t j=0; j<this->col; j++) {
                        this->A[i][j] *= a;
                    }
                }
                return *this;
            }
            Matrix operator*(const double a) const {
                return Matrix(*this) *= a;
            }

            void print() {
                /* 行列の状態を表示する */
                string format;
                if (typeid(T)==typeid(int)) format = "%*d"s;
                else if (typeid(T)==typeid(unsigned int) || typeid(T)==typeid(unsigned short)) format = "%*u"s;
                else if (typeid(T)==typeid(long)) format = "%*ld"s;
                else if (typeid(T)==typeid(unsigned long)) format = "%*lu"s;
                else if (typeid(T)==typeid(long long)) format = "%*lld"s;
                else if (typeid(T)==typeid(unsigned long long)) format = "%*llu"s;
                else if (typeid(T)==typeid(short)) format = "%*f"s;
                else if (typeid(T)==typeid(double)) format = "%*lf"s;
                else if (typeid(T)==typeid(long double)) format = "%*LF"s;
                else throw print_format_error();

                int len = 0;
                for (size_t i=0; i<this->row; i++) {
                    for (size_t j=0; j<this->col; j++) {
                        string str = to_string(this->A[i][j]);
                        len = max(len, (int)str.size());
                    }
                }

                printf("[[");
                for (size_t i=0; i<this->row; i++) {
                    for (size_t j=0; j<this->col; j++) {
                        printf(format.c_str(), len, this->A[i][j]);
                        if (j!=this->col-1) printf(", ");
                        else printf("]");
                    }
                    if (i!=this->row-1) printf(",\n [");
                    else printf("]\n");
                }
            }

            T det() const {
                /* 行列式を計算して返す */
                if (this->row!=this->col) throw determinant_error();

                return this->__cofactor(this->A);
            }

            Matrix dot(const Matrix B) const {
                /* ドット積（内積）計算をする */
                return Matrix(*this) * B;
            }

            Matrix inv() const {
                /* 逆行列を返す（掃き出し法） */
                if (!(this->row==this->col)) throw inversion_error();

                size_t N = this->row;
                Matrix<T> A = *this;
                Matrix<T> invA(N, N);
                for (size_t i=0; i<N; i++) {
                    for (size_t j=0; j<N; j++) {
                        invA[i][j] = (i==j) ? 1 : 0;
                    }
                }

                for (size_t i=0; i<N; i++) {
                    T buf = 1/A[i][i];
                    for (size_t j=0; j<N; j++) {
                        A[i][j] *= buf;
                        invA[i][j] *= buf;
                    }

                    for (size_t j=0; j<N; j++) {
                        if (i!=j) {
                            buf = A[j][i];
                            for (size_t k=0; k<N; k++) {
                                A[j][k] -= A[i][k]*buf;
                                invA[j][k] -= invA[i][k]*buf;
                            }
                        }
                    }
                }

                return invA;
            }

            /**
             * @brief 自身の行列累乗を計算して返す
             * 繰り返し二乗法を使って、O(log n)で計算する
             *
             * @param n n乗する
             * @return Matrix
             */
            Matrix pow(int n) const {
                if (this->row != this->col) { throw no_square_matrix_error(); }
                Matrix res = Matrix<T>(this->row, this->col);

                for(size_t i=0; i<this->row; i++) {
                    res[i][i] = 1;
                }

                Matrix a = (*this);
                while (n > 0) {
                    if (n&1) res = a.dot(res);
                    a = a.dot(a);
                    n /= 2;
                }
                return res;
            }
    };
}

void solve() {
    ll N; cin >> N;
    MatrixLib::Matrix<ll> A(N,N);  // 要素がll型のNxN行列の作成
    MatrixLib::Matrix<ll> B(N,N);  // 要素がll型のNxN行列の作成
    MatrixLib::Matrix<ll> C(N,N);  // 要素がll型のNxN行列の作成
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            cin >> A[i][j];
        }
    }
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            cin >> B[i][j];
        }
    }
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            cin >> C[i][j];
        }
    }

    // 何回かwitnessを使って計算して、多数決をとる
    ll T = 1;
    ll vote_yes = 0;
    ll vote_no = 0;
    for(ll t=0; t<T; t++) { // 何回か試す
        MatrixLib::Matrix<ll> x(N,1); // 列ベクトルxを適当に作る
        for(ll i=0; i<N; i++) {
            ll r = rand();
            x[i][0] = 1;
        }
        auto ABx = A*(B*x);
        auto Cx = C*x;

        if (ABx == Cx) vote_yes++;
        else vote_no++;
    }
    if (vote_yes > vote_no) cout << "YES" << endl;
    else cout << "NO" << endl;
}


int main() {
    solve();
    return 0;
}