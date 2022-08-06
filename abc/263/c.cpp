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
    ll N, M; cin >> N >> M;

    priority_queue<vector<ll>, vector<vector<ll>>, greater<vector<ll>>> pq;  // 小さい順を維持する優先度付きキュー
    for(ll bit=0; bit<1<<M; bit++) {
        vector<ll> vec;
        for(ll d=0; d<M; d++) {
            if (bit>>d&1) {
                vec.push_back(d+1);
            }
        }

        if ((ll)vec.size() != N) { continue; }
        pq.push(vec);
    }

    // 出力
    while(!pq.empty()) {
        auto vec = pq.top(); pq.pop();
        for(auto a: vec) {
            cout << a << " ";
        }
        cout << endl;
    }
}


int main() {
    solve();
    return 0;
}