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

vector<map<int, int>> class_mp;  // class_mp[i][j] := 生徒iが知っている、クラスjの人数

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
                for (auto p: class_mp[gx]) {
                    // cout << "p: " << p.first << " " << p.second << endl;
                    class_mp[gy][p.first] += p.second;
                }
            }
            else {
                this->parents[gy] = gx;
                this->sizes[gx] += this->sizes[gy];
                for (auto p: class_mp[gy]) {
                    // cout << "p: " << p.first << " " << p.second << endl;
                    class_mp[gx][p.first] += p.second;
                }
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
    int N, Q;
    cin >> N >> Q;
    vector<int> C(N+1);
    class_mp.resize(N+1);
    for (int i=1; i<N+1; i++) {
        cin >> C[i];
        class_mp[i][C[i]] = 1;
    }

    UnionFindVerSize uf(N+1);

    for (int i=0; i<Q; i++) {
        int q, a, b;
        cin >> q >> a >> b;
        if (q==1) {
            // 生徒aと生徒bが合流
            uf.unite(a, b);
            // cout << "find_root: " << uf.find_root(a) << " " << uf.find_root(b) << endl;
            // cout << "size: " << uf.get_size(uf.find_root(a)) << " " << uf.get_size(uf.find_root(b)) << endl;
        }
        else {
            // 生徒aと合流している生徒のうち、クラスbに所属している生徒の数を求める
            int root = uf.find_root(a);
            cout << class_mp[root][b] << endl;
        }
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}