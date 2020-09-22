# -*- coding:utf-8 -*-
"""解説
2019で割った余りが同じであるような2数a, bにおいて、

a * c mod 2019
b * c mod 2019

は同じ値になる。

今求めたいのは、

(i*j) ≡ x (mod 2019)

のxの最小値である。

(例)
L=2020のとき、
mod 2019の世界では、2020は1と等価

よって、
2020 * 2021 は、
1 * 2 と等価

つまり、

(i*j) ≡ x (mod 2019) は、

(i%2019) * (j%2019) ≡ x (mod 2019) と同じ

そう考えると、i, jの調べる範囲は、

・R-L < 2019のとき、

L%2019 ≦ i < j ≦ R%2019

でよい。

・R-L >= 2019のとき、

 mod2019の1周分の範囲を取れるので、必ずiかjが0になり、そのとき最小値0になるから。


よって、(i, j)として調べる候補はたかだか2019**2 であり、全探索で間に合う。
"""

def solve():
    L, R = list(map(int, input().split()))
    MOD = 2019

    if R-L >= MOD:
        print(0)
        return

    L %= MOD
    R %= MOD
    ans = MOD
    for i in range(L, R):
        for j in range(i+1, R+1):
            ans = min(ans, (i*j)%MOD)
            if ans == 0:
                print(ans)
                return
    print(ans)


if __name__ == "__main__":
    solve()
