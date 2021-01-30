# -*- coding:utf-8 -*-

def dividor(n):
    ans = []
    i = 1
    while True:
        if i*i > n: break
        m = n%i
        if m==0:
            ans.append(i)
            if not n//i in ans:
                ans.append(n//i)
        i += 1
    return ans


def solve():
    N = int(input())
    ans = 0

    divs = dividor(2*N)
    divs.sort()

    for i in range(len(divs)):
        A, B = divs[-i-1], divs[i]
        if B>A: break

        """
        A = a+b
        B = b-a+1
        をそれぞれ満たすか？
        すなわち式変形して、
        B+A-1 = 2bを満たすか？
        つまりB+A-1は偶数か？
        """
        if (B+A-1)&1==0:
            ans += 2

    print(ans)


if __name__ == "__main__":
    solve()
