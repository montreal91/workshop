
//
// Problem: https://leetcode.com/problems/palindrome-number/
// Author: montreal91
// Solved in 0:28
//

using System;
using System.Diagnostics;


namespace leetsharp {

class Solution0026 {
  public int RemoveDuplicates(int[] nums) {
    if (nums.Length == 0) {
      return 0;
    }
    int cursor = 0;
    for (int i=1; i<nums.Length; i++) {
      if (nums[cursor] != nums[i]) {
        cursor++;
        nums[cursor] = nums[i];
      }
    }
    return cursor + 1;
  }
  public static void TestSolution() {

    TestArrays(new int[]{}, new int[]{}, 0);
    TestArrays(new int[]{-100}, new int[]{-100}, 1);
    TestArrays(new int[]{-1, -1}, new int[]{-1}, 1);
    TestArrays(new int[]{1, 2, 3}, new int[]{1, 2, 3}, 3);
    TestArrays(new int[]{1, 1, 2, 3, 3, 3}, new int[]{1, 2, 3}, 3);
    Console.WriteLine("All tests passed.");
  }

  private static void TestArrays(int[] input, int[] expected, int expectedL) {
    var s = new Solution0026();
    var l = s.RemoveDuplicates(input);
    Debug.Assert(l == expectedL);
    Debug.Assert(CompareArrays(input, expected, l));
  }

  private static bool CompareArrays(int[] resulted, int[] expected, int nums) {
    if (resulted.Length < nums || expected.Length < nums) {
      return false;
    }

    for (int i=0; i<nums; i++) {
      if (resulted[i] != expected[i]) {
        return false;
      }
    }
    return true;
  }
}

} // namespace leetsharp
