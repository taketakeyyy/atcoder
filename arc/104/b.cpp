#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    int N;
    string S;
    cin >> N >> S;

    int ans = 0;
    for (int i=0; i<N; i++) {
        int cg = 0; int at = 0;
        for (int j=i; j+1<=N-1; j+=2) {
            string s = S.substr(j,2);
            // cgとatの文字数を、しゃくとり法っぽく数える
            for (int k=0; k<2; k++) {
                if (s[k] == 'A') at++;
                else if (s[k] == 'T') at--;
                else if (s[k] == 'C') cg++;
                else cg--;
            }

            /* 相補的か？ */
            if (at==0 && cg==0) ans++;
        }
    }
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}