#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    int T, N;
    cin >> T >> N;
    vector<int> A(N);
    for (int i=0; i<N; i++) {
        int a;
        cin >> a;
        A[i] = a;
    }
    sort(A.begin(), A.end());

    int M;
    cin >> M;
    vector<int> B(M);
    for (int i=0; i<M; i++) {
        int b; cin >> b;
        B[i] = b;
    }
    sort(B.begin(), B.end());

    int j=0;
    for (int i=0; i<A.size(); i++) {
        if (B[j]<A[i]) {
            // 人が来た時にたこ焼きがなかったら終わり
            cout << "no" << endl;
            return;
        }

        if (B[j]>=A[i] && B[j]-A[i]<=T) {
            j++;
            if (j==B.size()) {
                cout << "yes" << endl;
                return;
            }
        }
    }
    cout << "no" << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}