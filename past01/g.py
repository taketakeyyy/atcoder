# -*- coding:utf-8 -*-

def solve():
    import sys
    N = int(sys.stdin.readline())
    Adic = {}
    for i in range(N-1):
        pads = [0]*(i+1)
        As = list(map(int, sys.stdin.readline().split()))
        As = pads + As
        for j in range(i+1, N):
            Adic[(i,j)] = As[j]


    def to3d(n):
        """nを三進数に直して返す"""
        ans = [0]*N
        i = N-1
        while n != 0:
            ans[i] = n%3
            n //= 3
            i -= 1
        return ans

    # 3進数で解く
    ans = -float("inf")
    for i in range(3**N):
        digits = to3d(i)
        group = []
        for _ in range(3):
            group.append([])

        for j in range(N):
            group[digits[j]].append(j)

        total = 0
        for j in range(3):
            members = group[j]

            if len(members) <= 1:
                continue

            members.sort()

            for k in range(len(members)):
                for l in range(k+1, len(members)):
                    total += Adic[(members[k], members[l])]

        ans = max(ans, total)

    print(ans)


if __name__ == "__main__":
    solve()
