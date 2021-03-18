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
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll N; cin >> N;
    vector<vector<ll>> A(N, vector<ll>(N,0));
    for (int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin >> A[i][j];
        }
    }

    // A[a][b]+A[b][c] < A[a][c] となるとき、Aの表は破綻している
    for(int a=0; a<N; a++) {
        for (int b=0; b<N; b++) {
            for(int c=0; c<N; c++) {
                if (!(a!=b && b!=c && c!=a)) continue;
                if (A[a][b]+A[b][c]<A[a][c]) {
                    cout << -1 << endl;
                    return;
                }
            }
        }
    }

    // 存在する場合、道路の長さの和の最小を求めたい
    // A[a][b]+A[b][c] = A[a][c] みたいなaからcへ行くときに
    // (1) a->b->c
    // (2) a->c
    // の2種類の行き方があるが、(2)の道路は邪魔なので消し、(1)のみ残す
    vector<vector<ll>> cost;
    cost = A;
    for(int a=0; a<N; a++) {
        for (int b=0; b<N; b++) {
            for(int c=0; c<N; c++) {
                if (!(a!=b && b!=c && c!=a)) continue;
                if (A[a][b]+A[b][c]==A[a][c]) {
                    cost[a][c] = INF;
                }
            }
        }
    }

    ll ans = 0;
    for(int a=0; a<N; a++) {
        for(int b=0; b<N; b++) {
            if (cost[a][b]==INF) continue;
            ans += cost[a][b];
        }
    }
    ans /= 2;
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}