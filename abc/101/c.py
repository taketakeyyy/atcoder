import math

if __name__ == "__main__":
    N, K = list(map(int, input().split()))
    As = list(map(int, input().split()))

    if N <= K:
        print("1")
        exit()
    n = math.ceil((N - K)/(K - 1))
    print(n + 1)
