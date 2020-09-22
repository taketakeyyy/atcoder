# -*- coding:utf-8 -*-

def solve():
    S = input()
    S = list(S)
    S.sort()

    # 重複した文字を削除する
    import copy
    tmpS = copy.deepcopy(S)
    S = []
    S.append(tmpS[0])
    for i in range(1, len(tmpS)):
        if S[-1] == tmpS[i]:
            continue
        S.append(tmpS[i])

    ans = "a"
    for moji in S:
        if ans == moji:
            ans = chr(ord(ans)+1)
            continue
        
        break
    if ans == "{":
        print("None")
    else:
        print(ans)


if __name__ == "__main__":
    solve()
