#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;
const int INF = 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve(){
    ll N, K, M, R; cin >> N >> K >> M >> R;

    if (N==1) {
        cout << R << endl;
        return;
    }

    vector<ll>S(N-1);
    for(ll i=0; i<N-1; i++) cin >> S[i];

    sort(S.begin(), S.end(), greater<ll>());
    ll total = 0;

    if (K==N) {
        for (ll i=0; i<N-1; i++) total += S[i];

        // (total+x)/K >= Rになるようなxが存在したらOK
        ll x = max<ll>(K*R - total, 0);
        if (x <= M) {
            cout << x << endl;
            return;
        }
        else {
            cout << -1 << endl;
            return;
        }
    }
    else {
        for (ll i=0; i<K; i++) total += S[i];

        // long double avg = (long double)total/K;  // 誤差で死ぬ？
        if (total >= K*R) {
            // すでにK個の平均点がR以上なら、0点とってもよい
            cout << 0 << endl;
            return;
        }
        else {
            // なんとかしていい点とらなければならない。
            total -= S[K-1];
            // (total+x)/K >= Rになるようなxが存在したらOK
            ll x = K*R - total;
            if (x <= M) {
                cout << x << endl;
                return;
            }
            else {
                cout << -1 << endl;
                return;
            }
        }
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}