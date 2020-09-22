#include <iostream>
#include <string>
#include <math.h>
#include <vector>

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
    int H, W;
    cin >> H >> W;
    char ans[100][100];
    int ans_i = 0;

    for(int i=0; i<H; i++){
        string line;
        cin >> line;
        cout << line <<endl;
        cout << line << endl;
    }

    return 0;
}
