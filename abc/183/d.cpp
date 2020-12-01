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
    int N; long long W;
    cin >> N >> W;
    // vector<int> S(N);
    // vector<int> T(N);
    // vector<long long> P(N);
    // いもす法じゃん
    vector<long long> imos(2*pow(10,5)+1, 0);
    for (int i=0; i<N; i++) {
        int S; int T; long long P;
        cin >> S >> T >> P;
        imos[S] += P;
        imos[T] -= P;  // 時刻Tちょうどを除くので
    }

    vector<long long> rimos(2*pow(10,5)+1, 0);  // 累積和
    rimos[0] = imos[0];
    for (int i=1; i<2*pow(10,5)+1; i++) {
        rimos[i] = rimos[i-1] + imos[i];
    }

    // for (int i=0; i<11; i++) {
    //     cout << rimos[i] << " ";
    // }
    // cout << endl;

    // Wを超える時刻を探す
    auto it = max_element(rimos.begin(), rimos.end());
    if (*it > W) {
        cout << "No" << endl;
    }
    else {
        cout << "Yes" << endl;
    }
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}