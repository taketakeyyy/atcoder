#define _USE_MATH_DEFINES  // M_PI等のフラグ

#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>
#include <list>

#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))

using namespace std;

string replace_with_str(string str, string str_from, string str_to) {
    string::size_type pos = 0;
    while (pos = str.find(str_from, pos), pos != string::npos) {
        str.replace(pos, str_from.length(), str_to);
        pos += str_to.length();
    }
    return str;
}


void solve(){
    #define BIG_NUM 1000000001
    int N, M;
    cin >> N >> M;

    vector<vector<long>> prefectures(N+1, vector<long>(0));
    map<long, int> mp;

    for(int i=1; i<=M; i++){
        long P, Y;
        cin >> P >> Y;
        prefectures[P].push_back(Y);
        mp[Y] = i;
    }

    vector<int> ans(M+1, 0);
    vector<int> shi_ans(M+1, 0);
    for(int i=1; i<=N; i++){
        stable_sort(prefectures[i].begin(), prefectures[i].end());

        for(int j=0; j<prefectures[i].size(); j++){
            ans[mp[prefectures[i][j]]] = j+1;
        }
    }

    for(int i=1; i<=M; i++){
        printf("%06d%06d\n", shi_ans[i], ans[i]);

}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}