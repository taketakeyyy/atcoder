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


void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> C;
    vector<ll> A(N), B(M);
    set<ll> Aset;
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        C.push_back(A[i]);
        Aset.insert(A[i]);
    }
    for(ll i=0; i<M; i++) {
        cin >> B[i];
        C.push_back(B[i]);
    }
    sort(C.begin(), C.end());

    // 調べる
    for(ll i=1; i<N+M; i++) {
        if (Aset.count(C[i-1]) and Aset.count(C[i])) {
            cout << "Yes" << endl;
            return;
        }
    }
    cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}