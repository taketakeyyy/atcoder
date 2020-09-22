#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <map>

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

    int ans = 100001;
    for(int h=1; h<=N; h++){
        for(int w=1; h*w<=N; w++){
            ans = min(ans, N-h*w+abs(h-w));
            if(ans == 0){
                printf("0\n");
                return 0;
            }
        }
    }

    printf("%d\n",ans);
    return 0;
}