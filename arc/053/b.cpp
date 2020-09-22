#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    string S;
    cin >> S;
    map<char, int> mp;
    for (int i=0; i<S.size(); i++) {
        if (!mp.count(S.at(i))) {
            mp[S.at(i)] = 0;
        }
        mp[S.at(i)]++;
    }

    /* 奇数の文字は、回文の真ん中の文字にするしかない（あるいはその奇数の文字だけの回文にする）
    (例)kkkll => kkk, ll

    (例)kkkllllmo => kkk, lml, lol
    奇数の数を調べて、（上の例では奇数の文字は{k,m,o}の3個）奇数の文字の1個ずつを真ん中の文字にする。
    すると、余った文字はすべて偶数の文字になる。それを1文字のやつに均等に割り振る。
    k, m, o の3つが真ん中の文字。
    余った文字は{kk,llll}の6文字ですべて偶数
    これを均等に割り振る。6/3=2で2文字ずつ配れる。
    ただし、もし3文字ずつ配れるような場合になったとき、3文字配っても回文にはならないので注意。そのときは1文字減らした2文字配るのが答えになる。
    */
    int odd = 0;  // 奇数の文字の数
    int all = S.size();  // 全体の文字の数
    for (pair<char, int> p : mp) {
        char key = p.first;
        int  val = p.second;
        if (val%2 == 1) odd++;
    }

    if (odd == 0) {
        // もし奇数の文字が1文字も存在しないなら、すべての文字を使って1つの回文を作れる。
        cout << all << endl;
        return;
    }

    int syo = (all-odd)/odd;
    if (syo%2==1) {
        cout << (syo-1)+1 << endl;
    }
    else {
        cout << syo+1 << endl;
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}