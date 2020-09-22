# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    A = list(map(int, input().split()))
    B = list(map(int, input().split()))

    ans = 0
    motikosi = 0
    for i in range(N+1):
        if i <= N-1:
            if B[i]+motikosi > A[i]:
                # この街のモンスは全部倒す
                ans += A[i]
                restA = max(A[i]-motikosi, 0)
                motikosi = B[i] - restA
            else:
                # この街のモンスは全部倒しきれない
                ans += B[i]+motikosi
                motikosi = 0
        else:
            # 最後の街は総力戦
            if A[i] > motikosi:
                ans += motikosi
            else:
                ans += A[i]

    print(ans)


if __name__ == "__main__":
    solve()
