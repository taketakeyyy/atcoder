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


void solve() {
    ll Q; cin >> Q;
    // 先に筒に全部入れて、あとから取り出すクエリを処理しても大丈夫
    deque<pair<ll,ll>> deq;

    vector<ll> query;
    for(ll q=0; q<Q; q++) {
        ll cmd; cin >> cmd;
        if (cmd == 1) {
            ll x, c; cin >> x >> c;
            deq.push_back({x,c});
        }
        else {
            ll c; cin >> c;
            query.push_back(c);
        }
    }

    // 取り出すクエリを処理する
    for(ll q=0; q<query.size(); q++) {
        ll c = query[q];

        ll total = 0;
        while(1) {
            ll x, b;
            tie(x, b) = deq.front(); deq.pop_front();

            if (b <= c) {
                total += x*b;
                c -= b;
            }
            else {
                total += x*c;
                b -= c;
                c = 0;
                if (b > 0) {
                    deq.push_front({x, b});
                }
            }

            if (c == 0) break;
        }

        cout << total << endl;
    }
}


int main() {
    solve();
    return 0;
}