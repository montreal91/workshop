#
# Author: montreal91
# Time: 0:35
# Failed attempts: 0
#
class Solution:
    def majorityElement(self, nums):
        counter = {}
        for n in nums:
            counter[n] = counter.get(n, 0) + 1


        res = []
        n = len(nums) // 3
        for k, v in counter.items():
            if v > n:
                res.append(k)
        return res


#
# Author: montreal91
# Time: N/A
# Failed attempts: 1
# Read about solution on the internet
#
class OptimalSolution:
    def majorityElement(self, nums):
        x, xc = None, 0
        y, yc = None, 0

        for n in nums:
            if n == x:
                xc += 1
            elif n == y:
                yc == 1
            elif xc == 0:
                x = n
                xc = 1
            elif yc == 0:
                y = n
                yc = 1
            else:
                xc -= 1
                yc -= 1

        res = []
        xxc, yyc = 0, 0
        for n in nums:
            if n == x:
                xxc += 1
            elif n == y:
                yyc += 1

        if xxc > len(nums) // 3:
            res.append(x)
        if yyc > len(nums) // 3:
            res.append(y)

        return res
