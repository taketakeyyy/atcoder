# -*- coding:utf-8 -*-

def solve():
    D, N = list(map(int, input().split()))

    if N != 100:
        ans = (100**D)*N
    else:
        ans = (100**D)*101
    
    print(ans)


if __name__ == "__main__":
    solve()
