#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

int judge(vector<ll>& A, ll l, ll r, ll mid, ll K, ll L) {
    ll cut = 0;
    ll pre = 0;

    for(int i=0; i<(int)A.size(); i++) {
        if (cut == K) break;

        if (A[i]-pre >= mid) {
            pre = A[i];
            cut++;
            continue;
        }
    }

    if (cut==K && L-pre >= mid) {
        // すべてmid以上の大きさで切れているので、もっと大きく切れないかを調べる
        return 1;
    }
    else if (cut==K && L-pre < mid) {
        // midが大きすぎるので、もっと小さくする
        return -1;
    }

    if (cut < K) {
        // 大きく切りすぎなのでもっと小さく切る
        return -1;
    }
    else if (cut > K){
        // 小さく切りすぎなのでもっと大きく切る
        return 1;
    }
}

void solve() {
    ll N, L; cin >> N >> L;
    ll K; cin >> K;
    vector<ll> A(N);
    for(int i=0; i<N; i++) cin >> A[i];

    // 最小のようかんをにぶたんで求める
    ll l=0; ll r=1000000000;
    ll mid = (l+r)/2;

    while(r-l!=1) {
        if (judge(A, l, r, mid, K, L)==-1) {
            r = mid;
        }
        else {
            l = mid;
        }
        mid = (l+r)/2;
    }
    // lかrが答え
    ll l2 = l;
    ll r2 = r;
    if (judge(A, l, r, r2, K, L)==1) {
        cout << r2 << endl;
        return;
    }
    cout << l2 << endl;
    return;
}


int main() {
    solve();
    return 0;
}