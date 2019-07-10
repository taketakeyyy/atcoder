# -*- coding:utf-8 -*-
"""
.....A
B.....
を連結させればABは一個増える

(例)
...A
B...
B..A
が一個ずつある時、

...A B..A B...
とやる2が正解で、

...A B... B..A
とやると1で不正解

"""
def solve():
    N = int(input())

    ans = 0
    b_start = 0
    a_end = 0
    ryouhou = 0
    for _ in range(N):
        s = input()
        ans += s.count("AB")
        
        if s[0] == "B" and s[-1] == "A":
            ryouhou += 1
        elif s[0] == "B":
            b_start += 1
        elif s[-1] == "A":
            a_end += 1
    
    # まず、ryouhouを可能な限りつなげる
    if ryouhou > 0:
        ans += ryouhou - 1

        # 両端にb_startとa_endをくっつけれるならそうする
        if b_start > 0:
            b_start -= 1
            ans += 1
        if a_end > 0:
            a_end -= 1
            ans += 1
    
    # 残ったb_startとa_endでABを作る
    ans += min(b_start, a_end)

    print(ans)
   
        

if __name__ == "__main__":
    solve()
