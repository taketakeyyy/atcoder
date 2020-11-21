#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    int N; string s;
    cin >> N; cin >> s;

    vector<string> stk;
    int delete_num = 0;
    for (int i=0; i<s.size(); i++) {
        if (i+2<s.size() && s[i]=='f' && s[i+1]=='o' && s[i+2]=='x') {
            /*fox見つけた*/
            delete_num += 3;
            i += 2;
            continue;
        }
        else if (i+1<s.size() && s[i]=='f' && s[i+1]=='o') {
            stk.push_back("fo");  // "fo"追加
            i += 1;
            continue;
        }
        else if (s[i]=='f') {
            stk.push_back("f");  // "f"追加
            continue;
        }
        else if (s[i]=='x') {
            if (!stk.empty() && stk.back()=="fo") {
                delete_num += 3;
                stk.pop_back();
                continue;
            }
            stk.clear();
            continue;
        }
        else if (i+1<s.size() && s[i]=='o' && s[i+1]=='x') {
            if (!stk.empty() && stk.back()=="f") {
                delete_num += 3;
                stk.pop_back();
                i += 1;
                continue;
            }
            stk.clear();
            i += 1;
            continue;
        }
        else if (s[i]=='o' && !stk.empty() && stk.back()=="f") {
            stk.pop_back();
            stk.push_back("fo");
            continue;
        }
        else {
            stk.clear();
            continue;
        }
    }

    cout << N - delete_num << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}