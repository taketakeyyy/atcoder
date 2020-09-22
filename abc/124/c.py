# -*- coding:utf-8 -*-

def solve():
    S= input()
    S = list(S)

    # 010101...のとき
    ans1 = 0
    for i in range(0, len(S)):
        if i%2==0 and S[i] == "1":
            ans1 += 1
        elif i%2==1 and S[i] == "0":
            ans1 += 1
    
    # 1010101...のとき
    ans2 = 0
    for i in range(0, len(S)):
        if i%2==0 and S[i] == "0":
            ans2 += 1
        elif i%2==1 and S[i] == "1":
            ans2 += 1

    print(min(ans1, ans2))

if __name__ == "__main__":
    solve()