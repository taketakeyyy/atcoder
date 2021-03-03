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


void solve(){
    string A; cin >> A;
    if (A.size()==1) {
        cout << 0 << endl;
        return;
    }

    // 文字列の長さをNとする
    // 文字列を左端leftと右端rightとする
    // A[left]とA[right]を両端から一つずつ同時に走査していって・・・
    // (1) 2文字以上違うとき
    // どうやっても回文にはならない。25*N通り
    // (2) 1文字違うとき
    // その1文字を変えると回文にすることができるが、それ以外の文字はどう変えてもOK
    // 24+24+25*(N-2)
    // (3) すでに回文のとき
    // 文字列が奇数のとき（ABA）、25*(N-1)
    // 文字列が偶数のとき（ABBA）、25*N
    int left=0, right=A.size()-1;
    int diff = 0;
    while(1){
        if (right<=left) {
            break;
        }
        if (A[left]!=A[right]) {
            diff++;
        }
        left++; right--;
    }

    ll ans;
    if (diff>=2) {
        ans = 25*A.size();
    }
    else if(diff==1) {
        ans = 24+24+25*(A.size()-2);
    }
    else {
        if (A.size()&1) {
            ans = 25*(A.size()-1);
        }
        else {
            ans = 25*A.size();
        }
    }
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}