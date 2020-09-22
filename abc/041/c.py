# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    A = list(map(int, input().split()))
    students = []

    for i in range(0, len(A)):
        students.append((i+1, A[i]))
    
    for student in sorted(students, key=lambda x: x[1], reverse=True):
        print(student[0])


if __name__ == "__main__":
    solve()
