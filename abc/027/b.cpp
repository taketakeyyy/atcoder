#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
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
    int sum = 0;
    vector<int> a(N, 0);
    for(int i=0; i<N; i++){
        cin >> a[i];
        sum += a[i];
    }
    
    if(sum%N != 0){
        printf("-1\n");
        return 0;
    }

    int person = sum / N;

    // iの左と右で住人の合計数がうまい具合になるようにする
    int ans = 0;
    int sum_left = 0, sum_right = sum;
    for(int i=0; i<N-1; i++){
        sum_left += a[i];
        sum_right -= a[i];
        if((i+1) * person != sum_left){
            ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}