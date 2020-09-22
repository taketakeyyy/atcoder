#define _USE_MATH_DEFINES  // M_PI等のフラグ

#include <iostream>
#include <bitset>
#include <string>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>
#include <list>
#include <numeric>

#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i, n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int, int>;



set<int64_t> prime_factor(int64_t n) {
    set<int64_t> ans;
    if (n <= 1) return ans;

    for (int64_t i=2; i*i<=n; i++) {
        while (n%i == 0) {
            ans.insert(i);
            n /= i;
        }
    }

    if (n != 1) ans.insert(n);

    return ans;
}

void solve(){
    /* setを使った方法。TLE */
    int N;
    cin >> N;
    vector<int> As(N);
    for (int i=0; i<N; i++) {
        cin >> As.at(i);
    }

    vector<set<int64_t>>pf_sets;
    for (int64_t x : As) {
        set<int64_t> pf_set = prime_factor(x);
        pf_sets.push_back(pf_set);
    }

    // pairwiseにできるかを調べる
    bool is_pairwise = true;
    set<int64_t> a_set;
    for (auto pf_set : pf_sets) {
        set<int64_t> tmp_set;
        // tmp_set = a_set & pf_set をしたい
        for (auto x : pf_set) {
            if (a_set.count(x)) tmp_set.insert(x);
        }

        if (!tmp_set.empty()) {
            // すでに因数が存在するならpairwiseになれない
            is_pairwise = false;
            break;
        }
        // a_set |= pf_set をしたい
        for (auto x : pf_set) {
            a_set.insert(x);
        }
    }

    if (is_pairwise) {
        cout << "pairwise coprime" << endl;
        return;
    }

    // setwiseにできるかを調べる
    bool is_setwise = false;
    set<int64_t> base_pf_set = pf_sets.at(0);
    for (int i=1; i<N; i++) {
        // base_pf_set &= pf_set.at(i) をしたい
        set<int64_t> tmp_set;
        for (auto x : pf_sets.at(i)) {
            if (base_pf_set.count(x)) tmp_set.insert(x);
        }
        base_pf_set = tmp_set;

        if (base_pf_set.empty()) {
            is_setwise = true;
            break;
        }
    }

    if (is_setwise) {
        cout << "setwise coprime" << endl;
        return;
    }

    cout << "not coprime" << endl;

}


void solve2() {
    /* bitsetを使った方法。TLE*/
    int N;
    cin >> N;
    vector<int> As(N);
    for (int i=0; i<N; i++) {
        cin >> As.at(i);
    }

    const int BN = 1000000+1;
    vector<bitset<BN>>pf_bsets;
    for (int64_t x : As) {
        set<int64_t> pf_set = prime_factor(x);
        bitset<BN> b;
        for (auto x : pf_set) {
            b.set(x);
        }
        pf_bsets.push_back(b);
    }

    // pairwiseにできるかを調べる
    bool is_pairwise = true;
    bitset<BN> a_bset;
    for (auto pf_bset : pf_bsets) {
        if ((a_bset & pf_bset).any()) {
            // すでに因数が存在するならpairwiseになれない
            is_pairwise = false;
            break;
        }
        a_bset |= pf_bset;
    }

    if (is_pairwise) {
        cout << "pairwise coprime" << endl;
        return;
    }

    // setwiseにできるかを調べる
    bool is_setwise = false;
    bitset<BN> base_pf_bset = pf_bsets.at(0);
    for (int i=1; i<N; i++) {
        base_pf_bset &= pf_bsets.at(i);

        if (!base_pf_bset.any()) {
            is_setwise = true;
            break;
        }
    }

    if (is_setwise) {
        cout << "setwise coprime" << endl;
        return;
    }

    cout << "not coprime" << endl;
}


void solve3() {
    /* 解説AC */
    const int A = 1000005;

    int N;
    cin >> N;
    vector<int> As(N);
    vector<int> Cs(A);  // 頻度を求める配列
    for (int i=0; i<N; i++) {
        cin >> As.at(i);
        Cs[As[i]]++;
    }

    /* pairwise判定をする
    頻度Csを順にiを素因数として持つものを数えていく。
    同じ素因数をもつものが2つ以上あれば、その時点でpairwiseでない
    計算量はO(Alog(A))
    */
    bool pairwise = true;
    for (int i=2; i<A; i++) {
        int cnt = 0;
        for (int j=i; j<A; j+=i) {
            cnt += Cs[j];
        }
        if (cnt > 1) pairwise = false;
    }

    if (pairwise) {
        cout << "pairwise coprime" << endl;
        return;
    }

    /* setwise判定をする
    As[0]からAs[N]まで順番にGCDをして、結果が1だったらsetwise
    計算量はO(N)?
    ※ gcd(0,x) = x
    */
    int g = 0;
    rep(i,N) g = gcd(g, As[i]);
    if (g == 1) {
        cout << "setwise coprime" << endl;
        return;
    }

    cout << "not coprime" << endl;
    return;
}

int main(int argc, char const *argv[]){
    solve3();
    return 0;
}