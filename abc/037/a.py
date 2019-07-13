# -*- coding:utf-8 -*-

def solve():
    A, B, C = list(map(int, input().split()))

    print(C // min(A,B))

if __name__ == "__main__":
    solve()
