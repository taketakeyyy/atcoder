# -*- coding:utf-8 -*-

def solve():
    M, D = list(map(int, input().split()))
    if M%D == 0:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
