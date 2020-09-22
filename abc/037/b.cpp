#include <iostream>
#include <string>
#include <cstring>
#include <math.h>
#include <algorithm>
#include <map>
#include <vector>

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

int main(int argc, char const *argv[]){
    int N, Q;
    cin >> N >> Q;
    vector<int> ans(N, 0);
    for(int q=0; q<Q; q++){
        int L, R, T;
        cin >> L >> R >> T;
        for(int i=L; i<=R; i++){
            ans[i-1] = T;
        }
    }
    for(int n=0; n<N; n++){
        printf("%d\n",ans[n]);
    }
    return 0;
}