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
    vector<int> A(N);
    for (int i=0; i<N; i++) {
        cin >> A[i];
    }
    sort(A.begin(), A.end());

    int ans = 0;
    int ans_num = 0;
    for (int i=2; i<=A[A.size()-1]; i++) {
        int tmp_ans = 0;
        for (int j=0; j<A.size(); j++) {
            if (A[j]%i == 0) tmp_ans++;
        }
        if (tmp_ans > ans_num) {
            ans = i; ans_num = tmp_ans;
        }
    }

    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}