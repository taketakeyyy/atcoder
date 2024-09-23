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
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll M; cin >> M;
    vector<ll> A;

    while(1) {
        if (M == 0) break;
        ll x = 1;
        ll a = 0;
        for(ll _=1; _<=10; _++) {
            if (M < x) {
                break;
            }
            x *= 3;
            a++;
        }
        if (M < x) {
            x /= 3;
            a--;
        }
        M -= x;
        A.push_back(a);
    }

    // 出力
    ll N = A.size();
    cout << N << endl;
    for(ll i=0; i<N; i++) cout << A[i] << " ";
    cout << endl;
}


void solve2() {
    ll M; cin >> M;

    // 3進数
    vector<ll> vec; // vec[d] := 3^dの係数
    while(M != 0) {
        vec.push_back(M%3);
        M /= 3;
    }

    // Aを作る
    vector<ll> A;
    for(ll d=0; d<(ll)vec.size(); d++) {
        for(ll i=0; i<vec[d]; i++) A.push_back(d);
    }

    // 答え
    cout << A.size() << endl;
    for(ll i=0; i<(ll)A.size(); i++) cout << A[i] << " ";
    cout << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}