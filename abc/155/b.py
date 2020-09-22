# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    As = list(map(int, input().split()))
    for a in As:
        if a%2==0:
            if a%3==0 or a%5==0:
                continue
            else:
                print("DENIED")
                return
    print("APPROVED")


if __name__ == "__main__":
    solve()
