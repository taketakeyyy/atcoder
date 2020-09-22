# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    A = list(map(int, input().split()))

    # 4の倍数がnum4個のとき、
    # 2の倍数がnum2個のとき、
    # num4*2 + 1 >= Nなら、Yes
    # ? 4 ? 4 ? 4 ?
    # そうでないなら、num4*2 + num2なら、Yes
    # 2 2 2 4 ? 4 ?
    num4 = 0
    num2 = 0
    for a in A:
        if a%4 == 0:
            num4 += 1
        elif a%2 == 0:
            num2 += 1
    
    if (num4*2+1) >= N:
        print("Yes")
    elif (num4*2)+num2 >= N:
        print("Yes")
    else:
        print("No")



if __name__ == "__main__":
    solve()
