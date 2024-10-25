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
    ll N; cin >> N;
    vector<string> A(N);
    vector<set<char>> Aset(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        for(ll j=0; j<N; j++) {
            Aset[i].insert(A[i][j]);
        }
    }

    string S;
    for(ll i=0; i<N; i++) S.push_back('-');

    ll l=0, r=N-1;
    while(l<=r) {
        if (l==r) {
            S[l] = A[l][0];
            break;
        }

        bool found = false;
        for(ll i=0; i<26; i++) {
            char moji = 'a'+i;
            if (Aset[l].contains(moji) and Aset[r].contains(moji)) {
                S[l] = moji;
                S[r] = moji;
                found = true;
                break;
            }
        }
        if (found == false) {
            cout << -1 << endl;
            return;
        }
        l++; r--;
    }

    // 出力
    cout << S << endl;
}


int main() {
    solve();
    return 0;
}