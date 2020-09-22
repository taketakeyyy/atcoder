# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    H = list(map(int, input().split(" ")))

    ans = 1
    pre_h = H[0]
    for i in range(1, len(H)):
        if H[i] >= pre_h:
            ans += 1
            pre_h = H[i]
    print(ans)



if __name__ == "__main__":
    solve()