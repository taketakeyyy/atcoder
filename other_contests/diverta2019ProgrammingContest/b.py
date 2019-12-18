# -*- coding:utf-8 -*-

def solve():
    R, G, B, N = list(map(int, input().split()))

    # r, g, bのそれぞれに関してforで回すとO(N**3)で間に合わないので、
    # rを固定する。するとO(N**2)で解ける
    ans = 0
    for g in range(N+1):
        if g*G > N: break
        for b in range(N+1):
            if g*G+b*B > N: break
            if (N - (g*G+b*B))%R == 0:
                ans += 1
    print(ans)


if __name__ == "__main__":
    solve()
