#define _USE_MATH_DEFINES  // M_PI等のフラグ

#include <iostream>
#include <bitset>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>
#include <list>

#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))

using namespace std;


void solve(){
    /**
     * stoul()を使うとunsigned long(符号なし32bit整数)の数値に変換するが、
     * これは最大 4294967295 まで表現できる
     * 入力例2の  9999999999 を変換できないので注意。
     * 代わりにstoull() := unsigned long long(符号なし64bit整数)に変換 を使う。
     * これは最大 18,446,744,073,709,551,615 まで表現できる
     * */
    string S;
    cin >> S;

    uint64_t ans = 0;
    int n = S.length()-1;

    for (int i=0; i<(1<<n); i++) {
        bitset<10> bit(i);

        int pre_j = 0;
        for (int j=0; j<n; j++) {
            if (bit.test(j)) {
                ans += stoull(S.substr(pre_j, (j+1-pre_j)));
                pre_j = j+1;
            }
        }
        if (pre_j != S.length()) {
            ans += stoull(S.substr(pre_j, S.length()-pre_j));
        }
    }

    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}