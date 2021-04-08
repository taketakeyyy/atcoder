# -*- coding:utf-8 -*-


def solve():
    MOD = 998244353
    N = int(input())
    D = list(map(int, input().split()))
    if D[0] != 0:
        print(0)
        return

    # 0 0 1 1 のようなありえないやつを落とす
    # 0 2 2 2 のようなありえないやつを落とす
    newD = sorted(D)
    now = 0
    zero_num = 0
    for i in range(len(newD)):
        if now == newD[i]:
            if now==0:
                zero_num += 1
                if zero_num >= 2:
                    print(0)
                    return
            continue
        if now+1 == newD[i]:
            now = now+1
            continue
        print(0)
        return

    # 遷移の個数を数え上げる
    mp = {}
    for d in D:
        if not d in mp:
            mp[d] = 0
        mp[d] += 1

    ans = 1
    for key, value in mp.items():
        if key==0: continue
        if key==1: continue
        ans *= pow(mp[key-1], mp[key], MOD)
        ans %= MOD
    print(ans)


if __name__ == "__main__":
    solve()
