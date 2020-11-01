# -*- coding:utf-8 -*-
import copy

def solve():
    # 下３桁が8の倍数かみればいいらしい
    S = input()
    dic = {}
    for moji in S:
        if not int(moji) in dic:
            dic[int(moji)] = 0
        dic[int(moji)] += 1

    if len(S) <= 1:
        if int(S)%8==0:
            print("Yes")
        else:
            print("No")
        return

    if len(S) <= 2:
        a = int(S[0])*10 + int(S[1])
        b = int(S[1])*10 + int(S[0])
        if a%8==0 or b%8==0:
            print("Yes")
        else:
            print("No")
        return

    # 3桁の数字を全探索
    for i in range(1,10):
        for j in range(1,10):
            for k in range(1,10):
                if (i*100+j*10+k)%8 == 0:
                    tmpdic = copy.deepcopy(dic)
                    try:
                        tmpdic[i]-=1
                        tmpdic[j]-=1
                        tmpdic[k]-=1
                    except:
                        continue
                    if tmpdic[i]>=0 and tmpdic[j]>=0 and tmpdic[k]>=0:
                        print("Yes")
                        return
    print("No")


if __name__ == "__main__":
    solve()
