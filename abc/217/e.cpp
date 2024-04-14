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
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


// 解説AC
// クエリ3のときに毎回ソートしてたらアカン
// 数列Aは、 [ソート済み][キュー] という構造になっているので、
// [ソート済み]部分をプライオリティキューで、
// [キュー]部分を queue, deque などで持つことで、
// ならし計算量（償却計算量）O(QlogQ)で解ける。
void solve() {
    ll Q; cin >> Q;
    deque<ll> deq;
    priority_queue<ll, vector<ll>, greater<ll>> pq;  // 小さい順を維持する優先度付きキュー
    for(ll q=0; q<Q; q++) {
        ll cmd; cin >> cmd;
        if (cmd == 1) {
            // xを追加クエリ
            ll x; cin >> x;
            deq.push_back(x);
        }
        else if (cmd == 2) {
            // 出力クエリ
            if (pq.empty()) {
                cout << deq[0] << endl;
                deq.pop_front();
            }
            else {
                cout << pq.top() << endl;
                pq.pop();
            }
        }
        else {
            // ソートクエリ
            while(!deq.empty()) {
                ll x = deq.front(); deq.pop_front();
                pq.push(x);
            }
        }
    }
}


int main() {
    solve();
    return 0;
}