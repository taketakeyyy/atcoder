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

template <typename T>
class SegmentTree_LazyRMQ {
    /* Lazy Renge Minimum Query */

    private:
        const T INF = numeric_limits<T>::max();
        ll _lst2node(ll i) {
            /* 元の配列lstのi番目を、セグ木のノード番号に変換する */
            return i+this->N-1;
        }

        ll _node2lst(ll i) {
            /* セグ木のノードのi番目を、元の配列 lst の添字に変換する */
            return i - (this->N-1);
        }

        void _eval(ll k) {
            /* 遅延評価関数 */
            if (this->lazy[k] == this->INF) return;
            if (k < this->N-1) {
                this->lazy[2*k+1] = this->lazy[k];
                this->lazy[2*k+2] = this->lazy[k];
            }
            // 自身を更新
            this->nodes[k] = this->lazy[k];
            this->lazy[k] = this->INF;
        }

        void _update(ll a, ll b, T x, ll k, ll l, ll r) {
            /* 区間 [a, b) に対して、担当区間 [l, r) のノード k が応答する */
            this->_eval(k);
            if (a<=l && r<=b) {
                // 担当区間がすっぽり含まれる場合
                this->lazy[k] = x;
                this->_eval(k);
            }
            else if (a<r && l<b){
                // 一部区間が被る場合
                this->_update(a, b, x, 2*k+1, l, (l+r)/2);  // 左の子
                this->_update(a, b, x, 2*k+2, (l+r)/2, r);  // 右の子
                this->nodes[k] = min(this->nodes[2*k+1], this->nodes[2*k+2]);
            }
        }

        T _query(ll a, ll b, ll k, ll l, ll r) {
            /* 区間 [a,b) のクエリに対して、担当区間 [l,r) のノード k が応答する */
            this->_eval(k);
            if (r<=a || b<=l) {
                // 区間がかぶらない場合
                return this->INF;
            }
            if (a<=l && r<=b) {
                // 担当区間がすっぽり含まれる場合
                return this->nodes[k];
            }
            // それ以外
            T ret1 = this->_query(a, b, 2*k+1, l, (l+r)/2);  // 左の子に聞く
            T ret2 = this->_query(a, b, 2*k+2, (l+r)/2, r);  // 右の子に聞く
            return min(ret1, ret2);
        }

        ll _find_rightest(ll a, ll b, T x, ll k, ll l, ll r) {
            /* 区間 [a, b) に対して、担当区間 [l, r) のノード k が応答する */
            this->_eval(k);
            if (this->nodes[k]>x || r <= a || b <= l) {
                // 自分の値がxより大きい or [a,b)が[l,r)の範囲外の場合
                return a-1;
            }
            else if (k >= this->N-1) {
                // 自分が葉の場合
                return this->_node2lst(k);
            }
            else {
                ll ret = this->_find_rightest(a, b, x, 2*k+2, (l+r)/2, r);
                if (ret != a-1) {
                    // 右の部分木を見て a-1 以外なら終了
                    return ret;
                }
                else {
                    // 左の部分木を見る
                    return this->_find_rightest(a, b, x, 2*k+1, l, (l+r)/2);
                }
            }
        }

        ll _find_leftest(ll a, ll b, T x, ll k, ll l, ll r) {
            /* 区間 [a, b) に対して、担当区間 [l, r) のノード k が応答する */
            this->_eval(k);
            if (this->nodes[k]>x || r <= a || b <= l) {
                // 自分の値がxより大きい or [a,b)が[l,r)の範囲外の場合
                return b;
            }
            else if (k >= this->N-1) {
                // 自分が葉の場合
                return this->_node2lst(k);
            }
            else {
                ll ret = this->_find_leftest(a, b, x, 2*k+1, l, (l+r)/2);
                if (ret != b) {
                    // 左の部分木を見て b 以外なら終了
                    return ret;
                }
                else {
                    // 右の部分木を見る
                    return this->_find_leftest(a, b, x, 2*k+2, (l+r)/2, r);
                }
            }
        }

    public:
        ll N;  // セグ木の葉の数
        ll list_size;  // 元の配列(lst)のサイズ
        vector<T> nodes, lazy;  // セグ木のノードと、遅延評価用のノード
        SegmentTree_LazyRMQ(ll n) {
            /***
             * Args:
             *  n(ll): 元の配列の要素数
             ***/
            this->list_size = n;

            ll x = 1;
            while (n > x) x *= 2;
            this->N = x;

            this->nodes.assign(this->N*2-1, this->INF);
            this->lazy.assign(this->N*2-1, this->INF);
        }

        void set(ll i, T x) {
            /* セグ木の葉に値をセットする（セットするだけ。セグ木を構築するときはbuild()を呼ぶ） */
            ll ni = this->_lst2node(i);
            this->nodes[ni] = x;
        }

        void build() {
            /* セグ木を構築する */
            for (ll k=this->N-2; k>=0; k--) {
                this->nodes[k] = min(this->nodes[2*k+1], this->nodes[2*k+2]);
            }
        }

        void update(ll a, ll b, T x) {
            /* 区間 [a, b) の値を x に変更し、セグ木全体を更新する */
            this->_update(a, b, x, 0, 0, this->N);
        }

        T query(ll a, ll b) {
            /* 区間 [a,b) のクエリに応答する */
            return this->_query(a, b, 0, 0, this->N);
        }

        ll find_rightest(ll a, ll b, T x) {
            /* 区間 [a, b) で x 以下の要素を持つ最右位置を返す
             * 見つからなかった場合、-1を返す
             */
            return _find_rightest(a, b, x, 0, 0, this->N);
        }

        ll find_leftest(ll a, ll b, T x) {
            /* 区間 [a, b) で x 以下の要素を持つ最左位置を返す
             * 見つからなかった場合、list_size以上の番号を返す
             */
            return _find_leftest(a, b, x, 0, 0, this->N);
        }
};


void solve() {
    const ll N = 1048576;

    /* LazyRMQの作成と構築 */
    SegmentTree_LazyRMQ lazyrmq = SegmentTree_LazyRMQ<ll>(N);
    for(ll i=0; i<N; i++) {
        lazyrmq.set(i, -1);
    }
    lazyrmq.build();

    ll Q; cin >> Q;
    for(ll q=0; q<Q; q++) {
        ll t, x; cin >> t >> x;
        ll h = x%N;
        if (t==1) {
            ll idx = lazyrmq.find_leftest(h, N, -1);
            if (idx==N) {
                idx = lazyrmq.find_leftest(0, h, -1);
            }
            lazyrmq.update(idx, idx+1, x);
        }
        else {
            cout << lazyrmq.query(h, h+1) << endl;
        }
    }
}


int main() {
    solve();
    return 0;
}