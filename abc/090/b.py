# -*- coding:utf-8 -*-

if __name__ == "__main__":
    A, B = list(map(int, list(map(float, input().split()))))
    ans = 0
    for i in range(A, B+1):
        c = str(i)
        length = len(c)
        if length%2 == 0:
            continue
        for j in range(length):
            if c[j] == c[length-1-j]:
                if j == length-1-j:
                    ans += 1
                    break
                continue
            else:
                break
    print(ans)
