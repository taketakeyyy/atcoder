#define _USE_MATH_DEFINES  // M_PI等のフラグ

#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>
#include <list>

#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))

using namespace std;


void solve(){
    int N, A;
    cin >> N >> A;
    char op;
    int B;
    for (int i=0; i<N; i++)
    {
        cin >> op >> B;
        if (op == '+')
            A += B;
        else if (op == '*')
            A *= B;
        else if (op == '-')
            A -= B;
        else if (op == '/')
        {
            if (B == 0)
            {
                cout << "error" << endl;
                return;
            }
            A /= B;
        }

        cout << i+1 << ":" << A << endl;
    }
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}