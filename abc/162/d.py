# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    S = input()

    Rnum = [0 for _ in range(N)]  # Rnum[i] := i以降の右側に何個Rがあるか？（i含む）
    Gnum = [0 for _ in range(N)]
    Bnum = [0 for _ in range(N)]

    if S[N-1] == "R":
        Rnum[N-1] = 1
    elif S[N-1] == "G":
        Gnum[N-1] = 1
    else:
        Bnum[N-1] = 1
    for i in range(N-2, -1, -1):
        if S[i] == "R":
            Rnum[i] = Rnum[i+1] + 1
            Gnum[i] = Gnum[i+1]
            Bnum[i] = Bnum[i+1]
        elif S[i] == "G":
            Rnum[i] = Rnum[i+1]
            Gnum[i] = Gnum[i+1] + 1
            Bnum[i] = Bnum[i+1]
        else:
            Rnum[i] = Rnum[i+1]
            Gnum[i] = Gnum[i+1]
            Bnum[i] = Bnum[i+1] + 1

    ans = 0
    for i in range(N-2):
        for j in range(i+1, N-1):
            if S[i]=="R" and S[j]=="G":
                ans += Bnum[j+1]
                if j+(j-i)<N:
                    if S[j+(j-i)] == "B":
                        ans -= 1
            elif S[i]=="R" and S[j]=="B":
                ans += Gnum[j+1]
                if j+(j-i)<N:
                    if S[j+(j-i)] == "G":
                        ans -= 1
            elif S[i]=="G" and S[j]=="R":
                ans += Bnum[j+1]
                if j+(j-i)<N:
                    if S[j+(j-i)] == "B":
                        ans -= 1
            elif S[i]=="G" and S[j]=="B":
                ans += Rnum[j+1]
                if j+(j-i)<N:
                    if S[j+(j-i)] == "R":
                        ans -= 1
            elif S[i]=="B" and S[j]=="R":
                ans += Gnum[j+1]
                if j+(j-i)<N:
                    if S[j+(j-i)] == "G":
                        ans -= 1
            elif S[i]=="B" and S[j]=="G":
                ans += Rnum[j+1]
                if j+(j-i)<N:
                    if S[j+(j-i)] == "R":
                        ans -= 1

    print(ans)


if __name__ == "__main__":
    solve()
