# -*- coding:utf-8 -*-

def solve():
    import sys
    N = int(sys.stdin.readline())

    Aset = set()
    Adic = {}
    for i in range(N):
        a = int(sys.stdin.readline())
        Aset.add(a)
        if not a in Adic:
            Adic[a] = 0
        Adic[a] += 1

    if len(Aset) == N:
        print("Correct")
        return

    for i in range(1, N+1):
        if not i in Adic:
            right = i
        elif Adic[i] == 2:
            left = i

    print(left, right)


if __name__ == "__main__":
    solve()
