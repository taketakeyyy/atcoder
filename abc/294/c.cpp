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
    ll N, M; cin >> N >> M;
    vector<ll> A(N), B(M);
    vector<ll> C;
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        C.push_back(A[i]);
    }
    for(ll i=0; i<M; i++) {
        cin >> B[i];
        C.push_back(B[i]);
    }
    sort(C.begin(), C.end());

    map<ll,ll> mp;
    for(ll i=0; i<(ll)C.size(); i++) {
        mp[C[i]] = i;
    }

    // 出力
    for(ll i=0; i<N; i++) {
        cout << mp[A[i]]+1 << " ";
    }
    cout << endl;
    for(ll i=0; i<M; i++) {
        cout << mp[B[i]]+1 << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}