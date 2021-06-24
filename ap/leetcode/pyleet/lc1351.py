#
# Author: montreal91
# Time: 0:41
# Failed attempts: 0
#

class Solution:
    def countNegatives(self, grid):
        return sum(countNegativesInRow(row) for row in grid)


def countNegativesInRow(row):
    left = 0
    right = len(row) - 1

    while left < right:
        i = (left + right) // 2

        if row[i] >= 0:
            if i == right or row[i+1] < 0:
                return len(row) - i - 1
            left = i + 1

        else:
            if i == left or row[i-1] >= 0:
                return len(row) - i

            right = i - 1

    if row[left] < 0:
        return len(row) - left
    return 0



if __name__ == '__main__':
    assert countNegativesInRow([4, 3, 2, 1, 0]) == 0
    assert countNegativesInRow([4, 3, 2, 1, 0, -1]) == 1
    assert countNegativesInRow([4, 4, 3, 0, -1, -1]) == 2
    assert countNegativesInRow([4, 2, 1, -1, -2, -3]) == 3
    assert countNegativesInRow([1, 1, -1, -1, -2, -3]) == 4
    assert countNegativesInRow([1, -1, -2, -3, -3, -4]) == 5
    assert countNegativesInRow([-1, -1, -2, -2, -2, -3]) == 6

    assert countNegativesInRow([1, 1, 0, -1, -1, -2, -3]) == 4

    print("All tests passed.")
