# -*- coding:utf-8 -*-

"""解説
すべての問題の合計を求める。SUMとする。

・SUM%10 != 0のとき、答えはSUM

・SUM%10 == 0のとき、(SUM-x)%10 == 0となるような最小のxを探す。

"""

def solve():
    N = int(input())
    S = []
    for i in range(N):
        s = int(input())
        S.append(s)
    SUM = sum(S)
    
    if SUM%10 != 0:
        print(SUM)
        return

    S.sort()
    for i in range(N):
        ans = SUM - S[i]
        if ans%10 != 0:
            print(ans)
            return
    
    print(0)
        

if __name__ == "__main__":
    solve()
