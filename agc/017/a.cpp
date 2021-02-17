#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = unsigned long long;
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


void solve(){
    ll N, P; cin >> N >> P;
    vector<ll> As(N);
    ll odd=0, even=0;  // 奇数の数、偶数の数
    rep(i,N) {
        cin >> As[i];
        if (As[i]&1) odd++;
        else even++;
    }

    // 天才解法：
    // * 適当に奇数の袋を選ぶ。
    // * それ以外の袋の選び方は2^{N-1}通り。
    // * 実は、偶数/奇数になるように食べる場合の数は、この2^{N-1}通り。
    // * なぜなら、適当に選んだ奇数の袋を「食べる」or「たべない」で偶数or奇数に必ず調整可能だから。
    // * 奇数の袋が一つもないパターンがコーナーケース
    if (P==0) {
        // 偶数個食べる場合の数
        if (odd==0) {
            // すべて偶数の袋なので、全通り
            unsigned long long  ans = pow(2, N);
            printf("%llu\n", ans);
            return;
        }
        // 適当に奇数の袋を選べば、調整可能
        unsigned long long  ans = pow(2, N-1);
        printf("%llu\n", ans);
        return;
    }
    else {
        // 奇数個食べる場合の数
        if (odd==0) {
            // すべて偶数の袋なので、0通り
            cout << 0 << endl;
            return;
        }
        // 適当に奇数の袋を選べば、調整可能
        unsigned long long  ans = pow(2, N-1);
        printf("%llu\n", ans);
        return;
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}