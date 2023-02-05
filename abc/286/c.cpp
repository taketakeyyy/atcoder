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


// 操作Aを i 回する
// 各iについて、回分判定O(N)。
void solve() {
    ll N, A, B; cin >> N >> A >> B;
    string S;
    cin >> S;

    auto kaibun = [&](string s) {
        ll cost = 0;
        ll l=0, r=N-1;
        while(r > l) {
            if (s[l] == s[r]) {
                ;
            }
            else {
                cost += B;
            }
            l++; r--;
        }
        return cost;
    };

    ll ans = INF;
    for(ll i=0; i<N; i++) {
        // 回分判定
        ll cost = i*A;
        cost += kaibun(S);
        ans = min(ans, cost);

        // Sに操作Aをする
        string newS = S.substr(1) + S.substr(0,1);
        S = newS;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}