#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    int N, K; cin >> N >> K;
    vector<int> plus;
    vector<int> minus;
    for (int i=0; i<N; i++) {
        int a;
        cin >> a;
        if (a<0) {
            minus.push_back(a);
        }
        else {
            plus.push_back(a);
        }
    }

    sort(plus.begin(), plus.end());
    reverse(plus.begin(), plus.end());
    sort(minus.begin(), minus.end());
    reverse(minus.begin(), minus.end());

    vector<int> one = plus;  // コスト1消費するもの
    vector<int> two;  // コスト2消費するもの
    for (int i=0; i<minus.size(); i++) {
        if(i+1 < minus.size()) {
            two.push_back((minus[i]*minus[i+1])%MOD);
        }
    }

    vector<int> dp(K,0);  // dp[i]:=コストiのときの作れる最大値
    dp[1] = dp[0]+one[0];
    for (int i=1; i<K; i++) {

    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}