#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    int N; cin >> N;
    vector<vector<int>> D(N, vector<int>(N, 0));
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            int d; cin >> d;
            D[i][j] = d;
        }
    }

    /* 二次元累積和 */
    vector<vector<ll>> Dsum(N+1, vector<ll>(N+1, 0));
    for (int i=1; i<N+1; i++) {
        for (int j=1; j<N+1; j++) {
            Dsum[i][j] = Dsum[i-1][j] + Dsum[i][j-1] - Dsum[i-1][j-1] + D[i-1][j-1];
        }
    }

    /* 区間和[(x1,y1), (x2,y2))を全列挙する
    N=50のO(N**4)なので、まあ間に合うでしょ
    */
    map<int, ll> mp;  // mp[key] := keyマス使ったときの美味しさの最大値
    for (int x1=0; x1<N; x1++) {
        for (int y1=0; y1<N; y1++) {
            for (int x2=x1+1; x2<N+1; x2++) {
                for (int y2=y1+1; y2<N+1; y2++) {
                    int masu = (x2-x1)*(y2-y1);
                    if (!mp.count(masu)) {
                        mp[masu] = 0;
                    }
                    ll ret = Dsum[x2][y2] - Dsum[x1][y2] - Dsum[x2][y1] + Dsum[x1][y1];
                    mp[masu] = max(mp[masu], ret);
                }
            }
        }
    }

    /* 店員クエリを読み込み、それぞれの店員について回答する */
    int Q; cin >> Q;
    vector<int> P(Q, 0);
    for (int i=0; i<Q; i++) {
        int p; cin >> p;
        ll ans = 0;
        for (int j=1; j<=p; j++) {
            ans = max(ans, mp[j]);  // これも毎回計算せずにすることもできますね
        }
        cout << ans << endl;
    }

}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}