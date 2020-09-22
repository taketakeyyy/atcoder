# -*- coding:utf-8 -*-
"""考え方
・Nが奇数の時、
0が一個と、
2, 4, 6, ..., K (< N)が2個ずつ

・Nが偶数の時、
1, 3, ... K (< N)が2個ずつ

"""
def solve():
    N = int(input())
    A = list(map(int, input().split()))
    MOD = 10**9+7

    dic = {}
    for a in A:
        if not a in dic:
            dic[a] = 0
        dic[a] += 1
    
    if N%2 == 0:
        # Nが偶数のとき
        for i in range(N):
            num = i*2+1
            if num > N:
                break

            if not num in dic:
                print(0)
                return

            if dic[num] == 2:
                continue
            else:
                print(0)
                return
        print((2**i)%MOD)
        return
    else:
        # Nが奇数のとき
        i = -1
        while True:
            i += 1
            num = i*2
            if num > N:
                break
            
            if not num in dic:
                print(0)
                return
            
            if num == 0 and dic[num] == 1:
                continue
            elif num != 0 and dic[num] == 2:
                continue
            else:
                print(0)
                return
        print((2**(i-1))%MOD)
        return
        

if __name__ == "__main__":
    solve()
