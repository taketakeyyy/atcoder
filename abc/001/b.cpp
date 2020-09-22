#include <iostream>

using namespace std;

void solve(){
    int m;
    cin >> m;

    if(m < 100){
        cout << "00" << endl;
    }
    else if(m >= 100 && m <= 5000){        
        printf("%02d\n", m/100.0);
    }
    else if(m >= 6000 && m <= 30000){
        printf("%d\n", (m/1000.0)+50 );
    }
    else if(m >= 35000 && m <= 70000){
        printf("%d\n", ((m/1000-30)/5.0)+80 );
    }
    else{
        cout << "89" << endl;
    }
    return;
}

int main(){
    solve();
}