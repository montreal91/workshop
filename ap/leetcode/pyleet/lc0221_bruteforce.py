
#
# Author: montreal91
# Solved N/A
# Failed attempts: 0
#

class Solution:
    def maximalSquare(self, matrix):
        slv = _Solver(matrix)
        best = 0
        for i, row in enumerate(matrix):
            for j, _ in enumerate(row):
                best = max(best, slv.get_best_square(i, j))
        return best


class _Solver:
    def __init__(this, matrix):
        this._summatrix = _get_summatrix(matrix)
    
    def get_best_square(this, i, j):
        height = len(this._summatrix)
        width = len(this._summatrix[0])
        tl = (i, j)
        res = 0
        for k in range(min(height - i, width - j)):
            br = (i + k, j + k)
            t = this._get_sum_rect(tl=tl, br=br)
            if t == (k + 1) ** 2:
                res = t
                continue
            else:
                break
        return res

    def _get_sum(this, i, j):
        if not i in range(len(this._summatrix)) or not j in range(len(this._summatrix[0])):
            return 0
        return this._summatrix[i][j]
    
    def _get_sum_rect(this, tl, br):
        return (
            + this._get_sum(br[0], br[1])
            - this._get_sum(tl[0] - 1, br[1])
            - this._get_sum(br[0], tl[1] - 1)
            + this._get_sum(tl[0] - 1, tl[1] - 1)
        )

def _get_summatrix(matrix):
    vals = {"0": 0, "1": 1}
    tmp = [None for _ in enumerate(matrix)]
    prev_row = tuple(0 for _ in enumerate(matrix[0]))
    for i, row in enumerate(matrix):
        row = tuple(vals[v] for _, v in enumerate(row))
        rowsum = tuple(sum(row[0: i+1]) for i, _ in enumerate(row))
        newrow = tuple(prev_row[j] + rowsum[j] for j, _ in enumerate(rowsum))
        prev_row = newrow
        tmp[i] = newrow
    return tuple(tmp)


lc_matrix0 = [["0"]]
my_matrix0 = [["1"]]

lc_matrix1 = [
    ["0","1"],
    ["1","0"]
]

my_matrix1 = [
    ["0","1"],
    ["1","1"]
]

my_matrix2 = [
    ["1","1"],
    ["1","1"]
]

lc_matrix2 = [
    ["1","0","1","0","0"],
    ["1","0","1","1","1"],
    ["1","1","1","1","1"],
    ["1","0","0","1","0"]
]

my_matrix3 = [
    ["1", "1", "0"],
    ["1", "1", "0"],
    ["1", "1", "1"],
    ["1", "1", "1"],
    ["1", "1", "1"],
    ["1", "1", "0"],
]

def _gen_big_matrix(n, m):
    res = []


if __name__ == "__main__":
    s = Solution()

    assert s.maximalSquare(matrix=lc_matrix0) == 0
    assert s.maximalSquare(matrix=lc_matrix1) == 1
    assert s.maximalSquare(matrix=lc_matrix2) == 4
    assert s.maximalSquare(matrix=my_matrix0) == 1
    assert s.maximalSquare(matrix=my_matrix1) == 1
    assert s.maximalSquare(matrix=my_matrix2) == 4
    assert s.maximalSquare(matrix=my_matrix3) == 9

    print("All tests passed")
