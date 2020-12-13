#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
const int INF = 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve(){
    long long N, M;
    cin >> N >> M;
    vector<long long> A(M);
    for (ll i=0LL; i<M; i++) {
        cin >> A[i];
    }
    sort(A.begin(), A.end());

    vector<long long>haba;
    long long min_haba = LONG_LONG_MAX;
    ll pre_masu = 0LL;
    ll h;
    for (ll i=0LL; i<M; i++) {
        h = A[i]-pre_masu-1LL;
        if (h <= 0) {
            pre_masu = A[i];
            continue;
        }
        haba.push_back(h);
        min_haba = min(min_haba, h);
        pre_masu = A[i];
    }
    h = (N+1) - pre_masu - 1LL;
    if (h > 0) {
        haba.push_back(h);
        min_haba = min(min_haba, h);
    }

    // bool is_ok = true;
    // for (ll i=0LL; i<haba.size(); i++) {
    //     if (haba[i]%min_haba != 0) {
    //         is_ok = false;
    //         break;
    //     }
    // }

    if (min_haba == LONG_LONG_MAX) {
        min_haba = 1LL;
    }

    // cout << "haba_min" << min_haba << endl;

    // 出力
    ll ans = 0LL;
    for (ll i=0LL; i<haba.size(); i++) {
        // cout << "haba[i]" << haba[i] << endl;
        if (haba[i]%min_haba == 0LL) {
            ans += haba[i]/min_haba;
        }
        else {
            ans += haba[i]/min_haba+1LL;
        }
    }
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}