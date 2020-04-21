# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    testimonies = []
    for n in range(N):
        A = int(input())
        XYs = []
        for a in range(A):
            x, y = list(map(int, input().split()))
            XYs.append((x-1, y))
        testimonies.append(XYs)

    # bit全探索する
    ans = 0
    for bit in range(2**N):
        is_continue = False
        total = 0
        # bitが1のやつが正直者と仮定する
        for i in range(N):
            if bit>>i&1:
                # iが正直者の場合
                total += 1
                for testimony in testimonies[i]:
                    x, y = testimony
                    if bit>>x&1 != y:
                        # 矛盾発生
                        is_continue = True
                        break
            if is_continue:
                break
        if is_continue:
            continue
        ans = max(ans, total)

    print(ans)



if __name__ == "__main__":
    solve()
