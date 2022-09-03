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
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    string S; cin >> S;
    vector<ll> col(7);
    col[0] = 1;
    col[1] = 1;
    col[2] = 2;
    col[3] = 2;
    col[4] = 2;
    col[5] = 1;
    col[6] = 1;

    bool one_falled = false;
    for(ll i=0; i<S.size(); i++) {
        if (S[i] == '0') {
            if (i+1==1) {
                one_falled = true;
                col[3]--;
            }
            if (i+1==2) col[2]--;
            if (i+1==3) col[4]--;
            if (i+1==4) col[1]--;
            if (i+1==5) col[3]--;
            if (i+1==6) col[5]--;
            if (i+1==7) col[0]--;
            if (i+1==8) col[2]--;
            if (i+1==9) col[4]--;
            if (i+1==10) col[6]--;
        }
    }

    if (one_falled) {
        ll left = 0;
        while(left < 7) {
            if (col[left] >= 1) break;
            left++;
        }
        ll right = 6;
        while(right >= 0) {
            if (col[right] >= 1) break;
            right--;
        }
        ll mid = left+1;
        while(mid < right) {
            if (col[mid] == 0) {
                cout << "Yes" << endl;
                return;
            }
            mid++;
        }
    }
    cout << "No" << endl;

}


int main() {
    solve();
    return 0;
}