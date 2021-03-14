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

template<typename T>
T mod_pow(T a, T n, T m) {
    /** a^{n} mod m の計算を、繰り返し二乗法で求める
     *  計算量：O(log n)
     **/
    if (n==0) return 1;
    T res = mod_pow(a*a%m, n/2, m);
    if (n&1) res = res * a % m;
    return res;
}

template <typename T>
T combination_mod(T n, T r, T mod) {
    /*** nCrを O(min(n-r, r)) で高速に計算する ***/
    auto inv = [mod](T x) { return mod_pow<T>(x, mod-2, mod); };

    r = min(n-r, r);
    T bunsi=1, bunbo=1;
    for (T i=0; i<r; i++) {
        bunsi = bunsi*(n-i)%mod;
        bunbo = bunbo*(i+1)%mod;
    }
    return (bunsi*inv(bunbo))%mod;
}

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

void solve() {
    ll N; cin >> N;
    vector<ll> F(N);
    vector<bool> self_loop(N, false);  // 自己ループのやつ
    vector<ll> resti;
    ll group = 0;  // グループ数
    rep(i,N) {
        cin >> F[i];
        F[i]--;
        if (i==F[i]) {
            self_loop[i] = true;
            group++;
        }
        else {
            resti.push_back(i);
        }
    }

    vector<ll>used(N, -1);  // まだグラフを形成していないやつは-1、もう形成したやつは根の番号が入る
    for(int j=0; j<resti.size(); j++) {
        ll i = resti[j];

        if (used[i]!=-1) continue;
        ll now = i;
        used[now] = i;
        while(1) {
            ll nx = F[now];
            if (self_loop[nx]) {
                // 部分集合形成失敗
                break;
            }
            if (!(used[nx]==-1 || used[nx]==i)) {
                // 既に他の部分集合として使われているなら、部分集合形成失敗
                break;
            }
            if (used[nx]==i) {
                // 部分集合形成成功
                group++;
                break;
            }
            used[nx] = i;
            now = nx;
        }
    }

    // nC1 + nC2 + ... + nCn をしたい
    // nC0 + nC1 + nC2 + ... + nCn = 2^nを使うと高速に求まる
    ll ans = 1;
    for (ll n=0; n<group; n++) {
        ans *= 2;
        ans %= MOD;
    }
    ans--;  // nC0を引く
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}