# -*- coding:utf-8 -*-

def solve():
    S = input()
    K = int(input())
    INF = 5000000000000000

    # num**INF はでかすぎる。無限長とみなしてOK

    now_k = 1
    for s in S:
        num = int(s)

        if now_k == K:
            print(num)
            return
        
        if num != 1:
            # 2以外なら、もうそれ。
            print(num)
            return
        
        now_k += 1
        



if __name__ == "__main__":
    solve()
