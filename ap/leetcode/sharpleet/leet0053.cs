
//
// Problem: https://leetcode.com/problems/maximum-subarray/
// Author: montreal91
// Solved in 1:11
// Took too much time, but passed on first attempt.
//

using System;
using System.Diagnostics;


namespace leetsharp {


class Solution0053 {
  public int MaxSubArray(int[] nums) {
    var best = nums[0];
    var D = new int[nums.Length];
    D[0] = nums[0];

    for (int i=1; i<nums.Length; i++) {
      D[i] = Math.Max(nums[i], D[i-1] + nums[i]);
      best = Math.Max(best, D[i]);
    }
    return best;
  }

  public static void TestSolution() {
    var empty = new int[]{}; // invalid case
    var singleton = new int[] {256};
    var shortTwo9 = new int[] {4, 5};
    var shortTwoNeg4 = new int[] {-4, -5};
    var shortTwo4 = new int[] {4, -5};
    var shortTwo5 = new int[] {-4, 5};
    var myTest11 = new int[]{
      1, -1, -1, 3, -1, 2, -2, -1, 1, 2, 3, -1, 5, -1, -1
    };
    var leet6 = new int[]{-2,1,-3,4,-1,2,1,-5,4};

    var S = new Solution0053();

    Debug.Assert(S.MaxSubArray(singleton) == 256);
    Debug.Assert(S.MaxSubArray(myTest11) == 11);
    Debug.Assert(S.MaxSubArray(leet6) == 6);
    Debug.Assert(S.MaxSubArray(shortTwo9) == 9);
    Debug.Assert(S.MaxSubArray(shortTwoNeg4) == -4);
    Debug.Assert(S.MaxSubArray(shortTwo4) == 4);
    Debug.Assert(S.MaxSubArray(shortTwo5) == 5);
    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
