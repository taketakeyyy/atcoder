def gcd(a, b):
    """ 最大公約数。aはbより大きいこと """
    if b == 0:
        return a
    else:
        return gcd(b, a%b)


def solve():
    N = int(input())
    A = [int(x) for x in input().split(" ")]

    A.sort(reverse=True)
    ans = A[0]
    for i in range(1, N):
        ans = gcd(ans, A[i])

    print(ans)


if __name__ == "__main__":
    solve()