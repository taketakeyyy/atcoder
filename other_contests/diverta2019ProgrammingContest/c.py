# -*- coding:utf-8 -*-
"""解説
・XXXA：Aで終わる文字列
・BXXX：Bで始まる文字列
・BXXA：Bで始まりAで終わる文字列
この３つをうまく使った場合分け問題


"""
def solve():
    N = int(input())
    ans = 0
    endA = 0
    startB = 0
    ryouhou = 0
    # Aで終わるs1と、Bで始まるs2を連結させれば1個増える
    for i in range(N):
        s = input()
        if s[-1]=="A" and s[0]=="B":
            ryouhou += 1
        elif s[-1]=="A":
            endA += 1
        elif s[0]=="B":
            startB += 1
        
        ans += s.count("AB")
    

    if endA>=1 and startB>=1 and ryouhou>=1:
        ans += min(endA-1, startB-1)
        ans += ryouhou + 1
        print(ans)
        return
    elif ((endA>=1 and startB==0 and ryouhou>=1) or
          (endA==0 and startB>=1 and ryouhou>=1)):
        ans += ryouhou
        print(ans)
        return
    elif endA==0 and startB==0 and ryouhou>=1:
        ans += ryouhou-1
        print(ans)
        return
    else:
        # ryouhou==0のとき
        ans += min(endA, startB)
        rest = abs(max(endA, startB) - min(endA, startB))
        
        ans += min(rest, ryouhou)
        rest = ryouhou - rest
        if rest <= 0:
            print(ans)
            return
        else:
            ans += rest//2
            print(ans)
            return

if __name__ == "__main__":
    solve()
