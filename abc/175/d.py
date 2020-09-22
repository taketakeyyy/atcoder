# -*- coding:utf-8 -*-


def solve():
    N, K = list(map(int, input().split()))
    Ps = list(map(int, input().split()))
    Cs = list(map(int, input().split()))

    # 最低一回は移動させないといけないの忘れてた
    ans = -float("inf")
    for i in range(N):
        ans = max(ans, Cs[i])

    if K == 1:
        print(ans)
        return

    loop_list = []
    for start in range(N):
        now = start
        visited = set()
        visited.add(now)
        move = 0
        total_score = 0
        max_score = ans

        while True:  # たかだかN回
            nx = Ps[now]-1
            total_score += Cs[nx]
            max_score = max(max_score, total_score)
            move += 1
            now = nx
            if now in visited:
                # 一周した
                if total_score > 0:
                    # 一周する価値あるので、loop_listに追加
                    loop_list.append((start, total_score, move))
                break

            # 一周してない
            if move == K:
                # もう移動できないので終わり
                break
            visited.add(now)
        ans = max(ans, max_score)


    # 一周した方が得かつ、移動回数が余っているなら、ぐるぐる回る
    for start, score, move in loop_list:
        total_score = score*(K//move)
        restK = K % move
        max_score = total_score

        # K回目の最大値を探す
        now = start
        while restK != 0:
            restK -= 1
            nx = Ps[now]-1
            total_score += Cs[nx]
            max_score = max(max_score, total_score)
            now = nx
        ans = max(ans, max_score)

        # K-1回目の最大値を探す
        now = start
        total_score = score*(K//move) - score
        max_score -= total_score
        for i in range(move):
            nx = Ps[now]-1
            total_score += Cs[nx]
            max_score = max(max_score, total_score)
            now = nx
        ans = max(ans, max_score)

    print(ans)


if __name__ == "__main__":
    solve()
