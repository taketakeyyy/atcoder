# -*- coding:utf-8 -*-

def solve():
    a = int(input())
    b = int(input())
    n = int(input())
    i = n
    while True:
        if i%a==0 and i%b==0:
            print(i)
            return
        i += 1
    

if __name__ == "__main__":
    solve()
