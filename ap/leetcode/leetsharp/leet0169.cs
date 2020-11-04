
//
// Problem: https://leetcode.com/problems/majority-element/
// Author: montreal91
// Solved in 0:40
//

using System;
using System.Collections.Generic;
using System.Diagnostics;


namespace leetsharp {


class Solution169 {
  public int MajorityElement(int[] nums) {
    var multi_counter = new Dictionary<int, long>();

    foreach (int n in nums) {
      if (!multi_counter.ContainsKey(n)) {
        multi_counter.Add(n, 1);
      } else {
        multi_counter[n]++;
      }
      if (multi_counter[n] > nums.Length / 2) {
        return n;
      }
    }

    // This actually should never happen on valid input.
    Console.WriteLine(multi_counter[nums[0]]);
    return 0;
  }

  public static void TestSolution() {
    var s = new Solution169();

    Debug.Assert(s.MajorityElement(new int[]{1}) == 1);
    Debug.Assert(s.MajorityElement(new int[]{3, 2, 3}) == 3);
    Debug.Assert(s.MajorityElement(new int[]{2, 2, 1, 1, 1, 2, 2}) == 2);
    Debug.Assert(s.MajorityElement(new int[]{3, 3, 3}) == 3);
    Debug.Assert(s.MajorityElement(new int[]{4, 3, 4, 4}) == 4);
    Debug.Assert(s.MajorityElement(new int[]{5, 5, 5, 2, 2}) == 5);
    Debug.Assert(s.MajorityElement(new int[]{5, 5, 1, 5, 5}) == 5);
    Debug.Assert(s.MajorityElement(new int[]{1, 2, 6, 6, 6, 6}) == 6);

    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
