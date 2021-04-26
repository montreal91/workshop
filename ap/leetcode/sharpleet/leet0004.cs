
//
// Problem: https://leetcode.com/problems/median-of-two-sorted-arrays/
// Author: montreal91
// Solved in 0:47
//

using System;
using System.Diagnostics;


namespace leetsharp {


class Mixer {
  private int[] arr1;
  private int[] arr2;
  private int c1 = 0;
  private int c2 = 0;

  public Mixer(int[] arr1, int[] arr2) {
    this.arr1 = arr1;
    this.arr2 = arr2;
  }

  public int Next() {
    var a1 = GetArr1();
    var a2 = GetArr2();
    if (a1 <= a2) {
      c1++;
      return a1;
    }
    c2++;
    return a2;
  }

  private int GetArr1() {
    if (c1 >= arr1.Length) {
      return Int32.MaxValue;
    }
    return arr1[c1];
  }

  private int GetArr2() {
    if (c2 >= arr2.Length) {
      return Int32.MaxValue;
    }
    return arr2[c2];
  }
}

class Solution0004 {
  public double FindMedianSortedArrays(int[] nums1, int[] nums2) {
    int cur = 0, prev = 0;
    int totalLength = nums1.Length + nums2.Length;
    var mix = new Mixer(nums1, nums2);
    for (int i=0; i <= totalLength / 2; i++) {
      prev = cur;
      cur = mix.Next();
    }
    if (totalLength % 2 == 0) {
      return Average(cur, prev);
    }
    return Average(cur, cur);
  }

  private static double Average(int a, int b) {
    return (double)(a + b) / 2.0;
  }

  public static void TestSolution() {
    var empty = new int[] {};
    var A1 = new int[] {1, 1, 1};
    var A2 = new int[] {2, 2, 2};
    var A3 = new int[] {1000000};
    var A4 = new int[] {-5, -4, 2, 3};
    var A5 = new int[] {0};
    var A6 = new int[] {100};
    var A7 = new int[] {0, 0};

    var S = new Solution0004();

    Debug.Assert(Equals(S.FindMedianSortedArrays(A1, A2), 1.5));
    Debug.Assert(Equals(S.FindMedianSortedArrays(A2, A1), 1.5));
    Debug.Assert(Equals(S.FindMedianSortedArrays(A1, empty), 1));
    Debug.Assert(Equals(S.FindMedianSortedArrays(empty, A2), 2));
    Debug.Assert(Equals(S.FindMedianSortedArrays(A3, empty), 1000000));
    Debug.Assert(Equals(
      S.FindMedianSortedArrays(HugeArray(1000000), HugeArray(1000000)),
      1000000
    ));
    Debug.Assert(Equals(S.FindMedianSortedArrays(A5, A6), 50.0));
    Debug.Assert(Equals(S.FindMedianSortedArrays(A7, A7), 0.0));

    Console.WriteLine("All tests passed.");
  }

  private const double YPS = 0.000001;

  private static bool Equals(double a, double b) {
    return Math.Abs(a - b) < YPS;
  }

  private static int[] HugeArray(int val) {
    int[] res = new int[1000];
    for (int i=0; i<1000; i++) {
      res[i] = val;
    }
    return res;
  }
}


} // namespace leetsharp
