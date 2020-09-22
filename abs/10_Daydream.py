#-*- coding:utf-8 -*-

if __name__ == "__main__":
    S = input()
    while len(S) != 0:
        if S.endswith("dream"):
            S = S[:-5]
        elif S.endswith("dreamer"):
            S = S[:-7]
        elif S.endswith("erase"):
            S = S[:-5]
        elif S.endswith("eraser"):
            S = S[:-6]
        else:
            print("NO")
            exit()
    print("YES")
