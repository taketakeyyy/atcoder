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

/* リュカ数のメモ化 */
vector<int64_t> memo(87, -1);

int64_t L(int i) {
    /* i番目のリュカ数を返す */
    if (i==0) return memo.at(0);
    if (i==1) return memo.at(1);
    if (memo.at(i) == -1)
        memo.at(i) = L(i-1)+L(i-2);
    return memo.at(i);
}

void solve(){
    memo.at(0) = 2;
    memo.at(1) = 1;

    int N;
    cin >> N;

    int64_t ans = 0;

    cout << L(N) << endl;
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}