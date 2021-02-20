# -*- coding:utf-8 -*-

def solve():
    S = input()
    flag = True
    for i, moji in enumerate(S):
        if i%2==0:
            # 奇数番目
            if 97 <= ord(moji) <= 122:
                pass
            else:
                flag = False
                break
        else:
            # 偶数番目
            if 65 <= ord(moji) <= 90:
                pass
            else:
                flag = False
                break

    if flag:
        print("Yes")
    else:
        print("No")

if __name__ == "__main__":
    solve()
