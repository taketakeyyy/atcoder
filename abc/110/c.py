# -*- coding: utf-8 -*-

def main():
    """ TLE """
    S = input()
    T = input()

    if S == T:
        print("Yes")
        exit()

    # ある文字cがsとtで場所が半端に一致していたらNO
    len_s = len(S)
    for i in range(len_s):
        flag1 = False
        flag2 = False
        fuitti = []
        finds = []
        start_i = i
        while True:
            find_i = T.find(S[i], start_i)
            if find_i == -1:
                break
            finds.append(find_i)
            start_i = find_i
        # findsを走査
        for find in finds:
            if S[find] == T[find]:
                flag1 = True
            else:
                flag2 = True
                fuitti.append(find)
        if flag1 and flag2:
            for f in fuitti:
                find_f = T.find(S[f])
                if find_f != -1:
                    print("No")
                    exit()
    print("Yes")



def main3():
    """ TLE """
    S = input()
    T = input()

    if S == T:
        print("Yes")
        exit()

    # ある文字cがsとtで場所が半端に一致していたらNO
    ans = S
    len_s = len(S)
    for i in range(len_s):
        if ans[i] != T[i]:
            c1 = ans[i]
            c2 = T[i]
            ans = ans.replace(c1, "?")
            ans = ans.replace(c2, c1)
            ans = ans.replace("?", c2)

    if ans == T:
        print("Yes")
    else:
        print("No")


def main2():
    """ TLE WA """
    S = input()
    T = input()

    if S == T:
        print("Yes")
        exit()

    # ある文字cがsとtで場所が半端に一致していたらNO
    len_s = len(S)
    for i in range(len_s):
        if not S[i] in T:
            continue
        flag1 = False
        flag2 = False
        for j in range(len_s):
            if flag1 and flag2:
                print("No")
                exit()
            if S[i] == T[j]:
                if i == j:
                    flag1 = True
                    continue
                flag2 = True
                continue
    print("Yes")



if __name__ == '__main__':
    main()
