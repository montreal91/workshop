#
# Author: montreal91
# Time: 2:15
# Failed attempts: 0
#

import unittest


class Solution:
    def generateParenthesis(self, n):
        self._solution_index = {}
        res = self._solve(n)

        return list(res)

    def _solve(self, n):
        if n in self._solution_index:
            return self._solution_index[n]

        if n == 1:
            self._solution_index[1] = set(["()"])
            return self._solution_index[n]

        prev_res = self._solve(n - 1)
        res = set()
        for p in prev_res:
            res.add("()" + p)
            res.add("(" + p + ")")
            res.add(p + "()")

        for i in range(1, n):
            prefix_res = self._solve(i)
            suffix_res = self._solve(n-i)

            for p in prefix_res:
                for s in suffix_res:
                    res.add(p + s)

        self._solution_index[n] = res
        return res


class SolutionTestCase(unittest.TestCase):
    def test_solution(self):
        self.assertEqual(
            sorted(Solution().generateParenthesis(1)), ["()"]
        )

        self.assertEqual(
            sorted(Solution().generateParenthesis(2)), ["(())", "()()"]
        )

        self.assertEqual(
            sorted(Solution().generateParenthesis(3)), ["((()))","(()())","(())()","()(())","()()()"]
        )

        self.assertEqual(
            sorted(Solution().generateParenthesis(4)),
            sorted([
                "(((())))","((()()))","((())())","((()))()","(()(()))","(()()())","(()())()",
                "(())(())","(())()()","()((()))","()(()())","()(())()","()()(())","()()()()"
            ])
        )



if __name__ == "__main__":
    unittest.main()
