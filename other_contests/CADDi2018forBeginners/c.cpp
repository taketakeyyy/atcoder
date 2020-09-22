#define _USE_MATH_DEFINES  // M_PI等のフラグ

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

void solve(){
    long long N, P;
    cin >> N >> P;

    if(N == 1){
        cout << P << endl;
        return;
    }

    vector<long long> v(1, 1);
    v[0] = P;
    long long p = 2;
    long long ans = 1;

    while(true){
        if(p >= v[0]){
            break;
        }

        long long tmp = v[0];
        bool flag = true;
        for(int i=0; i<N; i++){
            if(tmp%p == 0){
                tmp = tmp/p;
            }
            else{
                flag = false;
                break;
            }
        }

        if(!flag){
            p++;
            continue;
        }

        v[0] = tmp * p;
        ans *= p;
    }

    cout << ans << endl;
    return;
}

void solve2(){
        #define BIG_NUM 1000001 // 10**6 + 1
    long long N, P;
    scanf("%lld %lld", &N, &P);

    if(N == 1){
        cout << P << endl;
        return;
    }
    if(P == 1){
        cout << P << endl;
        return;
    }

    long long p = 2;
    long long ans = 1;

    while(true){
        if(p >= P){
            break;
        }

        if(p >= BIG_NUM){
            // 2乗した時点でPより大きくなる
            break;
        }
        if(N >= 40){
            // 40以上で10**12を超えるの確定
            break;
        }
        long long pn = pow(p, N);
        if(pn < 0 || pn > 1000000000000){
            // 10**12を超えてたら捨ててよい
            // オーバーフローしてたらpn>P確定なので捨ててよい
            break;
        }
        if(pn > P){
            break;
        }


        while(true){
            if(P%pn == 0){
                P = (long long)(P/pn);
                ans *= p;
            }
            else{
                break;
            }
        }
        p++;
    }

    printf("%lld\n", ans);
    return;
}

void solve3(){
    long long N, P;
    cin >> N >> P;
    long long ans=1, tmp;

    if(P==1){
        cout << 1 << endl;
        return;
    }
    if(N==1){
        cout<<P<<endl;
        return;
    }

    for(int i=2; pow(i, N)<=P; i++){
        tmp = (long long)pow(i, N);
        while(P%tmp == 0){
            P = (P/tmp);
            ans *= i;
        }
    }

    cout << ans << endl;
    return;
}

int main(int argc, char const *argv[]){
    solve3();
}
