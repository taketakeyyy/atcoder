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
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(int i=0; i<N; i++) cin >> A[i];
    sort(A.begin(), A.end());

    if (N==2) {
        cout << A[1] - A[0] << endl;
        cout << A[1] << " " << A[0] << endl;
        return;
    }
    else {
        vector<ll> minus;
        vector<ll> plus;
        for(int i=0; i<N; i++) {
            if (A[i]<0) minus.push_back(A[i]);
            else plus.push_back(A[i]);
        }

        vector<pair<ll,ll>> pairs;
        ll ans = 0;
        if (plus.size()==0) {
            // 「最も大きい負の値」以外を正に変換する
            sort(minus.begin(), minus.end());
            ans = minus[minus.size()-1];
            for(int i=0; i<minus.size()-1; i++) {
                pairs.push_back(make_pair(ans, minus[i]));
                ans -= minus[i];
            }
        }
        else if (plus.size() == 1) {
            // 「正 - 負」を繰り返す
            ans = plus[0];
            for(int i=0; i<minus.size(); i++) {
                pairs.push_back(make_pair(ans, minus[i]));
                ans -= minus[i];
            }
        }
        else if (minus.size()==0){
            // 「最も小さい正の値」-「最も大きい数以外の、それ以外の数」を繰り返し、最後に「最も大きい数 - 負」をする
            sort(plus.begin(), plus.end());
            ans = plus[0];
            for(int i=1; i<plus.size()-1; i++) {
                pairs.push_back(make_pair(ans, plus[i]));
                ans -= plus[i];
            }
            pairs.push_back(make_pair(plus[plus.size()-1], ans));
            ans = plus[plus.size()-1] - ans;
        }
        else if (minus.size()==1) {
            ans = minus[0];
            for(int i=0; i<plus.size()-1; i++) {
                pairs.push_back(make_pair(ans, plus[i]));
                ans -= plus[i];
            }
            pairs.push_back(make_pair(plus[plus.size()-1], ans));
            ans = plus[plus.size()-1] - ans;
        }
        else {
            ans = minus[0];
            // 適当な1個を除くすべての正の数を、負に変換する
            for(int i=0; i<plus.size()-1; i++) {
                pairs.push_back(make_pair(ans, plus[i]));
                ans -= plus[i];
            }
            // 「適当な1個の正の数 - 負の数」を繰り返す
            minus[0] = ans;
            ans = plus[plus.size()-1];
            for(int i=0; i<minus.size(); i++) {
                pairs.push_back(make_pair(ans, minus[i]));
                ans -= minus[i];
            }
        }

        // 出力
        cout << ans << endl;
        for(int i=0; i<pairs.size(); i++) {
            ll a, b;
            tie(a, b) = pairs[i];
            printf("%lld %lld\n", a, b);
        }
    }
}


int main() {
    solve();
    return 0;
}