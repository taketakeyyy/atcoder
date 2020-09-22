import sys

"""全探索
Nが高々50なので、O(N^3)まではいけそう

力技で計算をシミュレートする方法
"""
def solve():
    N = int(input())
    As = list(map(int, sys.stdin.readline().split()))

    ans = -float("inf")  # 出力する答え

    # i := 高橋が選んだ数列の番号
    # j := 青木が選んだ数列の番号
    for i in range(N):
        aoki = []  # 青木がとりうる可能性のある得点をすべて格納する
        for j in range(N):
            if i == j: continue

            left, right = min(i,j), max(i,j)
            Ts = As[left: right+1]  # 数列T
            aoki.append(sum(Ts[1::2]))

        # 青木が最大の得点を得るときの 青木が選んだjをもとに、高橋の得点を計算する     
        j = aoki.index(max(aoki))
        left, right = min(i, j), max(i, j)
        Ts = As[left: right+1]
        ans = max(ans, sum(Ts[0::2]))

    print(ans)


if __name__ == "__main__":
    solve()