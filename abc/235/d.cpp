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
    ll a, N; cin >> a >> N;

    // ダイクストラっぽく解く
    ll MAX_N = 1000000-1;
    vector<ll> dist(MAX_N+1, INF);
    dist[1] = 0;
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> que;
    que.push({0,1});
    while(!que.empty()) {
        ll cost, x;
        tie(cost, x) = que.top();
        que.pop();

        if (x == N) {
            break;
        }

        if (a*x <= MAX_N && dist[a*x] > cost+1) {
            dist[a*x] = cost+1;
            que.push({cost+1, a*x});
        }

        if (x >= 10 && x%10!=0) {
            string sx = to_string(x);
            string nsx = sx[sx.size()-1] + sx.substr(0, sx.size()-1);
            ll nx = stoll(nsx);
            if (nx <= MAX_N && dist[nx] > cost+1) {
                dist[nx] = cost + 1;
                que.push({cost+1, nx});
            }
        }
    }

    if (dist[N] != INF) {
        cout << dist[N] << endl;
    }
    else {
        cout << -1 << endl;
    }
}


int main() {
    solve();
    return 0;
}