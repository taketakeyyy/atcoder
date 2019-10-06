# -*- coding:utf-8 -*-

def solve():
    N, D, K = list(map(int, input().split()))
    Ls, Rs = [], []
    for i in range(D):
        l, r = list(map(int, input().split()))
        Ls.append(l)
        Rs.append(r)
    Ss, Ts = [], []
    for i in range(K):
        s, t = list(map(int, input().split()))
        Ss.append(s)
        Ts.append(t)

    ans = [None for _ in range(K)]
    for d in range(D):
        for k in range(K):
            if Ss[k] == None: continue

            if Ls[d] <= Ss[k] <= Rs[d]:
                # 移動可能
                if Ss[k] <= Ts[k]:
                    # 目的地が右にあるときは...
                    if Ts[k] <= Rs[d]:
                        # 目的地に到着
                        ans[k] = d + 1
                        Ss[k] = None
                    else:
                        # できるだけ右に行く
                        Ss[k] = Rs[d]
                else:
                    # 目的地が左にあるときは...
                    if Ls[d] <= Ts[k]:
                        # 目的地に到着
                        ans[k] = d + 1
                        Ss[k] = None
                    else:
                        # できるだけ左に行く
                        Ss[k] = Ls[d]

    # 出力
    for i in range(K):
        print(ans[i])





if __name__ == "__main__":
    solve()
