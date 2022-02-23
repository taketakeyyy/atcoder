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


void solve() {
    ll N; cin >> N;
    vector<ll> T(N);
    vector<ll> K(N);
    vector<vector<ll>> A(N);
    for(ll i=0; i<N; i++) {
        cin >> T[i];
        cin >> K[i];
        A[i].resize(K[i]);
        for(ll j=0; j<K[i]; j++) {
            cin >> A[i][j];
            A[i][j]--;
        }
    }

    deque<ll> que;
    set<ll> in_que;
    que.push_back(N-1);
    in_que.insert(N-1);
    for(ll i=0; i<K[N-1]; i++) {
        que.push_back(A[N-1][i]);
        in_que.insert(A[N-1][i]);
    }

    ll ans = 0;
    while(!que.empty()) {
        ll a = que.front();
        que.pop_front();
        ans += T[a];

        for(ll i=0; i<K[a]; i++) {
            if (!in_que.count(A[a][i])) {
                que.push_back(A[a][i]);
                in_que.insert(A[a][i]);
            }
        }
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}