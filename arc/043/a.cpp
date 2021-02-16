#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;
const int INF = 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve(){
    ll N, A, B; cin >> N >> A >> B;
    vector<ll> S(N);
    for (ll i=0; i<N; i++) cin >> S[i];

    /**
     * A = Q + P/N * (S[0]+...+S[N-1]) ・・・(★)
     *
     * (i) P > 0 のとき
     *   B = P(S[mxi]-S[mni])
     *   これを解くと、Pが求まるので、★よりQも求まる
     *
     * (ii) P<0のとき
     *   B = P(S[mni]-S[mxi])
     *   これを解くと、Pが求まるので、★よりQも求まる
     *
     * (iii) P=0のとき
     *   ★より、Q=A
     *   S'[i]=Qとなるが、このときB=0のときは成立する。B!=0のときは成立しない
     *
     ***/
    sort(S.begin(), S.end());
    ll mx = S[S.size()-1];
    ll mn = S[0];
    ll total = 0;
    for (ll i=0; i<N; i++) total += S[i];

    // (i)を検証
    if ((mx-mn)!=0) {
        double P = (double)B/(mx-mn);
        if (P > 0) {
            double Q = A - ((double)P/N) * total;
            printf("%.7lf %.7lf", P, Q);
            return;
        }
    }

    // (ii)を検証
    if ((mn-mx)!=0) {
        double P = (double)B/(mn-mx);
        if (P<0) {
            double Q = A - ((double)P/N) * total;
            printf("%.7lf %.7lf", P, Q);
            return;
        }
    }

    // (iii)を検証
    if (B==0) {
        cout << 0 << " " << 1 << endl;
        return;
    }

    cout << -1 << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}