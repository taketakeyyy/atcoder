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

string str_slice(string s, int start, int end){
    if(end > s.size()){
        end = s.size();
    }
    if(end-start <= 0){
        return "";
    }
    return s.substr(start, end-start);
}

string kuriagari(string s){
    if(s == ""){
        return "3";
    }
    bool is_kuriagari = false;
    for(int i=s.size()-1; i!=-1; i--){
        if(s[i] == '3'){
            s[i] = '5';
        }
        else if(s[i] == '5'){
            s[i] = '7';
        }
        else if(s[i] == '7'){
            s[i] = '3';
            is_kuriagari = true;
        }

        if(is_kuriagari){
            is_kuriagari = false;
            if(i == 0){
                s = "3" + s;
                return s;
            }
            continue;
        }
        else{
            break;
        }
    }
    return s;
}

string add_753(string s){
    string tail = str_slice(s, s.size()-3, s.size());
    string head = "";
    if(s.size() >= 4){
        head = str_slice(s, 0, s.size()-3);
    }

   if(tail == "333"){
       return head + "335";
   }
   else if(tail == "335"){
       return head + "337";
   }
   else if(tail == "337"){
       return head + "353";
   }
   else if(tail == "353"){
       return head + "355";
   }
   else if(tail == "355"){
       return head + "357";
   }
   else if(tail == "357"){
       return head + "373";
   }
   else if(tail == "373"){
       return head + "375";
   }
   else if(tail == "375"){
       return head + "377";
   }
   else if(tail == "377"){
       return head + "533";
   }
   else if(tail == "533"){
       return head + "535";
   }
   else if(tail == "535"){
       return head + "537";
   }
   else if(tail == "537"){
       return head + "553";
   }
   else if(tail == "553"){
       return head + "555";
   }
   else if(tail == "555"){
       return head + "557";
   }
   else if(tail == "557"){
       return head + "573";
   }
   else if(tail == "573"){
       return head + "575";
   }
   else if(tail == "575"){
       return head + "577";
   }
   else if(tail == "577"){
       return head + "733";
   }
   else if(tail == "733"){
       return head + "735";
   }
   else if(tail == "735"){
       return head + "737";
   }
   else if(tail == "737"){
       return head + "753";
   }
   else if(tail == "753"){
       return head + "755";
   }
   else if(tail == "755"){
       return head + "757";
   }
   else if(tail == "757"){
       return head + "773";
   }
   else if(tail == "773"){
       return head + "775";
   }
   else if(tail == "775"){
       return head + "777";
   }
   else if(tail == "777"){
       head = kuriagari(head);
       return head + "333";
   }
}

void solve(){
    long long N;
    cin >> N;
    if(N<357){
        cout << "0\n";
        return;
    }

    int ans = 0;
    string str_num = "357";
    while (true){
        if(str_num.find("3") == string::npos ||
           str_num.find("5") == string::npos ||
           str_num.find("7") == string::npos
        ){
            str_num = add_753(str_num);
            continue;
        }
        if(stoll(str_num) <= N){
            ans ++;
        }
        else{
            break;
        }
        str_num = add_753(str_num);
    }
    cout << ans << endl;    
    return;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}