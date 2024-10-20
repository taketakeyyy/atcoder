#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;


void solve() {
    ll N, Q; cin >> N >> Q;
    ll L = 0, R = 1;

    auto opt = [&](ll L, ll R, char H, ll T) -> ll {
        ll hand;
        ll another;
        if (H == 'L') {
            hand = L;
            another = R;
        }
        else {
            hand = R;
            another = L;
        }

        if (hand == T) return 0;

        // 時計回りを試す
        ll now = hand;
        ll res = 0;
        while(1) {
            now = (now+1)%N;
            res++;
            if (now == another) {res = -1; break;}
            if (now == T) break;
        }
        if (res != -1) return res;

        // 反時計回りを試す
        now = hand;
        res = 0;
        while(1) {
            now--;
            if (now==-1) now = N-1;
            res++;
            if (now == T) break;
        }
        return res;
    };

    ll ans = 0;
    for(ll q=0; q<Q; q++) {
        char h; cin >> h;
        ll t; cin >> t;
        t--;
        ans += opt(L, R, h, t);
        if (h == 'L') L = t;
        else R = t;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}