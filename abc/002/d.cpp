#define _USE_MATH_DEFINES  // M_PI等のフラグ

#include <iostream>
#include <algorithm>
#include <bitset>
#include <set>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <map>
#include <vector>
#include <list>

#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))

using namespace std;


void solve(){
    int N, M;
    cin >> N >> M;

    vector<int> relations(N);
    for (int i=0; i<M; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        relations.at(x) |= (1<<y);
        relations.at(y) |= (1<<x);
    }

    int ans = 1;
    for (int bit=0; bit<(1<<N); bit++) { // (2^12=4096)
        set<int> S;
        for (int i=0; i<N; i++) {  // 12
            if (bit>>i&1) {
                // iビット目が立っている := iを派閥に入れてみる
                S.insert(i);
            }
        }

        bool is_ok = true;
        for (int x : S) {  // 12
            for (int y : S) {  // 12
                if (x == y) continue;
                if (relations.at(x)>>y&1) continue;
                is_ok = false;
                break;
            }
            if (!is_ok) break;
        }

        if (is_ok) ans = max(ans, (int)S.size());
    }

    cout << ans << endl;
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}