#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string string_all_erase(string s, char erase_c){
    std::string::size_type find_pos = s.find(erase_c);
    while(find_pos != std::string::npos){
    s.erase(find_pos, 1);  // 1文字削除
    find_pos = s.find(erase_c, find_pos);
    }
    return s;
}


void solve(){
    string w;
    cin >> w;
    string ans;
    w = string_all_erase(w, 'a');
    w = string_all_erase(w, 'i');
    w = string_all_erase(w, 'u');
    w = string_all_erase(w, 'e');
    w = string_all_erase(w, 'o');
    cout << w << endl;
}

int main(){
    solve();
    return 0;
}