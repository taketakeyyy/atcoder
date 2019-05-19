# -*- coding:utf-8 -*-

def is_YY(s):
    if int(s) >= 0 and int(s) <= 99:
        return True
    return False

def is_MM(s):
    if int(s) >= 1 and int(s) <= 12:
        return True
    return False

def solve():
    S = input()
    upper = S[0:2]
    lower = S[2:]
    if is_YY(upper) and is_MM(lower):
        if is_YY(lower) and is_MM(upper):
            print("AMBIGUOUS")
            return
        print("YYMM")
    elif is_YY(lower) and is_MM(upper):
        print("MMYY")
    else:
        print("NA")


if __name__ == "__main__":
    solve()
