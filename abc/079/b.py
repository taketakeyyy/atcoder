# -*- coding:utf-8 -*-

def solve():
    N = int(input())

    if N == 1:
        print(1)
        return

    L0 = 2
    L1 = 1
    i = 2
    while True:
        ans = L0 + L1

        if i == N:
            break
        
        L0 = L1
        L1 = ans
        i += 1

    print(ans)

if __name__ == "__main__":
    solve()
