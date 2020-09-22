# -*- coding:utf-8 -*-

def solve():
    N, M = list(map(int, input().split()))

    if N==1 and M==0:
        print(0)
        return

    ans = [None for _ in range(N)]

    for i in range(M):
        s, c = list(map(int, input().split()))

        if N!=1 and s==1 and c==0:
            print("-1")
            return

        if (ans[s-1] is not None) and (ans[s-1] != c):
            print("-1")
            return

        ans[s-1] = c

    s = ""
    for i, x in enumerate(ans):
        if (i==0) and (x is None):
            s += "1"
        elif x is None:
            s += "0"
        else:
            s += str(x)
    print(s)



if __name__ == "__main__":
    solve()
