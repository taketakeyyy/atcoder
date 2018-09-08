#include <iostream>
#include <string>
using namespace std;


void print_masu(char masu[][], H, W){
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++){
            printf("%c", masu[i][j]);
        }
        printf("\n");
    }
}


int main(void){
    int H, W;
    char masu[H][W];
    string a;
    int i, j;
    cin >> H >> W;

    for(i=0; i<H; i++){
        cin >> a;
        for(j=0; j<W; j++){
            masu[i][j] = a[j];
        }
    }

    print_masu(masu, H, W);
    return 0;
}
