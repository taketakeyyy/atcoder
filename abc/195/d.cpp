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

bool bagsort(pair<int,int>a, pair<int,int>b) {
    // 価値が高くて、大きさが大きいほど左
    if (a.first > b.first) return true;
    if (a.first == b.first) {
        if (a.second >= b.second) return true;
    }
    return false;
}

bool bagsort1(pair<int,int>a, pair<int,int>b) {
    // 価値が高いほうが左
    return (a.first >= b.first);
}

bool bagsort2(pair<int,int>a, pair<int,int>b) {
    // 大きいほど左
    return (a.second >= b.second);
}

int N, M, Q;
vector<pair<int,int>> bags;  // 荷物
vector<int> X;
vector<int> newX;
set<int> used;

void solve() {
    cin >> N >> M >> Q;
    for (int i=0; i<N; i++) {
        int w, v; cin >> w >> v;
        bags.push_back(make_pair(v,w));
    }
    sort(bags.begin(), bags.end(), bagsort);
    // sort(bags.begin(), bags.end(), bagsort2);
    // sort(bags.begin(), bags.end(), bagsort1);

    for (int m=0; m<M; m++) {
        int x; cin >> x;
        X.push_back(x);
    }

    for(int q=0; q<Q; q++) {
        int L, R; cin >> L >> R;
        L--; R--;
        newX.resize(0);
        for(int m=0; m<M; m++) {
            if (L<=m && m<=R) continue;
            newX.push_back(X[m]);
        }
        sort(newX.begin(), newX.end());

        int ans = 0;
        used = set<int>();
        for(int i=0; i<(int)newX.size(); i++) {
            for(int j=0; j<(int)bags.size(); j++) {
                if (used.count(j)) continue;

                if (newX[i] >= bags[j].second) {
                    ans += bags[j].first;
                    used.insert(j);
                    break;
                }
            }
        }
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}