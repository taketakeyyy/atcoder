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

struct frac {
    private:
        ll a;  // 分子
        ll b;  // 分母
    public:
        frac(ll _a=0, ll _b=1) {
            a = _a; b = _b;
            // 分母が0の場合
            if (b == 0) {
                a = 1;
                return;
            }
            // 分母がマイナスのときは、分母のマイナスを分子に与える
            if (b < 0) {
                a = -a; b = -b;
            }
            // 約分しとく
            ll g = gcd(a, b);
            a /= g; b /= g;
        }

        bool operator==(const frac& other) const {
            return (a==other.a) && (b==other.b);
        }
        bool operator!=(const frac& other) const {
            return !((a==other.a) && (b==other.b));
        }
};

void solve() {
    ll N; cin >> N;
    vector<pair<ll,ll>> XY(N);
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        XY[i] = {x, y};
    }

    ll ans = 0;
    for(ll i=0; i<N; i++) {
        ll x1, y1;
        tie(x1, y1) = XY[i];
        for(ll j=i+1; j<N; j++) {
            ll x2, y2;
            tie(x2, y2) = XY[j];

            frac f1(y2-y1, x2-x1);
            for(ll k=j+1; k<N; k++) {
                ll x3, y3;
                tie(x3, y3) = XY[k];

                frac f2(y3-y1, x3-x1);

                if (f1 != f2) {
                    ans++;
                }
            }
        }
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}