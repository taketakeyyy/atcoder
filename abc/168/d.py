# -*- coding:utf-8 -*-

def solve():
    import sys
    from collections import deque

    N, M = list(map(int, sys.stdin.readline().split()))
    rooms = [None]*(N+1)
    for _ in range(M):
        A, B = list(map(int, sys.stdin.readline().split()))
        # A, B = A-1, B-1
        if rooms[A] is None:
            rooms[A] = []
        if rooms[B] is None:
            rooms[B] = []
        rooms[A].append(B)
        rooms[B].append(A)

    ans = [None] * (N+1)
    ans[0] = -1
    ans[1] = -1

    # 幅優先探索
    que = deque([1])
    while que:
        room = que.popleft()
        nrooms = rooms[room]
        # print(nrooms)
        # input()

        for nroom in nrooms:
            if ans[nroom] == None:
                ans[nroom] = room
                que.append(nroom)
            else:
                pass

    if None in ans:
        print("No")
        return
    print("Yes")
    for v in ans[2:]:
        print(v)


if __name__ == "__main__":
    solve()
