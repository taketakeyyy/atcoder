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

    vector<pair<double, double>> vec(N);
    for (int i=0; i<N; i++) {
        double x, y;
        cin >> x >> y;
        pair<double, double> p(x,y);
        vec[i] = p;
    }

    for (int i=0; i<N; i++) {
        set<double> S;  // 傾きを格納する集合
        bool vertical = false;
        double x1 = vec[i].first;
        double y1 = vec[i].second;
        for (int j=i+1; j<N; j++) {
            double x2 = vec[j].first;
            double y2 = vec[j].second;
            if (!vertical && x2==x1) {
                vertical = true;
            }
            else if (vertical && x2==x1) {
                cout << "Yes" << endl;
                return;
            }

            double d = (y2-y1)/(x2-x1);
            if (S.count(d)) {
                cout << "Yes" << endl;
                return;
            }
            S.insert(d);
        }
    }
    cout << "No" << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}