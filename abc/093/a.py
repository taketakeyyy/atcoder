#-*- coding:utf-8 -*-

if __name__ == "__main__":
    S = input()
    is_a = False
    is_b = False
    is_c = False

    for i in range(3):
        if S[i] == "a":
            is_a = True
            continue
        elif S[i] == "b":
            is_b = True
            continue
        elif S[i] == "c":
            is_c = True
            continue

    if is_a and is_b and is_c:
        print("Yes")
    else:
        print("No")
