# -*- coding:utf-8 -*-

class Tree:
    def __init__(self):
        self.persons = {}    # self.persons[i] := 社員番号iの人が持っている直属の部下（リスト）
        self.persons[1] = []

    def add(self, boss, _id):
        if not boss in self.persons:
            self.persons[boss] = []
        if not _id in self.persons:
            self.persons[_id] = []
        self.persons[boss].append(_id)

    def calc(self):
        """親を計算する"""

        def dfs(now):
            """再帰的にnowの部下の給与を計算する"""
            if len(self.persons[now]) == 0:
                return 1

            buka_kyuyo = []
            while True:
                if len(self.persons[now]) == 0: break

                _id = self.persons[now].pop(-1)

                kyuyo = dfs(_id)
                buka_kyuyo.append(kyuyo)

            return max(buka_kyuyo) + min(buka_kyuyo) + 1

        return dfs(1)


def solve():
    N = int(input())
    tree = Tree()
    for i in range(N-1):
        b = int(input())
        tree.add(b, i+2)
    ans = tree.calc()
    print(ans)

if __name__ == "__main__":
    solve()
