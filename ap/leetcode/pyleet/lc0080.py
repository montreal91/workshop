
class Solution:
    def removeDuplicates(self, nums):
        writer = 0
        res_count = 0
        count = 0
        for reader in range(len(nums)):
            if nums[reader - 1] != nums[reader]:
                nums[writer] = nums[reader]
                writer += 1
                res_count += 1
                count = 1
            elif nums[reader - 1] == nums[reader] and count < 2:
                nums[writer] = nums[reader]
                writer += 1
                res_count += 1
                count += 1
            else:
                count += 1

        for i in range(writer, len(nums)):
            nums[i] = -1
        return res_count


# 3:15
# 3:50
if __name__ == "__main__":
    a1 = [1, 1, 1, 2, 2, 3]
    assert Solution().removeDuplicates(a1) == 5
    assert a1 == [1, 1, 2, 2, 3, -1]

    a2 = [1, 1, 1, 2, 3, 3]
    assert Solution().removeDuplicates(a2) == 5
    assert a2 == [1, 1, 2, 3, 3, -1]

    a3 = [0,0,1,1,1,1,2,3,3]
    assert Solution().removeDuplicates(a3) == 7
    assert a3 == [0,0,1,1,2,3,3,-1,-1]

    a4 = [1, 2, 3, 3, 3, 3]
    assert Solution().removeDuplicates(a4) == 4
    assert a4 == [1, 2, 3, 3, -1, -1]

    a5 = [1, 1, 1, 1, 1, 1]
    assert Solution().removeDuplicates(a5) == 2
    assert a5 == [1, 1, -1, -1, -1, -1]

    a6 = [1, 2]
    assert Solution().removeDuplicates(a6) == 2
    assert a6 == [1, 2]

    a7 = [1, 1, 2, 2]
    assert Solution().removeDuplicates(a7) == 4
    assert a7 == [1, 1, 2, 2]

    print("All tests passed.")
