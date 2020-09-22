# -*- coding:utf-8 -*-

def solve():
    A = int(input())
    B = int(input())
    cands = [1,2,3]
    cands.remove(A)
    cands.remove(B)
    print(cands[0])

if __name__ == "__main__":
    solve()
