# -*- coding:utf-8 -*-

def is_onaji(S):
    pre_moji = S[0]
    for i in range(1, len(S)):
        if S[i] == pre_moji:
            pre_moji = S[i]
            continue
        else:
            return False
    return True


def solve():
    S = input()
    K = int(input())
    N = len(S)

    if N == 1:
        print(K//2)
        return

    # 1回目
    base1 = 0
    pre_moji = S[0]
    for i in range(1, N):
        if S[i] == pre_moji:
            base1 += 1
            pre_moji = "?"
        else:
            pre_moji = S[i]

    if K == 1:
        print(base1)
        return

    # 2回目
    base2 = 0
    for i in range(0, N):
        if S[i] == pre_moji:
            base2 += 1
            pre_moji = "?"
        else:
            pre_moji = S[i]

    if K == 2:
        print(base1+base2)
        return

    # 3回目
    base3 = 0
    for i in range(0, N):
        if S[i] == pre_moji:
            base3 += 1
            pre_moji = "?"
        else:
            pre_moji = S[i]

    if K == 3:
        print(base1+base2+base3)
        return

    if base1 == base2 and base2 == base3:
        print(base1*K)
    elif base1 != base2 and base2 == base3:
        print(base1 + base2*(K-1))
    else:
        # base1とbase2が交互にくる
        print(base1*((K+1)//2) + base2*(K//2))


if __name__ == "__main__":
    solve()
