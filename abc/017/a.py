# -*- coding:utf-8 -*-

def solve():
    s1, e1 = list(map(int, input().split()))
    s2, e2 = list(map(int, input().split()))
    s3, e3 = list(map(int, input().split()))
    print(int(s1*e1/10 + s2*e2/10 + s3*e3/10))

if __name__ == "__main__":
    solve()
