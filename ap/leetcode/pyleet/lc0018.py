class Solution:
    def fourSum(self, nums, target):
        ind_res = set()
        for i in range(len(nums)):
            for j in range(i+1, len(nums)):
                doublets = self.twoSum(nums, target - nums[i] - nums[j])
                for d in doublets:
                    if i in d or j in d:
                        continue
                    q = tuple(sorted([nums[i], nums[j], nums[d[0]], nums[d[1]]]))
                    ind_res.add(q)
        return list(ind_res)


    def twoSum(self, nums, target):
        res = []
        ind = {}
        for i, n in enumerate(nums):
            if target - n in ind:
                res.append([ind[target-n], i])
            else:
                ind[n] = i

        return res

