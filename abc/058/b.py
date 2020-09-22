# -*- coding:utf-8 -*-

def solve():
    O = input()
    E = input()

    ans = ""
    for i in range(len(O)):
        ans += O[i]
        if i >= len(E):
            continue
        ans += E[i]
    
    print(ans)

if __name__ == "__main__":
    solve()
