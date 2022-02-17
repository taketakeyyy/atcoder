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
    ll N; cin >> N;
    string S; cin >> S;

    // 逆からやる
    deque<ll> que; que.push_back(N);
    for (ll j=S.size()-1; j>=0; j--) {
        ll i = j+1;
        if (S[j] == 'R') {
            que.push_front(i-1);
        }
        else {
            que.push_back(i-1);
        }
    }

    // 出力
    while (!que.empty()) {
        if (que.size() != 1) {
            cout << que.front() << " ";
        }
        else {
            cout << que.front() << endl;
        }
        que.pop_front();
    }
}


int main() {
    solve();
    return 0;
}