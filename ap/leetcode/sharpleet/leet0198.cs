//
// Problem: https://leetcode.com/problems/house-robber/
// Author: montreal91
// Solved in 0:48
// Failed attempts: 1
//

using System;
using System.Diagnostics;


namespace leetsharp {


class Solution0198 {
  public int Rob(int[] nums) {
    if (nums.Length == 0) {
      return 0;
    }
    if (nums.Length == 1) {
      return nums[0];
    }
    int[] D = new int[nums.Length];
    int i;
    for (i=0; i<nums.Length; i++) {
      if (i == 0) {
        D[i] = nums[i];
        continue;
      }
      if (i == 1) {
        D[i] = Math.Max(nums[i-1], nums[i]);
        continue;
      }
      D[i] = Math.Max(D[i-2] + nums[i], D[i-1]);
    }
    Console.WriteLine($"Answer: {D[D.Length - 1]}");
    return D[D.Length - 1];
  }

  public static void TestSolution() {
    var leet1 = new int[] {1,2,3,1};
    var leet2 = new int[] {2,7,9,3,1};
    var empty = new int[] {};
    var short1 = new int[] {10};
    var short2 = new int[] {10, 20};
    var short3 = new int[] {20, 10};
    var ladder = new int[] {1, 2, 3, 4, 5, 6};
    var wrong1 = new int[] {2,1,1,2};
    var case1 = new int[] {1, 2, 3, 4, 1, 1, 4};
    var case2 = new int[] {1, 2, 2, 1};

    var S = new Solution0198();
    Debug.Assert(S.Rob(leet1) == 4);
    Debug.Assert(S.Rob(leet2) == 12);
    Debug.Assert(S.Rob(empty) == 0);
    Debug.Assert(S.Rob(short1) == 10);
    Debug.Assert(S.Rob(short2) == 20);
    Debug.Assert(S.Rob(short3) == 20);
    Debug.Assert(S.Rob(ladder) == 12);
    Debug.Assert(S.Rob(wrong1) == 4);
    Debug.Assert(S.Rob(case1) == 10);
    Debug.Assert(S.Rob(case2) == 3);
    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
