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

// 求める角度を求める
// theta1 = 240, theta2 = 30 のとき、求める角度は150
double get_angle(double theta1, double theta2) {
    double tmp = abs(theta1 - theta2);
    if (tmp > 180) return 360 - tmp;
    return tmp;
}

void solve() {
    ll N; cin >> N;
    vector<ll> X(N), Y(N);
    for(ll i=0; i<N; i++) {
        cin >> X[i] >> Y[i];
    }

    double ans = 0;
    for(ll j=0; j<N; j++) {
        vector<double> henkaku;  // 偏角 [0, 360)
        for(ll i=0; i<N; i++) {
            if (i==j) continue;
            double theta = atan2(Y[i]-Y[j], X[i]-X[j]) * 180 / M_PI;  // [-180, 180]
            if (theta < 0) {
                theta += 360;  // [0, 360) に変換
            }
            henkaku.push_back(theta);
        }

        // 偏角ソートして答えを探索
        sort(henkaku.begin(), henkaku.end());
        for(ll h=0; h<henkaku.size(); h++) {
            double theta1 = henkaku[h];
            double target;
            if (theta1 < 180) {
                target = theta1 + 180;
            }
            else {
                target = theta1  - 180;
            }

            int idx = lower_bound(henkaku.begin(), henkaku.end(), target) - henkaku.begin();
            double theta2;
            // 1個目
            if (idx-1 >= 0) {
                theta2 = henkaku[idx-1];
            }
            else {
                theta2 = henkaku[henkaku.size()-1];
            }
            ans = max(ans, get_angle(theta1, theta2));

            // 2個目
            if (idx < henkaku.size()) {
                theta2 = henkaku[idx];
            }
            else {
                theta2 = henkaku[0];
            }
            ans = max(ans, get_angle(theta1, theta2));
        }
    }

    printf("%.8lf\n", ans);
}


int main() {
    solve();
    return 0;
}