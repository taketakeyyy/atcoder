#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

const ll LIMIT = 55555;

vector<ll> make_primes5d1() {
    vector<ll> primes5d1;  // 5で割ると1余る素数
    vector<bool> is_prime(LIMIT+1, true);
    is_prime[0]=false; is_prime[1]=false;
    for(int i=2; i<=LIMIT; i++) {
        if (is_prime[i]) {
            if (i%5==1) {
                primes5d1.emplace_back(i);
            }
            for(int j=i*2; j<=LIMIT; j+=i) {
                is_prime[j] = false;
            }
        }
    }
    return primes5d1;
}


void solve() {
    // N個の素数のうち、どの5個を選んでもその和を合成数にしたい
    // 最小の素数2を5個選んだときの和は10なので、少なくとも5個の素数の和は必ず10以上になる
    // 5で割って1余る整数を5個足すと、必ず5で割り切れる
    // 5で割って1余る異なる素数を5個を足せば、必ず5で割り切れるので、合成数になる
    //
    ll N; cin >> N;
    vector<ll> primes5d1;  // 55555以下の、5で割ると1余る素数の配列(1408個あるので、N(<=55)個を選ぶのに十分)
    primes5d1 = make_primes5d1();
    for(int i=0; i<N; i++) {
        cout << primes5d1[i];
        if (i!=N-1) {
            cout << " ";
        }
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}