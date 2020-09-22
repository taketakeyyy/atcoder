# -*- coding:utf-8 -*-

def solve():
    A, B, C = list(map(int, input().split()))

    # A(x1+x2+x3+...+xn)%B == C
    # (x1+x2+x3+...+xn) = Xとおくと
    # A*X%B == C
    # A*X ≡ C (mod B)
    # A*X-C ≡ 0 (mod B)

    for x in range(1, B+1):
        if (A*x-C)%B == 0:
            print("YES")
            return
    print("NO")

if __name__ == "__main__":
    solve()
