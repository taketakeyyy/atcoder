# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    As = list(map(int, input().split()))

    # 降順にぶちこむ人を選んでいく。
    # 実際に手で書けばわかるが、ある数がn個あるとき、
    # n*2回心地よさを感じるようになる。
    # ただし、最初の1個目だけは心地よさ0なので、そこを考慮する
    dic = {}
    for a in As:
        if not a in dic: dic[a] = 0
        dic[a] += 1

    keys = []
    for key in dic.keys():
        keys.append(key)
    keys.sort(reverse=True)

    ans = 0
    n = N - 1
    dic[keys[0]] -= 1
    ans += keys[0]
    n -= 1

    for i, key in enumerate(keys):
        if dic[key] == 0:
            continue

        if (dic[key]*2) <= n:
            ans += key*(dic[key]*2)
            n -= dic[key]*2
        else:
            ans += key*n
            n -= n
            break

    print(ans)


if __name__ == "__main__":
    solve()
