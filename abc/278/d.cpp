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


void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    ll Q; cin >> Q;
    ll all = 0;  // すべての要素に代入すべき値
    set<ll> done;  // 代入済みのインデックス
    bool is_flag = false;  // query=1が発生したか？
    for(ll q=0; q<Q; q++) {
        ll query; cin >> query;
        if (query == 1) {
            ll x; cin >> x;
            all = x;
            done = set<ll>();
            is_flag = true;
        }
        else if (query == 2) {
            ll i, x; cin >> i >> x; i--;

            if (is_flag) {
                if (done.count(i)) {
                    A[i] += x;
                }
                else {
                    A[i] = all + x;
                    done.insert(i);
                }
            }
            else {
                A[i] += x;
            }
        }
        else {
            ll i; cin >> i; i--;
            if (is_flag) {
                if (done.count(i)) {
                    cout << A[i] << endl;
                }
                else {
                    cout << all << endl;
                }
            }
            else {
                cout << A[i] << endl;
            }
        }
    }
}


int main() {
    solve();
    return 0;
}