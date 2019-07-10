# -*- coding:utf-8 -*-

def solve():
    A, B, C = list(map(int, input().split()))
    print(A*B*2 + B*C*2 + C*A*2)

if __name__ == "__main__":
    solve()
