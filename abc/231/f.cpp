#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
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


/*** BIT実装例
・N個の変数 v[1], ..., v[N]
    - すべて0で初期化
・2種類のクエリ
    - v[a]に値wを加える
    - prefix[1,a]のところの区間和v[1]+v[2]+..+v[a]を求める
・クエリあたりO(logN)時間にしたい

bit[1]からbit[N]までを使用(便宜上bit[0]は使用しない)
bit[1] := v[1]
bit[2] := v[1]+v[2]
bit[3] := v[3]
bit[4] := v[1]+v[2]+v[3]+v[4]
bit[5] := v[5]
***/
class BIT {
    public:
        ll N;  // 要素数
        vector<ll> bit;  // bit配列

        BIT(ll n) {
            this->N = n;
            this->bit.resize(n+1, 0);
        }

        void add(ll a, ll w) {
            /***v[a]番目に値wを加える
            O(logN)
            ***/
            // エラー処理
            if (a <= 0 || this->N < a) {
                try {
                    throw "Error BIT.add(a, w): Arg 'a' MUST '1 <= a <= N'.";
                }
                catch (const char *str) {
                    cout << str << endl;
                    terminate();
                }
            }

            ll x = a;
            while (x <= this->N) {
                this->bit[x] += w;
                x += x&-x;
            }
        }

        ll sum(ll a) {
            /***vの区間[1,a]の和を求める
            O(logN)
            ***/
            // エラー処理
            if (a <= 0 || this->N < a) {
                try {
                    throw "Error BIT.sum(a): Arg 'a' MUST '1 <= a <= N'.";
                }
                catch (const char *str) {
                    cout << str << endl;
                    terminate();
                }
            }

            ll ret = 0; ll x = a;
            while (x > 0) {
                ret += this->bit[x];
                x -= x&-x;
            }
            return ret;
        }
};


template<typename T>
T combination(T n, T r) {
    /***nCrは、O(min(n-r, r))で実装する

    Example:
        100C98 = 100!/(98!*2!)
               = 100*99/2*1
        となることから、計算量は減らせる

    Notes:
        分子と分母がかなり大きな値になった場合、計算は遅くなるので注意
        求める値がmodをとった値でいい場合、後述のフェルマーの小定理を使った方法が速い。
    ***/
    if (n < r) return 0;

    r = min(n-r, r);
    T bunsi=1, bunbo=1;
    for (T i=0; i<r; i++) {
        bunsi = bunsi*(n-i);
        bunbo = bunbo*(i+1);
    }
    return bunsi/bunbo;
}


bool compare(pair<ll,ll>&p1, pair<ll,ll>&p2) {
    // Aを昇順に並べ替え
    // ただし、Aが同じ値なら、Bの値が大きい順にする
    if (p1.first < p2.first) {
        return true;
    }
    if (p1.first == p2.first) {
        if (p1.second > p2.second) {
            return true;
        }
        return false;
    }
    return false;
}
void compress(vector<ll>&vec) {
    // 座標圧縮
    ll N = (ll)vec.size();
    map<ll,ll> mp;
    vector<ll> A = vec;
    sort(A.begin(), A.end());
    for(ll i=0; i<N; i++) {
        mp[A[i]] = i+1;
    }
    for(ll i=0; i<N; i++) {
        vec[i] = mp[vec[i]];
    }
}
void solve() {
    ll N; cin >> N;
    vector<ll> A(N), B(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i];
    }
    for(ll i=0; i<N; i++) {
        cin >> B[i];
    }
    // A,Bの値が大きい可能性があるので、転倒数を数えるために座標圧縮する必要がある
    compress(A);
    compress(B);

    vector<pair<ll,ll>> AB(N);
    for(ll i=0; i<N; i++) {
        AB[i] = {A[i], B[i]};
    }
    sort(AB.begin(), AB.end(), compare);

    // Bの転倒数を数える（ただしB[i]==B[j]も数える）
    ll tentou = 0;
    BIT bit(N);
    for(ll i=0; i<N; i++) {
        if (AB[i].second-1 >= 1) {
            tentou += i - bit.sum(AB[i].second-1);
        }
        else {
            tentou += i;
        }
        bit.add(AB[i].second, 1);
    }
    // (A[i], B[i])==(A[j], B[j])を数える。この場合、（青木, 高橋）だけでなく、（高橋, 青木）でもOK
    map<pair<ll,ll>,ll> mp;
    for(ll i=0; i<N; i++) {
        mp[AB[i]]++;
    }
    ll same = 0;
    for(auto[p, v]: mp) {
        if (v>=2) {
            same += combination<ll>(v, 2);
        }
    }

    // 出力
    cout << N+tentou+same << endl;
}


int main() {
    solve();
    return 0;
}