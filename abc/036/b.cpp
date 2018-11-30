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
    int N;
    cin >> N;
    vector<vector<char>> ans(N, vector<char>(N, ' '));
    int w = N - 1;
    for(int n=0; n<N; n++){
        string s;
        cin >> s;
        for(int i=0, h=0; h<N; i++, h++){
            ans[h][w] = s[i];
        }
        w--;
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            printf("%c",ans[i][j]);
        }
        printf("\n");
    }
    return 0;
}