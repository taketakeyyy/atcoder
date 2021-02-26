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
const long long INF = LONG_LONG_MAX - 1001001001;
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
    // 赤玉がある(2個以上玉が入っている)箱から適当に玉を選んで他の箱に入れるとき、白い玉を赤く塗って移動させたものと考えればよい
    // 赤玉はどんどん増えていく形になるが、それが「赤いボールが入っている可能性」となる
    ll N, M; cin >> N >> M;
    vector<pair<ll,bool>> box(N, make_pair(1,false));  // (玉の数,赤玉が入っている可能性があるか)
    box[0] = make_pair(1,true);
    for (int i=0; i<M; i++) {
        ll x, y; cin >> x >> y;
        x--; y--;

        if (box[x].first == 0) continue;
        box[y].first++;
        box[y].second |= box[x].second;
        if (box[x].first == 1) {
            box[x].first = 0;
            box[x].second = false;
        }
        else {
            box[x].first -= 1;
        }
    }

    // 最終的にbox[i].second==trueの数を数えればいい
    ll ans = 0;
    for (int i=0; i<N; i++) {
        ans += (box[i].second) ? 1 : 0;
    }
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}