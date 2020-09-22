# -*- coding:utf-8 -*-

def solve():
    H, W = list(map(int, input().split()))

    ans = "#"*(W+2) + "\r\n"
    for h in range(H):
        ans += "#" + input() + "#\r\n"
    ans += "#"*(W+2)
    
    print(ans)

if __name__ == "__main__":
    solve()
