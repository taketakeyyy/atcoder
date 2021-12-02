#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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


void solve__() {
    // TLEする
    ll N, Q; cin >> N >> Q;
    map<pair<ll,ll>,ll> Map; // Map[(i,i+1)] := A[i]+A[i+1]の値

    for (ll q=0; q<Q; q++) {
        ll t, x, y, v; cin >> t >> x >> y >> v;
        x--; y--;

        if (t==0) {
            Map[make_pair(x,y)] = v;
        }
        else {
            vector<ll> A(N, -1);
            A[x] = v;

            // A[y]を求めたい
            deque<tuple<ll,ll,ll>> deq;
            deq.push_back({x, x+1, x});
            if (x-1 >= 0) deq.push_back({x-1, x, x});
            while(!deq.empty()) {
                auto tpl = deq.front(); deq.pop_front();
                auto [l, r, xx] = tpl;
                if (!Map.count({l, r})) continue;

                if (l == xx && A[r]==-1) {
                    A[r] = Map[{l,r}] - A[l];
                    deq.push_back({r, r+1, r});
                    if (r-1 >= 0) deq.push_back({r-1, r, r});
                }
                if (r == xx && A[l]==-1) {
                    A[l] = Map[{l,r}] - A[r];
                    deq.push_back({l, l+1, l});
                    if (l-1 >= 0) deq.push_back({l-1, l, l});
                }

                if (A[y] != -1) {
                    break;
                }
            }

            if (A[y] != -1) {
                cout << A[y] << endl;
            }
            else {
                cout << "Ambiguous" << endl;
            }
        }
    }
}

template <typename T>
struct UnionFindVerSize {
    private:
        vector<T> sizes;   // グループのサイズ
        vector<T> parents;  // 親の番号を格納する。自分が親の場合は自分の番号になり、それがそのグループの番号になる

    public:
        UnionFindVerSize(T N=0): sizes(N,1), parents(N) {
            for (T i=0; i<N; i++) {
                parents[i] = i;
            }
        }

        T find_root(T x) {
            /* ノード番号xの木の根（xがどのグループか）を求める */
            if (this->parents[x] == x) return x;
            this->parents[x] = this->find_root(this->parents[x]);  // 縮約
            return this->parents[x];
        }

        void unite(T x, T y) {
            /* ノード番号xとyが属する木を併合する（グループの併合） */
            T gx = this->find_root(x); T gy = this->find_root(y);
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

        T get_size(T x) {
            /* ノード番号xが属するグループの深さを返す */
            return this->sizes[this->find_root(x)];
        }

        bool is_same_group(T x, T y) {
            /* ノード番号xとyが同じ集合に属するか否か */
            return this->find_root(x) == this->find_root(y);
        }

        T calc_group_num() {
            /* グループ数を計算して返す */
            T ans = 0;
            for (T i=0; i<(T)this->parents.size(); i++) {
                if (i == this->find_root(i)) ans++;
            }
            return ans;
        }

        void print_parents() {
            /* デバッグ用parentsの中身を出力する */
            for (T i=0; i<this->parents.size(); i++) {
                cout << this->parents[i] << endl;
            }
        }

        void print_sizes() {
            /* デバッグ用sizesの中身を出力する */
            for (T i=0; i<this->sizes.size(); i++) {
                cout << this->sizes[i] << endl;
            }
        }
};


void solve() {
    // クエリ先読みで解く
    ll N, Q; cin >> N >> Q;
    map<pair<ll,ll>,ll> Map; // Map[(i,i+1)] := A[i]+A[i+1]の値

    // 連結しているかをUnionFindで調べる
    UnionFindVerSize uf = UnionFindVerSize<ll>(N);

    vector<bool> ambiguous(Q, false);  // 1: ambiguous, 0: ambiguousにならない
    vector<ll> T(Q), X(Q), Y(Q), V(Q);
    // クエリ先読み
    for (ll q=0; q<Q; q++) {
        cin >> T[q] >> X[q] >> Y[q] >> V[q];
        X[q]--; Y[q]--;

        if (T[q] == 0) {
            uf.unite(X[q], Y[q]);
            Map[{X[q], Y[q]}] = V[q];
        }
        else {
            if (!uf.is_same_group(X[q], Y[q])) {  // 連結していないなら、確実にAmbiguous
            ambiguous[q] = true;
                continue;
            }

            // 連結しているなら、答えは確実に求まる
            // 毎回ここで計算していたらTLEしそうなので、クエリ先読みしてあとでまとめて答える
            ambiguous[q] = false;
        }
    }

    // 先にAを求めておく
    vector<ll> A(N, INF);
    // for (ll i=0; i<N; i++) {
    ll i=0;
    while(i<N) {
        if (Map.count({i,i+1})) {
            A[i] = 0;  // 0のときの答えを求めておく
            while (1) {
                if (!Map.count({i,i+1})) break;
                A[i+1] = Map[{i,i+1}] - A[i];
                i++;
            }
        }
        else {
            i++;
        }
    }

    // クエリ処理
    for (ll q=0; q<Q; q++) {
        if (T[q]==0) continue;

        if (ambiguous[q]) {
            cout << "Ambiguous" << endl;
            continue;
        }

        // 先に求めたAとの差で本当の答えが求まる
        ll x = X[q]; ll y = Y[q]; ll v = V[q];
        ll diff = v-A[x];  // 差
        if ((y-x)%2==0) {
            cout << A[y] + diff << endl;
        }
        else {
            cout << A[y] - diff << endl;
        }
    }
}

int main() {
    solve();
    return 0;
}