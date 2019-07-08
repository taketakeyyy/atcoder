# -*- coding:utf-8 -*-

def solve():
    ABC = list(map(int, input().split()))
    n5 = 0
    n7 = 0
    for n in ABC:
        if n == 5:
            n5 += 1
        elif n == 7:
            n7 += 1
    
    if n5==2 and n7==1:
        print("YES")
    else:
        print("NO")


if __name__ == "__main__":
    solve()
