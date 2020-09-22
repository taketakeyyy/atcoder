# -*- coding:utf-8 -*-

def solve():
    N, K = list(map(int, input().split(" ")))
    S = input()

    # 累積和で解く
    i = 0
    ruiseki = [0]
    while True:
        if i >= N:
            break
        
        num = 0
        if S[i] == "1":
            while i < N and S[i] == "1":
                num += 1
                i += 1
            ruiseki.append(num + ruiseki[-1])
        else:
            while i < N and S[i] == "0":
                num += 1
                i += 1
            ruiseki.append(num + ruiseki[-1])

    import math
    if S[0] == "1":
        zero_num = math.floor((len(ruiseki)-1)/2)
    else:
        zero_num = math.ceil((len(ruiseki)-1)/2)

    if K >= zero_num:
        print(ruiseki[-1])
        return

    ans = 0
    if S[0] == "1":
        for i in range(2, len(ruiseki), 2):
            end = i + 2*(K-1)
            if end >= len(ruiseki):
                break
            if end+1 < len(ruiseki):
                # 後ろが"1"のとき
                end += 1

            ans = max(ruiseki[end]-ruiseki[i-2], ans)

    else:
        for i in range(1, len(ruiseki), 2):
            end = i + 2*(K-1)
            if end >= len(ruiseki):
                break
            if end+1 < len(ruiseki):
                end += 1

            if i-2 >= 0:              
                ans = max(ruiseki[end]-ruiseki[i-2], ans)
            else:
                ans = max(ruiseki[end]-ruiseki[i-1], ans)

    print(ans)            




if __name__ == "__main__":
    solve()