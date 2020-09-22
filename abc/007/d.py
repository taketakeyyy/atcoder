# -*- coding:utf-8 -*-
"""解説
https://torus711.hatenablog.com/entry/20150423/1429794075
http://drken1215.hatenablog.com/entry/2019/02/04/013700

dp[i][j][k] := 総数
i: 決定した桁数
j: N未満確定か(1:yes)
k: 4または9を含むか(1:yes)

更新方法
・i: 新たに1桁決めるので、i+1になる
・j: 元から1なら1。そうでない場合、次の桁に入れる値がD未満なら1になる
・k: 元から1なら1。そうでない場合、次の桁に入れる値が4または9なら1になる

別の書き方をすると、

・j = j || (d<D)
・k = k || d==4 || d==9
"""

def f(NUM):
    """ 0~NUMまでの禁止数字の個数を返す """
    S = str(NUM)
    L = len(S)
    dp = [[[0 for k in range(2)] for j in range(2)] for i in range(L+1)]
    dp[0][0][0] = 1

    for i in range(L):
        D = int(S[i])

        for j in range(2):
            for k in range(2):
                if j == 0:
                    d_max = D
                else:
                    d_max = 9
                
                for d in range(0, d_max+1):
                    dp[i+1][j or (d<D)][k or d==4 or d==9] += dp[i][j][k]

    return dp[L][0][1] + dp[L][1][1]


def solve():
    A, B = list(map(int, input().split()))

    ans = f(B) - f(A-1)
    print(ans)



if __name__ == "__main__":
    solve()
