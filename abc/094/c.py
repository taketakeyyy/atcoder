# -*- coding:utf-8 -*-

def solver():
    # mr.zehnpaard
    from statistics import median_low, median_high

    n = int(input())
    xs = [int(x) for x in input().split()]

    m1, m2 = median_low(xs), median_high(xs)

    medians = (str(m2 if x < m2 else m1) for x in xs)
    print('\n'.join(medians))

def main():
    from statistics import median_low, median_high

    N = int(input())
    Xs = list(map(int, input().split()))
    m_low, m_high = median_low(Xs), median_high(Xs)

    for x in Xs:
        ans = m_high if x <= m_low else m_low
        print(ans)


if __name__ == "__main__":
    main()
