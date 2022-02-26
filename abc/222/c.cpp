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

bool rank_sort(pair<ll,ll> p1, pair<ll,ll> p2) {
    ll win1 = p1.second;
    ll win2 = p2.second;
    if (win1 > win2) return true;
    if (win1 < win2) return false;
    ll id1 = p1.first;
    ll id2 = p2.first;
    return id1 < id2;
}

ll battle(ll id1, ll id2, ll j, vector<string> &A) {
    char c1 = A[id1][j];
    char c2 = A[id2][j];

    if (c1==c2) return -1;
    if (c1=='G' && c2=='C') return id1;
    if (c1=='C' && c2=='P') return id1;
    if (c1=='P' && c2=='G') return id1;
    return id2;
}

void solve() {
    ll N, M; cin >> N >> M;
    vector<string> A(2*N);
    for(ll i=0; i<2*N; i++) {
        cin >> A[i];
    }
    vector<pair<ll,ll>> ranking(2*N);  // {id, 勝数}
    for(ll i=0; i<2*N; i++) {
        ranking[i] = {i, 0};
    }

    // 試合する
    for(ll i=0; i<M; i++) {
        for(ll k=1; k<=N; k++) {
            pair<ll,ll> p1 = ranking[2*k-1-1];
            pair<ll,ll> p2 = ranking[2*k-1];
            ll res = battle(p1.first, p2.first, i, A);
            if (res == -1) continue;
            else if (res == p1.first) ranking[2*k-1-1].second++;
            else ranking[2*k-1].second++;
        }
        sort(ranking.begin(), ranking.end(), rank_sort);
    }

    // 結果出力
    for(ll i=0; i<2*N; i++) {
        cout << ranking[i].first+1 << endl;
    }
}


int main() {
    solve();
    return 0;
}