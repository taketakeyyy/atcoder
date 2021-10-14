#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 100000
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


ll sum_digits(ll n) {
    // 各桁の和を返す
    ll ret = 0;
    while(n!=0) {
        ret += n%10;
        n /= 10;
    }
    return ret;
}

ll func(ll x) {
    // 一連の処理をする
    ll y = sum_digits(x);
    ll z = (x+y)%MOD;
    return z;
}

void solve() {
    ll N, K; cin >> N >> K;

    // [方針]
    // 途中でzが0になったら、それ以降zは0にしかならないので、答えは0
    // それ以外は、周期があるとしか考えられない。なぜならzは [0, 10^5-1] の範囲をループするMODの世界だから。たかだか周期は10^5のはず。
    // 周期を考えるときは、必ずしも0の形をした周期とは限らず、6の形をした周期になることもある。注意。
    map<ll,ll> nxt;  // nxt[i] := 整数iを操作したあとの値
    map<ll,ll> timestamp;  // timestamp[i] := 整数iが出現した時刻
    ll count = 0;  // 一連の処理の回数

    while(1) {
        if (N==0) {
            cout << 0 << endl;
            return;
        }
        if (count==K) {
            // 操作終了
            cout << N << endl;
            return;
        }

        if (!nxt.count(N)) {
            timestamp[N] = count;
            ll nx = func(N);
            nxt[N] = nx;
            count++;
            N = nx;
            continue;
        }
        else {
            // 一周した
            ll t = count - timestamp[N];  // 周期
            ll m = (K-timestamp[N])%t;
            for(ll i=0; i<m; i++) {
                N = nxt[N];
            }
            cout << N << endl;
            return;
        }
    }
}


int main() {
    solve();
    return 0;
}