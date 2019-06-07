# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    MOD = 10**9+7

    """考え方
    ・6の約数の個数は？
    6を素因数分解すると
    6 = 2 * 3
    2^(k1) * 3^(k2) （0<= k1,k2 <= 1）の組み合わせが約数（1,2,3,6）

    この約数の個数を求める問題は、「|k1|個のボールと|k2|個のボールを取り出す組み合わせ問題」と同じ。

    というふうに、まず素因数分解をして因数のknをそれぞれ求めて、その組合せの数を求めれば良い。
    """

    dic = {}  # dic[p] := 因数pの個数（ただしp^0も含めたいので初期値は1する）

    for n in range(2, N+1):
        num = n
        i = 2
        while True:
            if i > num: break

            if num%i == 0:
                num = num / i
                if not i in dic: dic[i] = 1
                dic[i] += 1
                continue
            else:
                i += 1
                continue

    ans = 1
    for key, value in dic.items():
        ans *= value
        ans %= MOD

    print(ans)


if __name__ == "__main__":
    solve()
