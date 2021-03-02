#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 998244353
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

struct UnionFindVerSize {
    private:
        vector<int> sizes;   // グループのサイズ
        vector<int> parents;  // 親の番号を格納する。自分が親の場合は自分の番号になり、それがそのグループの番号になる

    public:
        UnionFindVerSize(int N=0): sizes(N,1), parents(N) {
            for (int i=0; i<N; i++) {
                parents[i] = i;
            }
        }

        int find_root(int x) {
            /* ノード番号xの木の根（xがどのグループか）を求める */
            if (this->parents[x] == x) return x;
            this->parents[x] = this->find_root(this->parents[x]);  // 縮約
            return this->parents[x];
        }

        void unite(int x, int y) {
            /* ノード番号xとyが属する木を併合する（グループの併合） */
            int gx = this->find_root(x); int gy = this->find_root(y);
            if (gx == gy) return;

            // 深い方が浅い方を併合する（木の偏りが減るので）
            if (this->sizes[gx] < this->sizes[gy]) {
                this->parents[gx] = gy;
                this->sizes[gy] += this->sizes[gx];
            }
            else {
                this->parents[gy] = gx;
                this->sizes[gx] += this->sizes[gy];
            }
        }

        int get_size(int x) {
            /* ノード番号xが属するグループの深さを返す */
            return this->sizes[this->find_root(x)];
        }

        bool is_same_group(int x, int y) {
            /* ノード番号xとyが同じ集合に属するか否か */
            return this->find_root(x) == this->find_root(y);
        }

        int calc_group_num() {
            /* グループ数を計算して返す */
            int ans = 0;
            for (int i=0; i<this->parents.size(); i++) {
                if (i == this->find_root(i)) ans++;
            }
            return ans;
        }

        void print_parents() {
            /* デバッグ用parentsの中身を出力する */
            for (int i=0; i<this->parents.size(); i++) {
                cout << this->parents[i] << endl;
            }
        }

        void print_sizes() {
            /* デバッグ用sizesの中身を出力する */
            for (int i=0; i<this->sizes.size(); i++) {
                cout << this->sizes[i] << endl;
            }
        }
};


void solve(){
    // 行スワップという操作の、行番号に注目する。
    // 行スワップとはつまり、行番号を入れ替えることである。
    // 行番号の数列(0,1,2)を(2,1,0)などにするイメージ。
    // この数列を何通り作れるか？という問題。
    // 行と列2つの数列を何通り作れるかそれぞれ独立に求め、行の場合の数と列の場合の数を掛け算すればよい。
    // まとめると、行スワップと列スワップはそれぞれ独立しているので、
    // 答え = (行スワップで作れる場合の数) x (列スワップで作れる場合の数)
    // (1) まず、行スワップを考える
    // 各行を頂点として、行スワップが可能な頂点同士を辺で結ぶグラフを描く。
    // 連結成分が異なる部分グラフは、独立して考えられる
    // 行スワップとは、「辺で繋がれた頂点の番号を入れ替える」に等しい。
    // 入れ替え操作をして作れるグラフは何通りか？という問題
    // ある連結成分がn個の頂点を持つとき、頂点の入れ替えして作れるグラフは n! 通り
    // (2) 次に、列スワップを考える
    // 行スワップと独立にして同様に考えればOK
    ll N, K; cin >> N >> K;
    vector<vector<ll>> As(N, vector<ll>(N));
    for (int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin >> As[i][j];
        }
    }

    if (N==1) {
        cout << 1 << endl;
        return;
    }

    // 行スワップについて考える
    UnionFindVerSize uf(N);
    for(int x=0; x<N; x++) {
        for(int y=x+1; y<N; y++) {
            bool swappable = true;
            for(int i=0; i<N; i++) {
                if (As[x][i]+As[y][i]<=K) continue;
                swappable = false;
                break;
            }
            if (swappable) {
                uf.unite(x, y);
            }
        }
    }

    mint ans = mint(1);

    for (int x=0; x<N; x++) {
        if (uf.find_root(x) != x) continue;
        for(ll i=1; i<=(ll)uf.get_size(x); i++) {
            ans *= mint(i);
        }
    }

    // 列スワップについて考える
    uf = UnionFindVerSize(N);
    for(int x=0; x<N; x++) {
        for(int y=x+1; y<N; y++) {
            bool swappable = true;
            for(int i=0; i<N; i++) {
                if (As[i][x]+As[i][y]<=K) continue;
                swappable = false;
                break;
            }
            if (swappable) {
                uf.unite(x,y);
            }
        }
    }
    for (int x=0; x<N; x++) {
        if (uf.find_root(x) != x) continue;
        for(ll i=1; i<=(ll)uf.get_size(x); i++) {
            ans *= mint(i);
        }
    }

    cout << ans << endl;
}


void solve2(){
    // WA
    // 連結成分のchainに問題あり。
    // UnionFindでいうグループの併合をしていないのが原因
    ll N, K; cin >> N >> K;
    vector<vector<ll>> As(N, vector<ll>(N));
    for (int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin >> As[i][j];
        }
    }

    if (N==1) {
        cout << 1 << endl;
        return;
    }

    // 行スワップについて考える
    vector<set<ll>> chain;  // 連結成分の集合
    for(int x=0; x<N; x++) {
        for(int y=x+1; y<N; y++) {
            bool swappable = true;
            for(int i=0; i<N; i++) {
                if (As[x][i]+As[y][i]<=K) continue;
                swappable = false;
                break;
            }
            if (swappable) {
                bool found = false;
                for (int k=0; k<(int)chain.size(); k++) {
                    if (chain[k].count(x) || chain[k].count(y)) {
                        chain[k].insert(x); chain[k].insert(y);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    set<ll> s;
                    s.insert(x); s.insert(y);
                    chain.push_back(s);
                }
            }
        }
    }

    mint ans = mint(1);
    for (auto s: chain) {
        for(ll i=1; i<=(ll)s.size(); i++) {
            ans *= mint(i);
        }
    }

    // 列スワップについて考える
    chain = vector<set<ll>>();
    for(int x=0; x<N; x++) {
        for(int y=x+1; y<N; y++) {
            bool swappable = true;
            for(int i=0; i<N; i++) {
                if (As[i][x]+As[i][y]<=K) continue;
                swappable = false;
                break;
            }
            if (swappable) {
                bool found = false;
                for (int k=0; k<(int)chain.size(); k++) {
                    if (chain[k].count(x) || chain[k].count(y)) {
                        chain[k].insert(x); chain[k].insert(y);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    set<ll> s;
                    s.insert(x); s.insert(y);
                    chain.push_back(s);
                }
            }
        }
    }
    for (auto s: chain) {
        for(ll i=1; i<=(ll)s.size(); i++) {
            ans *= mint(i);
        }
    }

    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}