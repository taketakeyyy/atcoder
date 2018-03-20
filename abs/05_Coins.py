#-*- coding:utf-8 -*-

if __name__ == "__main__":
    A = int(input())
    B = int(input())
    C = int(input())
    X = int(input())

    ans = 0
    for i in range(A+1):
        for j in range(B+1):
            for k in range(C+1):
                money = 500*i + 100*j + 50*k
                if money == X:
                    ans += 1
                    break
                elif money > X:
                    break
    print(ans)
