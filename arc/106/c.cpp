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
    ll N, M; cin >> N >> M;
    // 問題Pは、区間スケジューリング問題
    // 高橋の解法が正しく、アオキの解法は間違ってる
    // さて、構築の仕方だが、
    // (1) M >= 0のとき、
    // [1,1000000000] の区間を1つ用意し、
    // 残りの区間は[2,3],[4,5],...とやれば、
    // 青木の解法だと必ず答えは1になり、
    // 高橋の解法は残りの区間の数になるので、そのようにしてMになるように構築すれば良い
    // (2) M < 0のとき、
    // -1を出力する（高橋の解法が区間スケジューリング問題の最適な解き方なので、必ず高橋>=青木になるので）
    if (M < 0) {
        cout << -1 << endl;
        return;
    }
    if (M==0) {
        ll left=1, right=1000000000;
        for(int i=0; i<N; i++) {
            cout << left << " " << right << endl;
            left++; right--;
        }
        return;
    }

    if (M>=1 && N>=M+2) {
        cout << 1 << " " << 1000000000 << endl;
        ll left=2;
        ll n = 0;
        for(int i=0; i<M; i++) {
            cout << left << " " << left+1 << endl;
            left += 2;
            n++;
        }
        // 最後の一個はどうするか？
        ll right = 1000000000-1;
        for(int i=n; i<N-1; i++) {
            cout << left << " " << right << endl;
            left++; right--;
        }
        return;
    }
    else {
        cout << -1 << endl;
        return;
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}