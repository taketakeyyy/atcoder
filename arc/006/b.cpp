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
    string line;
    getline(cin, line);
    ll N, L;
    ll pos = (ll)line.find(" ");
    N = (ll)stoi(line.substr(0, pos));
    L = (ll)stoi(line.substr(pos+1));

    vector<string>amida(L+1);
    rep(i,L+1) {
        getline(cin, line);
        amida[i] = line;
    }

    // あみだを下から逆にたどっていけば良い
    ll w;
    for(int i=0; i<2*N-1; i+=2) {
        if (amida[L][i]=='o') {
            w = i;
            break;
        }
    }

    ll h = L-1;
    while(1) {
        if (h==-1) {
            cout << (w/2)+1 << endl;
            return;
        }

        if (w-1>=0 && amida[h][w-1]=='-') {
            // 左に行く
            w -= 2;
            h--;
            continue;
        }
        else if (w+1<2*N-1 && amida[h][w+1]=='-') {
            // 右に行く
            w += 2;
            h--;
            continue;
        }
        else {
            // そのまま上に行く
            h--;
            continue;
        }
    }

}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}