# -*- coding:utf-8 -*-

def solve():
    import copy

    N, M, Q = list(map(int, input().split()))
    query = []
    for i in range(Q):
        a, b, c, d = list(map(int, input().split()))
        query.append((a,b,c,d))

    cands = []
    def rec(start, lst):
        if len(lst) == N:
            return lst

        for i in range(start, M+1):
            tmp_lst = copy.deepcopy(lst)
            tmp_lst.append(i)
            ret = rec(i, tmp_lst)
            if ret is not None:
                cands.append(ret)

    rec(1, [])

    ans = 0
    for cand in cands:
        total = 0
        for abcd in query:
            a,b,c,d = abcd
            if cand[b-1]-cand[a-1] == c:
                total += d
        ans = max(ans, total)

    print(ans)




if __name__ == "__main__":
    solve()
