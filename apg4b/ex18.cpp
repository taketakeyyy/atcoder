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
    int N, M;
    cin >> N >> M;
    vector<vector<char>> data(N, vector<char>(N, '-'));

    int win, lose;
    for (int i=0; i<M; i++)
    {
        cin >> win >> lose;
        win--; lose--;
        data.at(win).at(lose) = 'o';
        data.at(lose).at(win) = 'x';
    }

    // 出力
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            cout << data.at(i).at(j);
            if (j != N-1) cout << ' ';
        }
        cout << endl;
    }
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}