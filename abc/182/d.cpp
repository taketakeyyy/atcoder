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
    vector<long long> A(N);
    vector<long long> SUM(N+1);  // 累積和
    for (int i=0; i<N; i++) {
        cin >> A[i];
        SUM[i+1] = SUM[i]+A[i];
    }

    // A[0]~A[N-1]の一連の動作をしたときの最大座標tmp_ansと、そのときの一連の動作回数ans_iを求める
    long long tmp_ans = 0;
    int ans_i = 0;
    long long total = 0;
    for (int i=0; i<N+1; i++) {
        total += SUM[i];
        if (total >= tmp_ans) {
            ans_i = i;
            tmp_ans = total;
        }
    }

    // ans_iのときの最大値を探索する
    long long ans2 = -3*pow(10,13);
    ans2 = tmp_ans - SUM[ans_i];
    total = ans2;
    for (int i=0; i<ans_i; i++) {
        total += A[i];
        ans2 = max(ans2, total);
    }

    // ans_i+1のときに最大値になるパターンもあるので、それも探索する
    long long ans3 = -3*pow(10,13);
    if (ans_i+1 <= N) {
        ans3 = tmp_ans;
        total = ans3;
        for (int i=0; i<ans_i+1; i++) {
            total += A[i];
            ans3 = max(ans3, total);
        }
    }

    cout << max(ans2, ans3) << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}