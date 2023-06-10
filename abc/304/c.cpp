#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
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


void solve() {
    ll N, D; std::cin >> N >> D;
    vector<pair<ll,ll>> coords(N);
    for(ll i=0; i<N; i++) {
        ll x, y; std::cin >> x >> y;
        coords[i] = {x,y};
    }

    // 範囲内か？
    auto is_in_range = [&](ll x1, ll y1, ll x2, ll y2) -> bool {
        return ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) <= D*D);
    };

    // 感染するか調べる
    deque<ll> deq;
    deq.push_back(0);
    vector<bool> infected(N, false);
    infected[0] = true;
    while(!deq.empty()) {
        ll i = deq.front(); deq.pop_front();
        auto[x1, y1] = coords[i];

        for(ll j=0; j<N; j++) {
            if (infected[j]) continue;
            auto[x2, y2] = coords[j];

            if(is_in_range(x1,y1,x2,y2)) {
                infected[j] = true;
                deq.push_back(j);
            }
        }
    }

    // 出力
    for(ll i=0; i<N; i++) {
        std::cout << (infected[i] ? "Yes" : "No") << endl;
    }
}


int main() {
    solve();
    return 0;
}