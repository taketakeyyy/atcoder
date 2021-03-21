#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll N; cin >> N;
    vector<vector<ll>> C(N, vector<ll>(N, 0));
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cin >> C[i][j];
        }
    }

    vector<ll>minA(N);
    vector<ll>minB(N);
    for(int i=0; i<N; i++) {
        ll mn = INF;
        for(int j=0; j<N; j++) {
            mn = min(mn,C[i][j]);
        }
        minA[i] = mn;
    }

    for(int i=0; i<N; i++) {
        ll mn = INF;
        for(int j=0; j<N; j++) {
            mn = min(mn, C[j][i]);
        }
        minB[i] = mn;
    }

    ll l=0;
    ll r=minA[0];
    ll mid = (l+r)/2;
    while(abs(l-r)>1) {
        vector<ll> A(N,0);
        vector<ll> B(N,0);
        A[0] = mid;
        // Bが決まる
        bool is_next = false;
        for(int j=0; j<N; j++) {
            B[j] = C[0][j] - A[0];
            if (B[j]>minB[j]) {
                // Bが大きすぎ⇒A[0]をもっと上
                l = mid;
                mid = (l+r)/2;
                is_next = true;
                break;
            }
        }
        if (is_next) continue;

        // Aが正しく決まるか走査する
        bool is_ng = false;
        ll a;
        for(int i=1; i<N; i++) {
            a = C[i][0] - B[0];
            for(int j=0; j<N; j++) {
                ll aa = C[i][j] - B[j];
                if (aa < 0 || aa > minA[i] || a!=aa) {
                    a = aa;
                    is_ng = true;
                    break;
                }
            }
            if (is_ng) break;
            A[i] = a;
        }

        if (is_ng) {
            if (a < 0) {
                // aが小さすぎ⇒Bが大きすぎ⇒A[0]をもっと大きくする
                l = mid;
                mid = (l+r)/2;
                continue;
            }
            else {
                r = mid;
                mid = (l+r)/2;
                continue;
            }
        }

        // ここまで来たら、答えが確定している
        cout << "Yes" << endl;
        for(int i=0; i<N; i++) {
            cout << A[i];
            if (i!=N-1) cout << " ";
        }
        cout << endl;
        for(int i=0; i<N; i++) {
            cout << B[i];
            if (i!=N-1) cout << " ";
        }
        cout << endl;
        return;
    }

    // lかrのどちらかが答え
    vector<ll> A(N,0);
    vector<ll> B(N,0);
    bool is_ng = false;
    A[0] = l;
    bool is_next = false;
    for(int j=0; j<N; j++) {
        B[j] = C[0][j] - A[0];
        if (B[j]>minB[j]) {
            // Bが大きすぎ⇒A[0]をもっと上
            l = mid;
            mid = (l+r)/2;
            is_next = true;
            break;
        }
    }

    if (!is_next) {
        for(int i=1; i<N; i++) {
            ll a = C[i][0] - B[0];
            for(int j=0; j<N; j++) {
                ll aa = C[i][j] - B[j];
                if (a==aa) continue;
                is_ng = true;
                break;
            }
            if (is_ng) break;
            A[i] = a;
        }

        if (!is_ng) {
            // 答えが確定している
            cout << "Yes" << endl;
            for(int i=0; i<N; i++) {
                cout << A[i];
                if (i!=N-1) cout << " ";
            }
            cout << endl;
            for(int i=0; i<N; i++) {
                cout << B[i];
                if (i!=N-1) cout << " ";
            }
            cout << endl;
            return;
        }
    }


    if (l!=r) {
        is_next = false;
        is_ng = false;
        A[0] = r;
        for(int j=0; j<N; j++) {
            B[j] = C[0][j] - A[0];
            if (B[j]>minB[j]) {
                // Bが大きすぎ⇒A[0]をもっと上
                l = mid;
                mid = (l+r)/2;
                is_next = true;
                break;
            }
        }
        if (!is_next) {
            for(int i=1; i<N; i++) {
                ll a = C[i][0] - B[0];
                for(int j=0; j<N; j++) {
                    ll aa = C[i][j] - B[j];
                    if (a==aa) continue;
                    is_ng = true;
                    break;
                }
                if (is_ng) break;
                A[i] = a;
            }
            if (!is_ng) {
                // 答えが確定している
                cout << "Yes" << endl;
                for(int i=0; i<N; i++) {
                    cout << A[i];
                    if (i!=N-1) cout << " ";
                }
                cout << endl;
                for(int i=0; i<N; i++) {
                    cout << B[i];
                    if (i!=N-1) cout << " ";
                }
                cout << endl;
                return;
            }
        }
    }

    cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}