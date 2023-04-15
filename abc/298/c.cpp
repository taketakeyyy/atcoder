#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define intceil(a, b) ((a + (b - 1)) / b)
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long, long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x, y); }
void chmin(int& x, int y) { x = min(x, y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = {-1, 0, 1, 0};
vector<ll> vx = {0, 1, 0, -1};

void solve() {
    ll N;
    cin >> N;
    ll Q;
    cin >> Q;

    vector<multiset<ll>> box(N + 1);  // 箱iに入っているカードを管理
    map<ll, set<ll>> num2box;  // 数iが書かれたカードが入っている箱の集合
    for (ll q = 0; q < Q; q++) {
        ll query;
        cin >> query;
        if (query == 1) {
            ll i, j;
            cin >> i >> j;
            box[j].insert(i);
            num2box[i].insert(j);
        } else if (query == 2) {
            ll i;
            cin >> i;
            for (auto num : box[i]) {
                cout << num << " ";
            }
            cout << endl;
        } else {
            ll i;
            cin >> i;
            for (auto x : num2box[i]) {
                cout << x << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    solve();
    return 0;
}