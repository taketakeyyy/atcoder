#include <iostream>
#include <string>
#include <math.h>

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
    long a, b, x, ans=0;
    scanf("%ld %ld %ld",&a, &b, &x);

    long b_ans = b/x + 1;
    long a_ans = 0;
    if(a != 0){
        a_ans = (a-1)/x + 1;
    }

    printf("%ld\n", b_ans - a_ans);

    return 0;
}