# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    S = input()

    ans = 0
    x = 0

    for moji in S:
        if moji == "I":
            x += 1
            ans = max(ans, x)
        else:
            x -= 1
    
    print(ans)


if __name__ == "__main__":
    solve()
