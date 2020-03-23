# -*- coding:utf-8 -*-

"""
bit全探索の考え方

for div in range(2**3):
    print(div)
    # divの値を2進数で考えると、
    # 0000
    # 0001
    # 0010
    # 0011
    # 0100
    # 0101
    # ...
    # となるので、全探索を考えやすい

"""


def solve():
    """
    最初に横に切る方法を全探索し、
    次に、ギリギリのラインを縦に切っていく
    O(2**H W)

    Note1:
        1 << K  =>  2**k

    Note2:
        div>>i&1
        => divのi桁目が1であるかどうか
    """
    H, W, K = list(map(int, input().split()))
    S = ["" for _ in range(H)]
    for i in range(H):
        s = input()
        S[i] += s
    ans = float("inf")

    # 横に切るのを全部試す
    # divのbitが1のところで切る
    # gはグループ数
    for div in range(0, 1<<(H-1)):  # 2**(H-1)を全探索するとき、bitで考えたほうがラク
        g = 0
        ids = [0 for _ in range(H)]
        for i in range(H):
            ids[i] = g
            if div>>i&1:
                g += 1
        g += 1

        c = [[0 for _ in range(1005)] for __ in range(10)]

        for i in range(H):
            for j in range(W):
                c[ids[i]][j] += int(S[i][j])

        num = g-1  # g-1回、横に切る
        now = [0 for _ in range(g)]  # 今、各グループに何個のホワイトチョコレートがあるか
        def add(j, now, c):
            for i in range(g):
                now[i] += c[i][j]
            for i in range(g):
                if now[i] > K: return False
            return True

        for j in range(W):
            if not add(j, now, c):
                num += 1
                now = [0 for _ in range(g)]
                if not add(j, now, c):
                    num = float("inf")
                    break
        ans = min(ans, num)
    print(ans)


if __name__ == "__main__":
    solve()
