#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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

ll N, P, K;
vector<vector<ll>> A;

// f(x) := 整数X=xとしたときの、経路コストがPスヌーク以下となる組の数
ll f(ll x) {
    vector<vector<ll>> dist(N, vector<ll>(N,0));
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            if (A[i][j]==-1) {
                dist[i][j] = x;
            }
            else if (i==j) {
                dist[i][j] = 0;
            }
            else {
                dist[i][j] = A[i][j];
            }
        }
    }

    // ワーシャルフロイド
    for(ll k=0; k<N; k++) {
        for(ll i=0; i<N; i++) {
            for(ll j=0; j<N; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // f(x)の数を数える
    ll cnt = 0;
    for(ll i=0; i<N; i++) {
        for(ll j=i+1; j<N; j++) {
            if (dist[i][j] <= P) cnt++;
        }
    }

    return cnt;
}


ll get_border(ll y) {
    ll l=0, r=5e9;  // 40*10^8 以上の適当な数字
    while(r-l>1) {
        ll mid = (l+r)/2;
        ll cnt = f(mid);
        if (cnt <= y) {
            // 左側を選ぶ
            r = mid;
        }
        else {
            // 右側を選ぶ
            l = mid;
        }
    }
    return r;
}

void solve() {
    // 入力
    cin >> N >> P >> K;
    A.resize(N);
    bool existX = false;
    for(ll i=0; i<N; i++) {
        A[i].resize(N);
        for(ll j=0; j<N; j++) {
            cin >> A[i][j];
            if (A[i][j]==-1) existX = true;
        }
    }

    if (existX) {
        ll L = get_border(K);
        ll R = get_border(K-1);

        if (R-L >= 2000000000LL) {  // これは何？
            cout << "Infinity" << endl;
        }
        else {
            cout << R - L << endl;
        }
    }
    else {
        // Xが存在しないとき
        if (f(0)==K) {  // 適当な値でKちょうどなら、無限個ある
            cout << "Infinity" << endl;
        }
        else {
            cout << 0 << endl;
        }
    }
}


int main() {
    solve();
    return 0;
}