# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    As = list(map(int, input().split()))
    Bs = list(map(int, input().split()))
    Cs = list(map(int, input().split()))

    ans = 0
    pre_a = -100
    for i, a in enumerate(As):
        ans += Bs[a-1]
        if (a-1)-1 == pre_a:
            ans += Cs[pre_a]
        pre_a = a-1
    print(ans)

if __name__ == "__main__":
    solve()
