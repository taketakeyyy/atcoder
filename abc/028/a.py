# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    if N <= 59:
        print("Bad")
    elif N >= 60 and N <= 89:
        print("Good")
    elif N >= 90 and N <= 99:
        print("Great")
    else:
        print("Perfect")
        

if __name__ == "__main__":
    solve()
