# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    As = list(map(int, input().split()))

    Ldic = {}
    for i, a in enumerate(As):
        if not (a+i) in Ldic:
            Ldic[a+i] = 0
        Ldic[a+i] += 1

    ans = 0
    for j, a in enumerate(As):
        if j-a in Ldic:
            ans += Ldic[j-a]

    print(ans)


if __name__ == "__main__":
    solve()
