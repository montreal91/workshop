# 05:05
# time
from collections import deque


square_0_0 = (
    (0, 0), (0, 1), (0, 2),
    (1, 0), (1, 1), (1, 2),
    (2, 0), (2, 1), (2, 2),
)

square_0_1 = (
    (0, 3), (0, 4), (0, 5),
    (1, 3), (1, 4), (1, 5),
    (2, 3), (2, 4), (2, 5),
)

square_0_2 = (
    (0, 6), (0, 7), (0, 8),
    (1, 6), (1, 7), (1, 8),
    (2, 6), (2, 7), (2, 8),
)

square_1_0 = (
    (3, 0), (3, 1), (3, 2),
    (4, 0), (4, 1), (4, 2),
    (5, 0), (5, 1), (5, 2),
)
square_1_1 = (
    (3, 3), (3, 4), (3, 5),
    (4, 3), (4, 4), (4, 5),
    (5, 3), (5, 4), (5, 5),
)
square_1_2 = (
    (3, 6), (3, 7), (3, 8),
    (4, 6), (4, 7), (4, 8),
    (5, 6), (5, 7), (5, 8),
)

square_2_0 = (
    (6, 0), (6, 1), (6, 2),
    (7, 0), (7, 1), (7, 2),
    (8, 0), (8, 1), (8, 2),
)
square_2_1 = (
    (6, 3), (6, 4), (6, 5),
    (7, 3), (7, 4), (7, 5),
    (8, 3), (8, 4), (8, 5),
)
square_2_2 = (
    (6, 6), (6, 7), (6, 8),
    (7, 6), (7, 7), (7, 8),
    (8, 6), (8, 7), (8, 8),
)

GRID = (
    (square_0_0, square_0_0, square_0_0, square_0_1, square_0_1, square_0_1, square_0_2, square_0_2, square_0_2),
    (square_0_0, square_0_0, square_0_0, square_0_1, square_0_1, square_0_1, square_0_2, square_0_2, square_0_2),
    (square_0_0, square_0_0, square_0_0, square_0_1, square_0_1, square_0_1, square_0_2, square_0_2, square_0_2),
    (square_1_0, square_1_0, square_1_0, square_1_1, square_1_1, square_1_1, square_1_2, square_1_2, square_1_2),
    (square_1_0, square_1_0, square_1_0, square_1_1, square_1_1, square_1_1, square_1_2, square_1_2, square_1_2),
    (square_1_0, square_1_0, square_1_0, square_1_1, square_1_1, square_1_1, square_1_2, square_1_2, square_1_2),
    (square_2_0, square_2_0, square_2_0, square_2_1, square_2_1, square_2_1, square_2_2, square_2_2, square_2_2),
    (square_2_0, square_2_0, square_2_0, square_2_1, square_2_1, square_2_1, square_2_2, square_2_2, square_2_2),
    (square_2_0, square_2_0, square_2_0, square_2_1, square_2_1, square_2_1, square_2_2, square_2_2, square_2_2),
)


class SudokuTracker:
    def __init__(self, board):
        # print(board)
        self._board = [[c for c in line] for line in board]
        self._made_moves_stack = []
        self._possible_moves_stack = []

        for i in range(9):
            for j in range(9):
                print(self._board[i][j], end="")
            print()

    def solve(self):
        for i in range(9):
            for j in range(9):
                self._possible_moves_stack.extend(self._get_possible_moves(i, j))

        while self._possible_moves_stack:
            pass


    def _get_square_by_coordinate(self, i, j):
        return GRID[i][j]

    def _get_row_by_coordinate(self, i, j):
        return tuple((i, k) for k in range(9))

    def _get_column_by_coordinate(self, i, j):
        return tuple((k, j) for k in range(9))

    def _get_all_by_coordinate(self, i, j):
        res = []
        res += list(self._get_row_by_coordinate(i, j))
        res += list(self._get_column_by_coordinate(i, j))
        res += list(self._get_square_by_coordinate(i, j))
        return res

    def _get_initial_set(self):
        return set(str(i) for i in range(1, 10))

    def _make_move(self, i, j, num):
        self._board[i][j] = num
        self._made_moves_stack.append((i, j, num))

    def _undo_last_move(self):
        i, j, _ = self._made_moves_stack.pop()
        self._board[i][j] = "."

    def _get_possible_moves(self, i, j):
        if self._board[i][j] != ".":
            return []

        res = self._get_initial_set()

        for m, k in self._get_all_by_coordinate(i, j):
            if self._board[m][k] in res:
                res.remove(self._board[m][k])

        return list(res)



class Solution:
    def solveSudoku(self, board):
        """
        Do not return anything, modify board in-place instead.
        """
        tracker = SudokuTracker(board=board)



b1 = [
    ["5","3",".",".","7",".",".",".","."],
    ["6",".",".","1","9","5",".",".","."],
    [".","9","8",".",".",".",".","6","."],
    ["8",".",".",".","6",".",".",".","3"],
    ["4",".",".","8",".","3",".",".","1"],
    ["7",".",".",".","2",".",".",".","6"],
    [".","6",".",".",".",".","2","8","."],
    [".",".",".","4","1","9",".",".","5"],
    [".",".",".",".","8",".",".","7","9"],
]

b2 = [
    ["1","2","3","4","5","6","7","8","9"],
    ["7","8","9","1","2","3","4","5","6"],
    ["4","5","6","7","8","9","1","2","3"],
    ["3","2","1","6","4","5","9","7","8"],
    ["9","7","8","3","1","2","6","4","5"],
    ["6","4","5","9","7","8","3","1","2"],
    ["2","3","1","5","6","4","8","9","7"],
    ["8","9","7","2","3","1","5","6","4"],
    ["5","6","4","8","9","7","2","3","1"]
]

b3 = [
    ["1","2","3","4","5","6","7","8","9"],
    ["7","8","9","1","2","3","4","5","6"],
    ["4","5","6","7","8","9","1","2","3"],
    ["3","2","1","6","4","5","9","7","8"],
    ["9","7","8","3",".","2","6","4","5"],
    ["6","4","5","9","7","8","3","1","2"],
    ["2","3","1","5","6","4","8","9","7"],
    ["8","9","7","2","3","1","5","6","4"],
    ["5","6","4","8","9","7","2","3","1"]
]

my_answer = [
    ["1","2","3","4","5","6","7","8","9"],
    ["7","8","9","1","2","3","4","5","6"],
    ["4","5","6","7","8","9","1","2","3"],
    ["3","2","1","6","4","5","9","7","8"],
    ["9","7","8","3","1","2","6","4","5"],
    ["6","4","5","9","7","8","3","1","2"],
    ["2","3","1","5","6","4","8","9","7"],
    ["8","9","7","2","3","1","5","6","4"],
    ["5","6","4","8","9","7","2","3","1"]
]

if __name__ == "__main__":
    Solution().solveSudoku(b3)
    assert b3 == my_answer

    print("All tests passed.")
