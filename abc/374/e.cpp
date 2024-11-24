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
    ll N, X; cin >> N >> X;
    vector<ll> A(N+1), P(N+1), B(N+1), Q(N+1);
    for(ll i=1; i<=N; i++) {
        cin >> A[i] >> P[i] >> B[i] >> Q[i];
    }

    // 製造能力CAPを達成できるかどうか
    auto judge = [&](ll CAP) {
        ll totalMoney = 0;
        for(ll i=1; i<=N; i++) {
            if (totalMoney > X) return false;
            // 工程iでは、1円あたりの製造能力(WPY)が大きい機械をできるだけ買ったほうがよい（とは限らないが）
            frac<ll> AWPY(A[i],P[i]);
            frac<ll> BWPY(B[i],Q[i]);
            ll a = A[i], b = B[i], p = P[i], q = Q[i];
            if (AWPY < BWPY) {
                swap(a,b);
                swap(p,q);
            }

            // aをできるだけ多く買いつつも、bも買ったほうが良い場合もあるので、ある程度探索（どの程度探索すればええねん）
            ll limit = 0;
            const ll LIMIT = 1e5+10;
            ll minMoney = INF;
            for(ll ai=intceil(CAP,a); ai>=0; ai--) {
                limit++;
                if (limit == LIMIT) break;
                ll money = ai*p + max(0LL, intceil(CAP-ai*a, b))*q;
                chmin(minMoney, money);
            }
            totalMoney += minMoney;
        }
        return (totalMoney <= X);
    };

    // 製造能力midを達成できるか二分探索
    ll l = 0;
    ll r = 2e9+10;
    while(r-l > 1) {
        ll mid = (l+r)/2;
        if (judge(mid)) l = mid;
        else r = mid;
    }
    if (judge(r)) cout << r << endl;
    else cout << l << endl;
}


int main() {
    solve();
    return 0;
}