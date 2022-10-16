#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/b)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N; cin >> N;
    vector<ll> A;
    ll surplus = 0;  // 売ってもいい余り本の数
    set<ll> st;  // もう持ってる巻
    for(ll i=0; i<N; i++) {
        ll a; cin >> a;
        if (st.count(a)) {
            surplus++;
        }
        else {
            st.insert(a);
            A.push_back(a);
        }
    }
    sort(A.begin(), A.end());

    // 探索
    ll read = 1;  // 今読みたい巻
    ll left = 0;
    ll right = (ll)A.size()-1;
    while(1) {
        if (left <= right) {
            if (A[left] == read) {
                // ちょうど今読みたい巻でした
                read++;
                left++;
                continue;
            }
            else {
                // ちょうど今読みたい巻がない！
                if (surplus >= 2) {
                    // 2冊以上あまってるなら売って、買う
                    surplus -= 2;
                    read++;
                    continue;
                }
                else if (surplus == 1) {
                    // 1冊だけ余ってる
                    if (left <= right) {
                        // 後ろの巻を1冊売る
                        surplus -= 1;
                        right -= 1;
                        read++;
                        continue;
                    }
                    break;
                }
                else {
                    // 余りの本がない
                    if (left+1 <= right) {
                        // 後ろの巻を2冊売る
                        right -= 2;
                        read++;
                        continue;
                    }
                    break;
                }
            }
        }
        else {
            if (surplus >= 2) {
                surplus -= 2;
                read++;
                continue;
            }
            break;
        }
    }

    cout << read-1 << endl;
}


int main() {
    solve();
    return 0;
}