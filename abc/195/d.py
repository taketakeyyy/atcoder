# -*- coding:utf-8 -*-

def solve():
    N, M, Q = list(map(int, input().split()))
    bags = []
    for _ in range(N):
        W, V = list(map(int, input().split()))
        bags.append((V,W))
    bags.sort(key=lambda x: x[1], reverse=True)
    bags.sort(key=lambda x: x[0], reverse=True)

    X = list(map(int, input().split()))
    for _ in range(Q):
        l, r = list(map(int, input().split()))
        l-=1
        r-=1
        newX = []
        for m in range(M):
            if l<=m<=r: continue
            newX.append(X[m])
        newX.sort()

        ans = 0
        used = set()
        for i in range(0, len(newX)):
            for j in range(0, len(bags)):
                if j in used: continue

                v, w = bags[j]
                if newX[i] >= w:
                    ans += v
                    used.add(j)
                    break
        print(ans)


if __name__ == "__main__":
    solve()
