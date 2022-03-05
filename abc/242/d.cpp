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

string S;

char operation(char ch) {
    if (ch == 'A') return 'B';
    if (ch == 'B') return 'C';
    return 'A';
}

void tree_solver(ll t, ll k) {
    // go_up
    vector<ll> res;
    char now = ' ';
    while(t>=1) {  // tがでかすぎるのでTLEになる可能性あり
        if (k==0) {  // 木の左端に到達した
            if (t%3 == 0) { now = S[0]; }
            else if (t%3 == 1) {
                now = operation(S[0]);
            }
            else if (t%3 == 2) {
                now = operation(operation(S[0]));
            }
            break;
        }

        res.push_back(k%2);
        k = k/2;
        t--;
    }

    // go_down
    ll b;
    if (now == ' ') { now = S[k]; }
    for(ll i=res.size()-1; i>=0; i--) {
        b = res[i];
        if (now == 'A') {
            if (b == 0) { now = 'B'; }
            else { now = 'C'; }
        }
        else if (now == 'B') {
            if (b == 0) { now = 'C'; }
            else { now = 'A'; }
        }
        else if (now == 'C') {
            if (b == 0) { now = 'A'; }
            else { now = 'B'; }
        }
    }

    // 出力
    cout << now << endl;
}

void solve() {
    cin >> S;
    ll Q; cin >> Q;
    for(ll q=0; q<Q; q++) {
        ll t, k; cin >> t >> k;
        tree_solver(t, k-1);
    }
}


int main() {
    solve();
    return 0;
}