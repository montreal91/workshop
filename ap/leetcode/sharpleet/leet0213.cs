//
// Problem: https://leetcode.com/problems/house-robber-ii/
// Author: montreal91
// Solved in 1:14
// Failed attempts: 0
//
using System;
using System.Collections.Generic;
using System.Diagnostics;


namespace leetsharp {


class Solution0213 {
  public int Rob(int[] nums) {
    if (nums.Length == 1) {
      return nums[0];
    }
    if (nums.Length == 2) {
      return Math.Max(nums[0], nums[1]);
    }
    return Math.Max(LinRob(nums, true), LinRob(nums, false));
  }

  public static int LinRob(int[] nums, bool robFirst) {
    var D = new List<int>();
    int first, last;
    if (robFirst) {
      first = 0;
      last = nums.Length - 1;
    }
    else {
      first = 1;
      last = nums.Length;
    }
    if (!robFirst) {
      D.Add(0);
    }
    D.Add(nums[first]);
    D.Add(Math.Max(nums[first], nums[first + 1]));

    for (int i=first+2; i<last; i++) {
      D.Add(Math.Max(D[i-1], D[i-2] + nums[i]));
    }
    return D[D.Count - 1];
  }

  public static void TestSolution() {
    var S = new Solution0213();
    var leet1r0 = new int[]{2, 3, 2}; // 3
    var leet1r1 = new int[]{2, 2, 3};
    var leet1r2 = new int[]{3, 2, 2};

    var leet2r0 = new int[]{1, 2, 3, 1}; //4
    var leet2r1 = new int[]{1, 1, 2, 3};
    var leet2r2 = new int[]{3, 1, 1, 2};
    var leet2r3 = new int[]{2, 3, 1, 1};

    var corner2r0 = new int[]{5, 1}; // 5
    var corner2r1 = new int[]{1, 5};

    var corner1 = new int[]{5}; // 5

    var long1r0 = new int[]{6, 3, 9, 1, 8, 5}; // 23
    var long1r1 = new int[]{5, 6, 3, 9, 1, 8};
    var long1r2 = new int[]{8, 5, 6, 3, 9, 1};
    var long1r3 = new int[]{1, 8, 5, 6, 3, 9};
    var long1r4 = new int[]{9, 1, 8, 5, 6, 3};
    var long1r5 = new int[]{3, 9, 1, 8, 5, 6};

    var long2r0 = new int[]{1, 3, 9, 6, 8, 5}; // 18
    var long2r1 = new int[]{5, 1, 3, 9, 6, 8};
    var long2r2 = new int[]{8, 5, 1, 3, 9, 6};
    var long2r3 = new int[]{6, 8, 5, 1, 3, 9};
    var long2r4 = new int[]{9, 6, 8, 5, 1, 3};
    var long2r5 = new int[]{3, 9, 6, 8, 5, 1};

    Debug.Assert(S.Rob(leet1r0) == 3);
    Debug.Assert(S.Rob(leet1r1) == 3);
    Debug.Assert(S.Rob(leet1r2) == 3);

    Debug.Assert(S.Rob(leet2r0) == 4);
    Debug.Assert(S.Rob(leet2r1) == 4);
    Debug.Assert(S.Rob(leet2r2) == 4);
    Debug.Assert(S.Rob(leet2r3) == 4);

    Debug.Assert(S.Rob(corner2r0) == 5);
    Debug.Assert(S.Rob(corner2r1) == 5);

    Debug.Assert(S.Rob(corner1) == 5);

    Debug.Assert(S.Rob(long1r0) == 23);
    Debug.Assert(S.Rob(long1r1) == 23);
    Debug.Assert(S.Rob(long1r2) == 23);
    Debug.Assert(S.Rob(long1r3) == 23);
    Debug.Assert(S.Rob(long1r4) == 23);
    Debug.Assert(S.Rob(long1r5) == 23);

    Debug.Assert(S.Rob(long2r0) == 18);
    Debug.Assert(S.Rob(long2r1) == 18);
    Debug.Assert(S.Rob(long2r2) == 18);
    Debug.Assert(S.Rob(long2r3) == 18);
    Debug.Assert(S.Rob(long2r4) == 18);
    Debug.Assert(S.Rob(long2r5) == 18);

    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
