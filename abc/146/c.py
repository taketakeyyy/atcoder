# -*- coding:utf-8 -*-

def solve():
    A, B, X = list(map(int,input().split()))

    def d(n):
        if n == 0:
            return 1

        ans = 1
        while True:
            n //= 10
            if n != 0:
                ans += 1
                continue
            return ans

    if X <= A*0+B*d(0):
        print(0)
        return

    # にぶたん
    left, right = 1, 10**9
    while True:
        if (right-left) == 1:
            need = A*right+B*d(right)
            if X < need:
                print(left)
                return
            else:
                print(right)
                return

        N = (left+right)//2
        need = A*N+B*d(N)
        if X < need:
            right = N
            continue
        elif X > need:
            left = N
            continue
        else:
            print(N)
            return



if __name__ == "__main__":
    solve()
