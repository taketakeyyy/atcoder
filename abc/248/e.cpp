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
        ll a; // 分子
        ll b; // 分母
    public:
        frac(ll _a=0, ll _b=1) {
            a = _a; b = _b;
            // 分母が0のとき、無限大扱い
            if (b == 0) {
                a = 1;
                return;
            }
            // マイナスは分子につける
            if (b < 0) { a = -a; b = -b; }
            // 約分しておく
            ll g = gcd(a, b);
            a /= g;
            b /= g;
        }
        bool operator<(const frac &other) const {
            return a*other.b < b*other.a;
        }
        bool operator<=(const frac &other) const {
            return a*other.b <= b*other.a;
        }
        bool operator==(const frac &other) const {
            return (a==other.a) && (b==other.b);
        }
        frac operator*(const frac &other) const {
            ll a1 = a*other.a;
            ll b1 = b*other.b;
            return frac(a1, b1);
        }
        frac operator-(const frac &other) {
            ll l = lcm(b, other.b);
            ll na1 = a*(l/b);
            ll na2 = other.a*(l/other.b);
            ll na = na1 - na2;
            ll nb = l;
            return frac(na, nb);
        }
};

void solve() {
    ll N, K; cin >> N >> K;

    if (K==1) {
        cout << "Infinity" << endl;
        return;
    }

    vector<pair<ll,ll>> coords(N);
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        coords[i] = {x,y};
    }

    // 傾きと切片を管理する
    map<pair<frac,frac>,set<pair<ll,ll>>> mp1;  // y=ax+d の直線を通る点 {傾き, 切片}
    map<ll,set<pair<ll,ll>>> mp2;  // x=x1 の直線を通る点
    for(ll i=0; i<N; i++) {
        ll x1, y1;
        tie(x1, y1) = coords[i];
        for(ll j=i+1; j<N; j++) {
            ll x2, y2;
            tie(x2, y2) = coords[j];

            if (x2 != x1) {
                frac a(y2-y1, x2-x1);  // 傾き
                frac d = a;  // 切片
                d = d * frac(x1, 1);
                d = frac(y1, 1) - d;
                mp1[{a,d}].insert({x1, y1});
                mp1[{a,d}].insert({x2, y2});
            }
            else {
                mp2[x1].insert({x1, y1});
                mp2[x1].insert({x2, y2});
            }
        }
    }

    // K以上の点を持つ直線を数える
    ll ans = 0;
    for(auto[key, val]: mp1) {
        if (val.size() >= K) ans++;
    }
    for(auto[key, val]: mp2) {
        if (val.size() >= K) ans++;
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}