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
    int W, H, N;
    cin >> W >> H >> N;
    int x1 = 0, x2 = W, y1 = 0, y2 = H;
    for(int i=0; i<N; i++){
        int x, y, a;
        cin >> x >> y >> a;
        switch(a){
            case 1:
                x1 = max(x1, x);
                break;
            case 2:
                x2 = min(x2, x);
                break;
            case 3:
                y1 = max(y1, y);
                break;
            case 4:
                y2 = min(y2, y);
                break;
        }
    }

    if((x2-x1) < 0 || (y2-y1) < 0){
        printf("0\n");
        return 0;
    }
    printf("%d\n", (x2-x1)*(y2-y1));
    return 0;
}