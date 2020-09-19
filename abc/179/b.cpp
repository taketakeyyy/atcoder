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
    cin >> N;

    int count = 0;
    for (int i=0; i<N; i++) {
        int d1, d2;
        cin >> d1 >> d2;
        if (d1 == d2) count++;
        else count = 0;

        if (count == 3) {
            cout << "Yes" << endl;
            return;
        }
    }
    cout << "No" << endl;
    return;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}