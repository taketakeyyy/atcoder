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
    vector<string>S;
    ll N;
    while(1) {
        string s;
        cin >> s;
        try {
            N = stol(s);
            break;
        }
        catch (...){
            ;
        }
        S.push_back(s);
    }

    // NGワードを読み込んで、フィルタリングしていく
    vector<bool> filtered(S.size(), false);  // フィルタリングしたかどうか
    rep(i, N) {
        string ng;
        cin >> ng;

        rep(j, S.size()) {
            if (filtered[j]) continue;
            if (S[j].size()!=ng.size()) continue;

            bool flag = true;
            rep(k, S[j].size()) {
                if ((k <= ng.size()-1) && (S[j][k]==ng[k] || ng[k]=='*')) {
                    continue;
                }
                flag = false;
                break;
            }

            if (flag) {
                filtered[j] = true;
            }
        }
    }

    // 出力
    rep(i, S.size()) {
        if (filtered[i]) {
            for(int j=0; j<S[i].size(); j++) {
                cout << "*";
            }
        }
        else {
            cout << S[i];
        }

        if (i!=S.size()-1) {
            cout << " ";
        }
    }
    cout << endl;

}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}