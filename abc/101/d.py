
def eval_sn(n):
    s = str(n)
    ans = 0
    for i in s:
        ans += int(i)
    return n/ans

if __name__ == "__main__":
    K = int(input())
    n = 0
    Sn = [0] # 添字0は便宜上埋めておく
    RANGE_ = 100
    while n != RANGE_:
        n += 1
        Sn.append(eval_sn(n))

    while K != 0:
        n += 1
        #
        Sn.append(eval_sn(n))
        check = 0
        for j in range(RANGE_):
            if (Sn[n-RANGE_] <= Sn[n-j]):
                check += 1
                continue
            else:
                break
        if check == RANGE_:
            K -= 1
            print(n-RANGE_)
