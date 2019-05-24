# -*- coding:utf-8 -*-
""" 考え方
T=5のとき

0 2 6 10 20 25 30

total = 0  # お湯が出る総時間

・0~2
2-0 <= Tより、お湯が出てる時間は2

・2~6
6-2 <= Tより、お湯が出てる時間は4

・6~10
10-6 <= Tより、お湯が出てる時間は4

・10~20
20-10 > Tより、お湯が出てる時間はT

...

という風に、全探索すればOK

N = 2* 10**5なのでO(N)でも間に合うでしょ

"""
def solve():
    N, T = list(map(int, input().split()))
    t = list(map(int, input().split()))

    total = 0
    for i in range(1, len(t)):
        diff = t[i] - t[i-1]
        if diff <= T:
            total += diff
        else:
            total += T
    total += T  # 最後にTを足すのを忘れないこと

    print(total)


if __name__ == "__main__":
    solve()
