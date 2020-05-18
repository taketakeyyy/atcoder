# -*- coding:utf-8 -*-

def solve():
    import sys

    N, K = list(map(int, sys.stdin.readline().split()))
    As = [-1] + list(map(int, sys.stdin.readline().split()))

    now = 1
    dic = {1:0}
    turns = [1]
    for i in range(1, N+1):
        nx = As[now]
        turns.append(nx)

        if not nx in dic:
            dic[nx] = i
            now = nx

            if i == K:
                print(now)
                return

            continue
        else:
            # サイクルが存在している
            cycle_num = i - dic[nx]  # 再度同じところに戻ってくるのにかかるテレポーテーションの回数
            k = (K-i)%cycle_num
            cycle_turns = turns[dic[nx]:i]
            print(cycle_turns[k])
            return


if __name__ == "__main__":
    solve()
