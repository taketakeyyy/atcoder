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


void solve(){
    int N, K; cin >> N >> K;
    vector<ll> As(N);
    vector<ll> plus;
    vector<ll> minus;
    int minus_num = 0, plus_num = 0;
    for (int i=0; i<N; i++) {
        cin >> As[i];
        if (As[i]<0) {
            minus_num++;
            minus.push_back(As[i]);
        }
        else {
            plus_num++;
            plus.push_back(As[i]);
        }
    }

    bool ok = false;  // 正にできるか？
    if (plus_num > 0) {
        if (N==K) ok = (minus_num%2==0);
        else ok = true;
    }
    else {
        ok = (K%2==0);
    }

    mint ans = 1;
    if (!ok) {
        // 正にできない場合、絶対値が小さい順に取る
        sort(As.begin(), As.end(), [](int x, int y) {return abs(x) < abs(y);} );
        for (int i=0; i<K; i++) {
            ans *= As[i];
        }
    }
    else {
        // 正にできる場合、2個ずつとっていく（ただしKが奇数のときは、正からまず1個とる）
        sort(plus.rbegin(), plus.rend());
        sort(minus.begin(), minus.end());
        int pi = 0, mi = 0;
        int cost = 0;
        if (K%2==1 && plus.size()!=0) {
            ans *= plus[pi];
            pi++;
            cost ++;
        }

        vector<ll> dbl;  // 2個ずつの配列
        for (; pi+1<plus.size(); pi+=2) {
            dbl.push_back(plus[pi]*plus[pi+1]);
        }
        for (; mi+1<minus.size(); mi+=2) {
            dbl.push_back(minus[mi]*minus[mi+1]);
        }
        sort(dbl.rbegin(), dbl.rend());

        int i=0;
        while(cost!=K) {
            ans *= dbl[i];
            i++;
            cost += 2;
        }
    }
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}