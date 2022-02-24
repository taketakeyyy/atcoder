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


bool comp (pair<double, double> a, pair<double, double> b) {
    return (a.second <= b.second);
}

/* 分数 */
struct frac {
    private:
        ll a;  // 分子
        ll b;  // 分母
    public:
        frac(ll a=0, ll b=0) {
            this->a = a; this->b = b;
            if (this->b == 0) {
                this->a = 1;
                return;
            }
            ll g = gcd(this->a, this->b);
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
};

void solve() {
    // 射影でなくて偏角で考える
    // 偏角を計算したらdouble型になるので、傾きを分数で保持する
    // その後、区間スケジューリング問題になる
    ll N; cin >> N;
    vector<pair<frac,frac>> data(N);  // [終端, 始端]
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        frac d1 = frac(y-1, x);
        frac d2 = frac(y, x-1);
        data[i] = {d2, d1};
    }
    sort(data.begin(), data.end());

    // 区間スケジューリング問題
    ll ans = 0;
    frac t(0, 1);
    for(ll i=0; i<N; i++) {
        frac r, l;
        tie(r, l) = data[i];
        if (t <= l) {
            ans++;
            t = r;
        }
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}