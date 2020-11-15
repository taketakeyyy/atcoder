#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    /* なんかWA */
    long long X, Y, A, B, C;
    cin >> X >> Y >> A >> B >> C;
    vector<long long> P(A);
    vector<long long> Q(B);
    vector<long long> R(C);
    for (long long i=0; i<A; i++) cin >> P[i];
    for (long long i=0; i<B; i++) cin >> Q[i];
    for (long long i=0; i<C; i++) cin >> R[i];
    sort(P.begin(), P.end()); reverse(P.begin(), P.end());
    sort(Q.begin(), Q.end()); reverse(Q.begin(), Q.end());
    sort(R.begin(), R.end()); reverse(R.begin(), R.end());

    /*
    まず、Pの中から美味しい順にX個食べる
    次に、Qの中から美味しい順にY個食べる
    次に、食べたP,Qの中から、最も美味しさが低かったやつを吐き出し、Rの中から最も美味しいやつを食べ直す
    この「吐き出して食べ直す」操作を、Rの中から食べ直すものがなくなるまで繰り返す
    「吐き出して食べ直す」操作は高々C回なので、O(C)でいける
    */
    long long pi = X-1LL;
    long long qi = Y-1LL;
    long long ri = 0LL;
    long long ans = 0LL;
    ans += accumulate(P.begin(), P.begin()+X, 0LL);
    ans += accumulate(Q.begin(), Q.begin()+Y, 0LL);
    while (true) {
        if (ri == C) break;

        if (pi >= 0LL && P[pi] <= Q[qi]) {  // 次の吐き出す候補はP[pi]
            if (R[ri] > P[pi]) {            // 吐き出してRを食べたほうが良い
                ans -= P[pi];
                ans += R[ri];
                pi--; ri++;
                continue;
            }
            break;
        }
        else if (qi >= 0LL && Q[qi] <= P[pi]) {  // 次の吐き出す候補はQ[qi]
            if (R[ri] > Q[qi]) {                 // 吐き出してRを食べたほうが良い
                ans -= Q[qi];
                ans += R[ri];
                qi--; ri++;
                continue;
            }
            break;
        }
        break;
    }
    cout << ans << endl;
}


void solve2() {
    long long X, Y, A, B, C;
    cin >> X >> Y >> A >> B >> C;
    vector<long long> P(A);
    vector<long long> Q(B);
    vector<long long> R(C);
    for (long long i=0; i<A; i++) cin >> P[i];
    for (long long i=0; i<B; i++) cin >> Q[i];
    for (long long i=0; i<C; i++) cin >> R[i];
    sort(P.begin(), P.end()); reverse(P.begin(), P.end());
    sort(Q.begin(), Q.end()); reverse(Q.begin(), Q.end());
    sort(R.begin(), R.end()); reverse(R.begin(), R.end());

    /**解説AC
     * P,Q,Rをすべて一緒にしてALLを作り、美味しさ順にソートする。
     * ALLを美味しい順にX+Y個食べれば良い。このような食べ方は作れる。
     **/
    vector<long long> ALL;
    ALL.reserve(X+Y+C);
    ALL.insert(ALL.end(), P.begin(), P.begin()+X);
    ALL.insert(ALL.end(), Q.begin(), Q.begin()+Y);
    ALL.insert(ALL.end(), R.begin(), R.end());
    sort(ALL.begin(), ALL.end()); reverse(ALL.begin(), ALL.end());
    long long ans = accumulate(ALL.begin(), ALL.begin()+X+Y, 0LL);
    cout << ans << endl;
}

int main(int argc, char const *argv[]){
    solve2();
    return 0;
}