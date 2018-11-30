#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>

#define MOD 1000000007

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
    unsigned long ans = 0;
    int N, K;
    cin >> N >> K;

    if(N == 1){
        printf("%d\n",K);
        return 0;
    }

    ans = K * pow((K-1), (N-1));
    printf("%lu\n", ans);
    return 0;
}