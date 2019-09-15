# -*- coding:utf-8 -*-
"""解説
大きい数が書かれた箱からボールを入れるかを決める。

こうすると、整数iが書かれた箱にボールを入れるか決めるとき、i以外のiの倍数が書かれた箱については、すでに
ボールを入れるか決まっている。
それらの箱に入ったボールの総和の偶奇がA[i]と異なる場合は箱にボールを入れる。

計算量は十分高速で、
O(N/1+N/2+...+N/N) = O(NlogN)
"""
def solve():
    N = int(input())
    A = list(map(int, input().split()))

    ans_num = 0
    ans = ""
    box = [0] * (N)
    for i in range(N-1, -1, -1):
        total = 0
        for j in range(i, N, i+1):
            # iの倍数のボールの個数の和を計算する
            total += box[j]
        if total%2 == A[i]:
            continue
        else:
            ans_num += 1
            ans += str(i+1) + " "
            box[i] = 1

    # 検査する
    for i in range(N-1, -1, -1):
        total = 0
        for j in range(i, N, i+1):
            total += box[j]
        if total%2 == A[i]:
            continue
        else:
            print(-1)
            return

    print(ans_num)
    if ans_num != 0:
        print(ans[0:-1])

if __name__ == "__main__":
    solve()
