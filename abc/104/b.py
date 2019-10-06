# -*- coding: utf-8 -*-

if __name__ == "__main__":
    S = input()
    if S[0] != "A":
        print("WA")
        exit()

    count = 0
    for i in range(2, len(S)-1):
        if S[i] == "C":
            count += 1
            c_i = i
            continue
    if count != 1:
        print("WA")
        exit()

    for i in range(1, len(S)):
        if i == c_i:
            continue
        if not (97 <= ord(S[i]) and ord(S[i]) <= 122):
            print("WA")
            exit()

    print("AC")
