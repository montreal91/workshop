//
// Problem: https://leetcode.com/problems/two-sum/
// Author: montreal91
// Solved in 0:26
// Failed attempts: 0
//
using System;
using System.Collections.Generic;


namespace leetsharp {


class Solution0001 {
  public int[] TwoSum(int[] nums, int target) {
    var dict = new Dictionary<int, List<int>>();
    for (int i=0; i<nums.Length; i++) {
      if (dict.ContainsKey(nums[i])) {
        dict[nums[i]].Add(i);
      }
      else {
        dict[nums[i]] = new List<int>{i};
      }
    }

    int key;
    foreach (var entry in dict) {
      key = entry.Key;
      if (key * 2 == target) {
        if (dict[key].Count > 1) {
          return dict[key].ToArray();
        }
      }
      if (dict.ContainsKey(target - key)) {
        return new int[] {
          dict[key][0],
          dict[target - key][0]
        };
      }
    }
    return new int[]{};
  }
  public static void TestSolution() {
  }
}


} // namespace leetsharp
