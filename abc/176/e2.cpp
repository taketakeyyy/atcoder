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
    int H, W, M; cin >> H >> W >> M;
    // vector<vector<int>> grid(H, vector<int>(W, 0));  HxWの配列は大きすぎる可能性がある（REの原因）
    vector<int>BombH (H, 0);
    vector<int>BombW (W, 0);
    set<pair<int, int>> target_set;
    int max_H=0, max_W=0;
    for (int i=0; i<M; i++) {
        int h, w; cin >> h >> w; h--; w--;
        target_set.insert(make_pair(h, w));
        BombH[h]++; BombW[w]++;
        max_H = max(max_H, BombH[h]);
        max_W = max(max_W, BombW[w]);
    }

    vector<int>candsH, candsW;
    for (int i=0; i<H; i++) {
        if (BombH[i] == max_H) {
            candsH.push_back(i);
        }
    }
    for (int i=0; i<W; i++) {
        if (BombW[i] == max_W) {
            candsW.push_back(i);
        }
    }

    bool is_found = false;
    int ans = 0;
    for(int i=0; i<candsH.size(); i++) {
        for(int j=0; j<candsW.size(); j++) {
            int h = candsH[i];
            int w = candsW[j];
            int total = BombH[h] + BombW[w];
            if (target_set.count(make_pair(h,w))) {
                ans = max(ans, total-1);
            }
            else {
                ans = max(ans, total);
                is_found = true;
                break;
            }
        }
        if (is_found) break;
    }

    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}