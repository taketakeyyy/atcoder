# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    H = list(map(int,input().split()))

    if N == 1:
        print("Yes")
        return

    pre_h = H[0]
    for _, h in enumerate(H):
        if h == pre_h:
            continue
        elif h > pre_h:
            pre_h = (h - 1)
            continue
        print("No")
        return
    
    print("Yes")
    return


if __name__ == "__main__":
    solve()
