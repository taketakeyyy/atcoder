#include <iostream>
#include <string>
#include <math.h>

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
    int N, M;
    int T[100], P[100], X[100];
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        cin >> T[i];
    }
    scanf("%d", &M);
    for(int i=0; i<M; i++){
        cin >> P[i] >> X[i];
    }

    // 出力
    int all_time = 0;
    for(int i=0; i<N; i++){
        all_time += T[i];
    }
    for(int i=0; i<M; i++){
        int ans = all_time;
        ans -= T[P[i]-1];
        ans += X[i];
        printf("%d\n", ans);
    }

    return 0;
}