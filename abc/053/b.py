# -*- coding:utf-8 -*-

def solve():
    s = input()

    for i in range(len(s)):
        if s[i] == "A":
            a_i = i
            break
    
    for i in range(len(s)-1, -1, -1):
        if s[i] == "Z":
            z_i = i
            break

    print(len(s[a_i:z_i+1]))

if __name__ == "__main__":
    solve()
