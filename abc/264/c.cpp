#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/b)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

// bool search(ll i, ll j, const vector<) {

// }

void solve() {
    ll H1, W1; cin >> H1 >> W1;
    vector A(H1, vector<ll>(W1));
    for(ll i=0; i<H1; i++) {
        for(ll j=0; j<W1; j++) {
            cin >> A[i][j];
        }
    }
    ll H2, W2; cin >> H2 >> W2;
    vector B(H2, vector<ll>(W2));
    vector<ll> newB;
    for(ll i=0; i<H2; i++) {
        for(ll j=0; j<W2; j++) {
            cin >> B[i][j];
            newB.push_back(B[i][j]);
        }
    }

    // for(ll i1=0; i1<H1; i1++) {
    //     for(ll j1=0; j1<W1; j1++) {
    //         if (A[i1][j1]==B[0][0]) {
    //             // 探索
    //             search(i1, j1);
    //         }
    //     }
    // }

    // bit全探索
    for(ll bit1=0; bit1<1<<H1; bit1++) {
        for(ll bit2=0; bit2<1<<W1; bit2++) {
            vector<ll> newA;
            for(ll d1=0; d1<H1; d1++) {
                for(ll d2=0; d2<W1; d2++) {
                    if ((bit1>>d1&1) && (bit2>>d2&1)) {
                        newA.push_back(A[d1][d2]);
                    }
                }
            }

            // newA完成
            if (newA.size() != newB.size()) continue;
            bool is_same = true;
            for(ll i=0; i<newA.size(); i++) {
                if (newA[i]==newB[i]) continue;
                is_same = false;
                break;
            }
            if (is_same) {
                cout << "Yes" << endl;
                return;
            }
        }
    }
    cout << "No" << endl;
    return;
}


int main() {
    solve();
    return 0;
}