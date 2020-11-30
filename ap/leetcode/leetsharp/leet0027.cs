//
// Problem: https://leetcode.com/problems/remove-element/
// Author: montreal91
// Solved in 1:05
//
using System;


namespace leetsharp {


class Solution0027 {
  class Generator {
    private int[] nums;
    private int returnedValues = 0;
    private int ptr = -1;
    private int val;

    public Generator(int[] nums, int val) {
      this.nums = nums;
      this.val = val;
      UpdatePtr();

    }

    public int GetReturnedValues() {
      return returnedValues;
    }

    public int NextValue() {
      if (ptr >= nums.Length) {
        return val;
      }
      var res = nums[ptr];
      UpdatePtr();
      returnedValues++;
      return res;
    }

    private void UpdatePtr() {
      while (true) {
        ptr++;
        if (ptr >= nums.Length || nums[ptr] != val) {
          break;
        }
      }
    }
  }

  public int RemoveElement(int[] nums, int val) {
    var gen = new Generator(nums, val);
    int i, nv;
    i = 0;
    nv = gen.NextValue();
    Console.WriteLine(nv);
    while (nv != val) {
      nums[i] = nv;
      i++;
      nv = gen.NextValue();
    }
    return gen.GetReturnedValues();
  }

  public static void TestSolution() {
    var test = new int[] {};
    var S = new Solution0027();
    var res = S.RemoveElement(test, 3);
    PrintSolution(test, res);
  }

  private static void PrintSolution(int[] nums, int n) {
    Console.WriteLine($"Resulted length: {n};");
    for (int i=0; i<n; i++) {
      Console.WriteLine(nums[i]);
    }
  }
}


} // namespace leetsharp
