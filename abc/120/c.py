# -*- coding:utf-8 -*-

def solve():
    S = input()

    ans = 0
    i = 0
    while i != len(S):
        if i+1 >= len(S):
            break

        if S[i] != S[i+1]:
            # 消す
            if i == 0:
                if len(S) <= 2:
                    ans += 1
                    S = ""
                    continue
                else:
                    ans += 1
                    S = S[2:]
                    continue
            else:
                if i+2 < len(S):
                    ans += 1
                    S = S[:i] + S[i+2:]
                    i -= 1
                    continue
                else:
                    ans += 1
                    S = S[:i]
                    i -= 1
                    continue
            
        i += 1
    print(ans*2)


if __name__ == "__main__":
    solve()
    