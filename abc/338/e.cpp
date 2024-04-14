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
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };

// 「点1 から点2N に向かって左から右に見ていったとき、曲線i の左端が来て、その右端が来る前に別の曲線j の左端が来たならば、曲線j の右端は曲線i の右端より先に来なければならない」
void solve() {
    ll N; cin >> N;
    map<ll,ll> A2B, B2A;
    for(ll i=0; i<N; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        if (a > b) swap(a,b);
        A2B[a] = b;
        B2A[b] = a;
    }

    // 左から順に走査
    set<ll> right; // 今まで追加された弦の右端の集合
    for(ll i=0; i<2*N; i++) {
        if (A2B.count(i)) { // 頂点iが弦の左端ならば
            // 交差判定
            auto it = right.upper_bound(A2B[i]);
            if (it!=right.begin()) {
                cout << "Yes" << endl;
                return;
            }
            // 右端を追加
            right.insert(A2B[i]);
            continue;
        }
        if (B2A.count(i)) { // 頂点iが弦の右端ならば
            right.erase(i);
        }
    }
    cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}