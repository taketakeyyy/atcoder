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


void solve1() {
    // 公式解説。
    // A[i]/2 < B[i] < A[i] の制約が重要で、この条件があるからこそ成り立つ解法。

	// Step #1. 入力など
    ll N, K;
	cin >> N >> K;
    vector<ll> A(N), B(N);
    vector<ll> vec;
	for (int i = 0; i < N; i++) {
		cin >> A[i] >> B[i];
		vec.push_back(B[i]);
		vec.push_back(A[i] - B[i]);
	}

	// Step #2. 答えを求める
	long long Answer = 0;
	sort(vec.begin(), vec.end());
	reverse(vec.begin(), vec.end());
	for (int i = 0; i < K; i++) Answer += vec[i];

	// Step #3. 出力
	cout << Answer << endl;
}


int main() {
    solve1();
    return 0;
}