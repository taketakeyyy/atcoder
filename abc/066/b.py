# -*- coding:utf-8 -*-

def solve():
    S = input()
    for i in range(1, len(S)):
        s = S[:-i]
        if len(s)%2 != 0: continue # 長さが偶数じゃなければ偶文字列になりえない
        
        pivot = len(s)//2
        upper = s[0:pivot]
        lower = s[pivot:]

        if upper == lower:
            print(len(s))
            return

if __name__ == "__main__":
    solve()
