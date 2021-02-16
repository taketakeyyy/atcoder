# -*- coding:utf-8 -*-

def solve():
    B, C = list(map(int, input().split()))

    ans = 0
    if C == 0:
        print(1)
        return

    # 0方向を探索
    if B > 0:
        n = C//2
        amari = C%2
        if B-n > 0:
            if amari == 1:
                ans += (n+1)*2
            else:
                ans += (n+1)*2 - 1
        elif B-n == 0:
            ans += (n+1)*2-1
        else:
            # OK
            ans += B*2+1
    elif B < 0:
        n = (C-1)//2
        amari = (C-1)%2
        if abs(B)-n > 0:
            if amari == 1:
                ans += (n+1)*2
            else:
                ans += (n+1)*2 - 1
        elif abs(B)-n == 0:
            ans += (n+1)*2-1
        else:
            ans += abs(B)*2+1
    else:
        ans += 1

    # +方向を探索
    if B > 0:
        n = (C-1)//2
        amari = (C-1)%2
    elif B < 0:
        n = C//2
        amari = C%2
    else:
        n = C//2
        amari = C%2

    if amari == 1:
        # OK
        ans += n*2
    else:
        # OK
        ans += max(n*2-1, 0)

    print(ans)





if __name__ == "__main__":
    solve()
