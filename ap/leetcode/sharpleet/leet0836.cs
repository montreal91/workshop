//
// Problem: https://leetcode.com/problems/rectangle-overlap/
// Author: montreal91
// Solved in 00:17
//
using System;
using System.Diagnostics;


namespace leetsharp {


class Solution0836 {
  public bool IsRectangleOverlap(int[] rec1, int[] rec2) {
    long Dx = GetCoordinateOverlap(rec1[0], rec1[2], rec2[0], rec2[2]);
    long Dy = GetCoordinateOverlap(rec1[1], rec1[3], rec2[1], rec2[3]);
    return Dx * Dy > 0;
  }

  private long GetCoordinateOverlap(int x11, int x12, int x21, int x22) {
    long begin = Math.Min(x11, x21);
    long end = Math.Max(x12, x22);
    long l1 = Math.Abs(x11 - x12);
    long l2 = Math.Abs(x21 - x22);
    return Math.Max(0, l1 + l2 - (end - begin));
  }

  public static void TestSolution() {
    var rec1 = new int[] {0, 0, 2, 2};
    var rec2 = new int[] {1, 1, 3, 3};
    var dot = new int[] {1, 1, 1, 1};
    var myRec1 = new int[] {2, 1, 5, 4};
    var myRec2 = new int[] {-1, 2, 2, 5};
    var myRec3 = new int[] {2, 1, 3, 2};

    var S = new Solution0836();
    Debug.Assert(S.IsRectangleOverlap(rec1, rec2) == true);
    Debug.Assert(S.IsRectangleOverlap(rec2, rec1) == true);
    Debug.Assert(S.IsRectangleOverlap(rec2, dot) == false);
    Debug.Assert(S.IsRectangleOverlap(myRec1, myRec2) == false);
    Debug.Assert(S.IsRectangleOverlap(myRec1, myRec3) == true);
    Debug.Assert(S.IsRectangleOverlap(myRec3, myRec1) == true);
    Debug.Assert(S.IsRectangleOverlap(myRec3, myRec3) == true);
    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
