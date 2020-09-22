# -*- coding:utf-8 -*-

def solve():
    A, B = list(map(int, input().split()))
    S = input()

    for i in range(len(S)):
        if i == A:
            if S[A] == "-":
                continue
            print("No")
            return 
        try:
            int(S[i])
        except:
            print("No")
            return
    print("Yes")

if __name__ == "__main__":
    solve()
