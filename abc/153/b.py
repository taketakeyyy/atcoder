# -*- coding:utf-8 -*-

def solve():
    H, N = list(map(int, input().split()))
    As = list(map(int, input().split()))
    if H <= sum(As):
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    solve()
