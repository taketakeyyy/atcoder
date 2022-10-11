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
    vector<ll> P(N), Q(N);
    for(ll i=0; i<N; i++) cin >> P[i];
    for(ll i=0; i<N; i++) cin >> Q[i];

    vector<ll> A(N);
    for(ll i=0; i<N; i++) A[i] = i+1;
    sort(A.begin(), A.end());

    // 順列全列挙でP,Qが辞書順何番目かをそれぞれ求める
    ll cnt = 0;
    ll a, b;
    do{
        cnt++;
        bool is_P = true, is_Q = true;

        for(ll i=0; i<N; i++) {
            if (A[i] != P[i]) is_P = false;
            if (A[i] != Q[i]) is_Q = false;
        }

        if (is_P) a = cnt;
        if (is_Q) b = cnt;
    }while(next_permutation(A.begin(), A.end()));

    // 出力
    cout << abs(a-b) << endl;
}


int main() {
    solve();
    return 0;
}