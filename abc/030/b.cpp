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
    int n, m;
    cin >> n >> m;
    // nは1分で360/12/60
    // mは1分で360/60
    if(n >= 12){
        n -= 12;
    }
    float tanshin, tyoushin;
    tanshin = (360.0/12.0) * n + (360.0/12.0/60.0) * m;
    tyoushin = (360.0/60.0) * m;
    float ans = abs(tyoushin - tanshin);
    ans = min(ans, 360-ans);
    printf("%f\n",ans);
    return 0;
}