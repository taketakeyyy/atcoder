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
// 初項a, 末項l, 項数n のときの等差数列の和
ll tousa1(const ll &a, const ll &l, const ll &n) { return ((a+l)*n)/2; }
// 初項a, 公差d, 項数n のときの等差数列の和
ll tousa2(const ll &a, const ll &d, const ll &n) { return ((2*a+(n-1)*d)*n)/2; }


void solve() {
    ll K; cin >> K;
    string S; cin >> S;
    string T; cin >> T;
    ll SN = S.size();
    ll TN = T.size();

    if (abs(SN-TN) >= 2) {
        cout << "No" << endl;
        return;
    }

    if (abs(SN-TN) == 0) {
        // S中の文字を1つ選んで変更して一致するか？ あるいは何もしないで一致するか
        ll diff = 0;
        for(ll i=0; i<SN; i++) {
            if (S[i]!=T[i]) diff++;
        }
        if (diff <= 1) {
            cout << "Yes" << endl;
            return;
        }
        cout << "No" << endl;
        return;
    }

    if (SN-TN == 1) {
        // S中の文字を1つ削除して一致するか？
        ll diff = 0;
        ll ti = 0;
        for(ll i=0; i<SN; i++) {
            if (S[i]!=T[ti]) {
                diff++;
                continue;
            }
            ti++;
        }
        if (diff == 1) {
            cout << "Yes" << endl;
            return;
        }
        cout << "No" << endl;
        return;
    }

    if (TN-SN == 1) {
        // S中の任意の位置に、1つ挿入して一致するか？
        ll diff = 0;
        ll si = 0;
        for(ll i=0; i<TN; i++) {
            if (S[si]!=T[i]) {
                diff++;
                continue;
            }
            si++;
        }
        if (diff == 1) {
            cout << "Yes" << endl;
            return;
        }
        cout << "No" << endl;
        return;
    }

    cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}