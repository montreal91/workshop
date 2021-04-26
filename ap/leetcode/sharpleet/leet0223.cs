//
// Problem: https://leetcode.com/problems/rectangle-area/
// Author: montreal91
// Solved in 1:11
// Passed from second attempt.
// Though output was specified as int, intermediate values could cause int
// overflow and I didn't deal with this case correctly.
//

using System;
using System.Diagnostics;


namespace leetsharp {


class Solution0223 {
  public int ComputeArea(
    long A, long B, long C, long D, long E, long F, long G, long H
  ) {
    long S = ComputeArea(A, B, C, D) + ComputeArea(E, F, G, H);
    long dS = Computelongersection(A, C, E, G) * Computelongersection(B, D, F, H);
    return (int)(S - dS);
  }

  private static long ComputeArea(long A, long B, long C, long D) {
    return Math.Abs(A - C) * Math.Abs(B - D);
  }

  private static long Computelongersection(long A, long B, long C, long D) {
    var arr = new long[] {A, B, C, D};
    long tmp = Math.Abs(A - B) + Math.Abs(C - D) - (Max(arr) - Min(arr));
    return Math.Max(tmp, 0);
  }

  private static long Max(long[] arr) {
    var tmpMax = arr[0];
    foreach (var a in arr) {
      tmpMax = Math.Max(tmpMax, a);
    }
    return tmpMax;
  }

  private static long Min(long[] arr) {
    var tmpMax = arr[0];
    foreach (var a in arr) {
      tmpMax = Math.Min(tmpMax, a);
    }
    return tmpMax;
  }

  public static void TestSolution() {
    var S = new Solution0223();
    Debug.Assert(S.ComputeArea(2, 0, 5, 6, 4, -1, 8, 4) == 34);
    Debug.Assert(S.ComputeArea(-3, 0, 3, 4, 0, -1, 9, 2) == 45);
    Debug.Assert(S.ComputeArea(-1, 3, 2, 5, -2, 2, 3, 7) == 25);
    Debug.Assert(S.ComputeArea(2, 3, 5, 6, 0, -1, 4, 2) == 21);
    Debug.Assert(S.ComputeArea(-2, 0, 2, 2, -2, -2, 2, 0) == 16);
    Debug.Assert(S.ComputeArea(-2, 0, 2, 4, -4, -2, 4, 2) == 40);

    Debug.Assert(S.ComputeArea(4, -1, 8, 4, 2, 0, 5, 6) == 34);
    Debug.Assert(S.ComputeArea(0, -1, 9, 2, -3, 0, 3, 4) == 45);
    Debug.Assert(S.ComputeArea( -2, 2, 3, 7, -1, 3, 2, 5) == 25);
    Debug.Assert(S.ComputeArea(0, -1, 4, 2, 2, 3, 5, 6) == 21);
    Debug.Assert(S.ComputeArea(-2, -2, 2, 0, -2, 0, 2, 2) == 16);
    Debug.Assert(S.ComputeArea(-4, -2, 4, 2, -2, 0, 2, 4) == 40);
    Debug.Assert(S.ComputeArea(-1500000001, 0, -1500000000, 1, 1500000000, 0, 1500000001, 1) == 2);

    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
