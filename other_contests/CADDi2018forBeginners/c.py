def solve():
    N, P = list(map(int, input().split()))

    if N== 1:
        print(P)
        return
    if P == 1:
        print(P)
        return

    p = 2
    ans = 1

    while True:
        if p >= P:
            break

        if N >= 40:
            break

        pn = p**N
        if pn > P or pn > 10**12:
            break

        while True:
            if P%pn == 0:
                P = (P/pn)
                ans *= p
            else:
                break

        p += 1

    print(ans)


if __name__ == "__main__":
    solve()
