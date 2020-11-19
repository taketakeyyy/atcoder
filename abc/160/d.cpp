#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    int N, X, Y; cin >> N >> X >> Y;
    X--; Y--;
    vector<int> dist(N, 0);
    for (int i=0; i<N; i++) {
        for (int j=i+1; j<N; j++) {
            // dist[min(j-i, min(abs(X-i)+abs(Y-j)+1, abs(Y-i)+abs(X-j)+1))]++;
            dist[min(j-i, abs(X-i)+abs(Y-j)+1)]++;
        }
    }

    for (int k=1; k<N; k++) {
        cout << dist[k] << endl;
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}