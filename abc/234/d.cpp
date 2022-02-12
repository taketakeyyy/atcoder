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
class SegmentTree_RMQ {
    /* Renge Minimum Query */

    private:
        T _lst2node(T i) {
            /* 元の配列 lst[i] は、セグ木の i+(葉の数)-1 番目のノード */
            return i+this->n-1;
        }

        T _find(T a, T b, T k, T l, T r) {
            /* 区間 [a,b) のクエリに対して、担当区間 [l,r) のノード k が応答する */
            if (r<=a || b<=l) {
                // 区間がかぶらない場合
                return this->max_num;
            }
            if (a<=l && r<=b) {
                // 担当区間がすっぽり含まれる場合
                return this->nodes[k];
            }
            // それ以外
            T ret1 = this->_find(a, b, 2*k+1, l, (l+r)/2);  // 左の子に聞く
            T ret2 = this->_find(a, b, 2*k+2, (l+r)/2, r);  // 右の子に聞く
            return min(ret1, ret2);
        }

    public:
        T max_num;  // セグ木のノードの最大値
        T n;  // セグ木の葉の数
        vector<T> nodes;  // セグ木のノード
        SegmentTree_RMQ(vector<T> lst, T max_num) {
            /***
             * Args:
             *  lst(vector<T>) 元の配列
             *  max_num(T): セグ木の各ノードの初期値
             ***/
            this->max_num = max_num;
            T i = 1; T total = 1;
            while (1) {
                if (lst.size() <= i) break;
                i *= 2;
                total += i;
            }
            this->n = i;
            this->nodes.resize(total, this->max_num);
            for (T i=0; i<lst.size(); i++) {
                this->update(i, lst[i]);
            }
        }

        void update(T i, T x) {
            /* 元の配列 lst[i] に対応するセグ木のノード値をxに変更し、セグ木全体を更新する */
            T ni = this->_lst2node(i);
            this->nodes[ni] = x;
            while (ni > 0) {
                ni = (ni-1)/2;
                T l = ni*2+1; T r = ni*2+2;
                this->nodes[ni] = min(this->nodes[l], this->nodes[r]);
            }
        }

        T query(T a, T b) {
            /* 区間 [a,b) のクエリに応答する */
            return this->_find(a, b, 0, 0, this->n);
        }
};


void solve() {
    ll N, K; cin >> N >> K;
    vector<ll> P(N);
    for(ll i=0; i<N; i++) {
        cin >> P[i];
    }

    priority_queue<ll> que;
    for(ll i=0; i<K; i++) {
        que.push(-P[i]);
    }
    ll mn = -que.top(); que.pop();
    cout << mn << endl;
    for(ll i=K; i<N; i++) {
        if (mn < P[i]) {
            // 次に大きいやつ
            que.push(-P[i]);
            mn = -que.top(); que.pop();
            cout << mn << endl;
        }
        else {
            // mnのまま
            cout << mn << endl;
        }
    }
}


int main() {
    solve();
    return 0;
}
