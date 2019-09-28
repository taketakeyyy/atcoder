# -*- coding:utf-8 -*-

class Student:
    def __init__(self, id, toukou):
        self.id = id
        self.toukou = toukou


def solve():
    N = int(input())
    As = list(map(int, input().split()))
    ans = []
    for i, a in enumerate(As):
        ans.append(Student(i+1, a))

    ans.sort(key=lambda x: x.toukou)

    ans1 = []
    for student in ans:
        ans1.append(student.id)

    print(*ans1)


if __name__ == "__main__":
    solve()
