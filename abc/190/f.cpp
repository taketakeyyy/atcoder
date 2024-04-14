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


/*** BIT実装例
・N個の変数 v[1], ..., v[N]
    - すべて0で初期化
・2種類のクエリ
    - v[a]に値wを加える
    - prefix[1,a]のところの区間和v[1]+v[2]+..+v[a]を求める
・クエリあたりO(logN)時間にしたい

bit[1]からbit[N]までを使用(便宜上bit[0]は使用しない)
bit[1] := v[1]
bit[2] := v[1]+v[2]
bit[3] := v[3]
bit[4] := v[1]+v[2]+v[3]+v[4]
bit[5] := v[5]
***/
template <typename T>
class BIT {
    private:
        /* 引数チェック */
        void _check_args_add(size_t a) {
            if (a <= 0 || this->N < a) {
                try {
                    throw "Error BIT.add(a, w): Arg 'a' MUST '1 <= a <= N'.";
                }
                catch (const char *str) {
                    cerr << str << endl;
                    terminate();
                }
            }
        }

        /* 引数チェック */
        void _check_args_sum(size_t a) {
            if (a <= 0 || this->N < a) {
                try {
                    throw "Error BIT.add(a, w): Arg 'a' MUST '1 <= a <= N'.";
                }
                catch (const char *str) {
                    cerr << str << endl;
                    terminate();
                }
            }
        }

    public:
        size_t N;  // 要素数
        vector<T> bit;  // bit配列

        BIT(size_t n) {
            this->N = n;
            this->bit.resize(n+1, 0);
        }

        /**
         * @brief v[a]番目に値wを加える
         * @details O(logN)
         */
        void add(size_t a, T w) {
            // エラー処理
            _check_args_add(a);

            size_t x = a;
            while (x <= this->N) {
                this->bit[x] += w;
                x += x&-x;
            }
        }

        /**
         * @brief vの区間[1,a]の和を求める
         * @details O(logN)
         */
        T sum(size_t a) {
            _check_args_sum(a);

            T ret = 0; size_t x = a;
            while (x > 0) {
                ret += this->bit[x];
                x -= x&-x;
            }
            return ret;
        }
};

void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // k=0のときの転倒数を数える
    ll ans = 0;
    BIT<ll> b(N);  // これまでの数字がどんな風になってるのかをメモる為のBIT
    for (int i = 0; i < N; i++) {
        ans += i - b.sum(A[i]+1); // BITの総和 - 自分より左側 ＝ 自分より右側
        b.add(A[i]+1, 1); // 自分の位置に1を足す
    }
    cout << ans << endl;

    // k=1以降は、しゃくとり法的に解く
    for(ll k=0; k<N-1; k++) {
        ll a = A[k];
        ans += (N-1)-a;
        ans -= a;
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}