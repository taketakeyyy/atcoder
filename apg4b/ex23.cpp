#define _USE_MATH_DEFINES  // M_PI等のフラグ

#include <iostream>
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
    int N;
    cin >> N;
    map<int, int> mp;

    // 出現回数をmapで保存する
    for (int i=0; i<N; i++) {
        int a;
        cin >> a;

        if (!mp.count(a)) {
            mp[a] = 0;
        }
        mp.at(a) += 1;
    }

    // 最頻値を調べる
    pair<int, int> ans(-1,-1);
    for (auto p: mp) {
        int key = p.first;
        int val = p.second;
        if (p.second > ans.second) {
            ans = p;
        }
    }

    cout << ans.first << " " << ans.second << endl;
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}