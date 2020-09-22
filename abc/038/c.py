# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    As = list(map(int, input().split()))

    if N == 1:
        print(1)
        return

    pre_a = As[0]
    seq = 0
    ans = 0
    for i in range(1, N):
        if pre_a < As[i]:
            seq += 1
            if i == N-1:
                ans += (seq+1)*seq/2  # 和の公式
                seq = 0
                break
        else:
            if seq != 0:
                ans += (seq+1)*seq/2  # 和の公式
                seq = 0
        pre_a = As[i]

    ans += N
    print(int(ans))



if __name__ == "__main__":
    solve()
