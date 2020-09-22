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
    int L, H;
    cin >> L >> H;
    int N;
    cin >> N;
    for(int i=0; i<N; i++){
        int A;
        cin >> A;
        if(L <= A && A <= H){
            cout << "0" << endl;
        }
        else if(A < L){
            cout << L - A << endl;
        }
        else{
            printf("-1\n");
        }
    }
    return 0;
}