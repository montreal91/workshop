#
# Author: montreal91
# Solved in 1:11
# Failed attempts: 1
# Freaking zeroes!
#


def two_sum(nums, target, ignore_ind):
    board = {}
    answers = {}

    for i, n in enumerate(nums):
        if i == ignore_ind:
            continue
        if target - n in board:
            answers[n] = target - n
        board[n] = i

    return [list(v) for v in answers.items()]


def three_sum(nums):
    answers = set()
    for i, n in enumerate(nums):
        tmp = two_sum(nums, -n, i)
        answers.update([tuple(sorted(t + [n])) for t in tmp])
    return list(answers)


if __name__ == '__main__':
    print(three_sum([0, 0, 0]))