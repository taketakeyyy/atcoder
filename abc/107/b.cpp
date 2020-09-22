#include <iostream>
#include <string>
#include <vector>
using namespace std;


void solve(){
    int H, W;
    cin >> H >> W;
    vector<vector<char>> masu(H, vector<char>(W, ' '));

    for(int h=0; h<H; h++){
        string s;
        cin >> s;
        for(int w=0; w<W; w++){
            masu[h][w] = s[w];
        }
    }

    // Hを削減する
    vector<vector<char>> masu2;
    for(int h=0; h<H; h++){
        bool can_delete = true;
        for(int w=0; w<W; w++){
            if(masu[h][w] != '.'){
                can_delete = false;
                break;
            }
        }

        if(!can_delete){
            vector<char> tmp(W);
            for(int w=0; w<W; w++){
                tmp[w] = masu[h][w];
            }
            masu2.push_back(tmp);
        }
    }

    //Wを削減する
    vector<vector<char>> masu3;
    for(int w=0; w<W; w++){
        bool can_delete = true;
        for(int h=0; h<H; h++){
            if(masu2[h][w] != '.'){
                can_delete = false;
                break;
            }
        }
/*
        if(!can_delete){
            for(int h=0; h<H; h++){
                masu3.push_back(N, 0);

            }
        }
*/
    }
}

void solve2(){
    int H, W;
    cin >> H >> W;
    vector<string> masu(H);

    for(int h=0; h<H; h++){
        string s;
        cin >> s;
        //masu[h].push_back(s);
        masu[h] = s;
    }

    vector<vector<bool>> printable(H, vector<bool>(W, true));

    // Hを走査
    for(int h=0; h<H; h++){
        bool can_delete = true;
        for(int w=0; w<W; w++){
            if(masu[h][w] != '.'){
                can_delete = false;
            }
        }

        if(can_delete){
            for(int w=0; w<W; w++){
                printable[h][w] = false;
            }
        }
    }

    // Wを走査
    for(int w=0; w<W; w++){
        bool can_delete = true;
        for(int h=0; h<H; h++){
            if(masu[h][w] != '.'){
                can_delete = false;
            }
        }

        if(can_delete){
            for(int h=0; h<H; h++){
                printable[h][w] = false;
            }
        }
    }

    // print
    for(int h=0; h<H; h++){
        int skip_count = 0;
        for(int w=0; w<W; w++){
            if(printable[h][w]){
                printf("%c",masu[h][w]);
            }
            else{
                skip_count++;
            }
        }
        if(skip_count != W){
            printf("\n");
        }
    }
    return;
}

int main(void){
    solve2();
    return 0;
}
