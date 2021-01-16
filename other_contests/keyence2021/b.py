# -*- coding:utf-8 -*-

def solve():
    N, K = list(map(int, input().split()))
    As = list(map(int, input().split()))
    dic = {}
    for a in As:
        if not a in dic:
            dic[a] = 0
        dic[a] += 1

    ans = 0
    k = K
    i = 0
    while True:
        if k == 0:
            break

        try:
            num = dic[i]
        except:
            num = 0

        if num-k >= 0:
            # すべて使える
            i += 1
            continue
        else:
            # 脱落したやつを足す
            ans += i*(k-num)
            # 脱落した個数を除く
            k += (num-k)
    print(ans)



if __name__ == "__main__":
    solve()
