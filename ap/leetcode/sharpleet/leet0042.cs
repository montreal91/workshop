//
// Author: montreal91
// Solved in 2:17
// Failed attempts: 0
//
using System;
using System.Collections.Generic;
using System.Diagnostics;

using Utils;


namespace leetsharp {

class Solution0042 {
  public int Trap(int[] height) {
    if (height == null) {
      return 0;
    }
    int res = 0;
    int[] maxLefts = new int[height.Length];
    int[] maxRights = new int[height.Length];
    int tmpMax = 0;
    for (int i=0; i<height.Length; i++) {
      maxLefts[i] = tmpMax;
      tmpMax = Math.Max(tmpMax, height[i]);
    }

    tmpMax = 0;
    for (int i=height.Length - 1; i>=0; i--) {
      maxRights[i] = tmpMax;
      tmpMax = Math.Max(tmpMax, height[i]);
    }

    int delta;
    for (int i=0; i<height.Length; i++) {
      delta = Math.Min(maxLefts[i], maxRights[i]) - height[i];
      res += Math.Max(delta, 0);
    }
    return res;
  }

  private static int MaxFactor(int left, int right) {
    if (left >= right) {
      return 1;
    }
    return 0;
  }

  public static void TestSolution() {
    var test6_1 = new int[]{6, 2, 4, 1, 3, 5}; // 10
    var test6_2 = new int[]{6, 2, 5, 1, 3, 4}; // 7
    var test6_3 = new int[]{6, 4, 5, 3, 2, 1}; // 1
    var test6_4 = new int[]{6, 4, 3, 2, 1, 5}; // 10
    var test6_5 = new int[]{6, 5, 4, 3, 2, 1}; // 0
    var test0 = new int[]{}; // 0
    var test10_1 = new int[]{1, 2, 3, 4, 5, 5, 4, 3, 2, 1}; // 0
    var leet1 = new int[]{0,1,0,2,1,0,1,3,2,1,2,1}; // 6
    var leet2 = new int[]{4,2,0,3,2,5}; // 9
    var S = new Solution0042();

    Debug.Assert(S.Trap(test0) == 0);
    Debug.Assert(S.Trap(test6_1) == 10);
    Debug.Assert(S.Trap(test6_2) == 7);
    Debug.Assert(S.Trap(test6_3) == 1);
    Debug.Assert(S.Trap(test6_4) == 10);
    Debug.Assert(S.Trap(test6_5) == 0);
    Debug.Assert(S.Trap(test10_1) == 0);
    Debug.Assert(S.Trap(leet1) == 6);
    Debug.Assert(S.Trap(leet2) == 9);
    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
