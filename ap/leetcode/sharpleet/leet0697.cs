//
// Problem: https://leetcode.com/problems/degree-of-an-array/
// Author: montreal91
// Solved in 0:29
// Failed attempts: 0
//
using System;
using System.Collections.Generic;
using System.Diagnostics;

using Utils;


namespace leetsharp {

// passive class to hold data
class Tracker {
  public int firstSeen, lastSeen, count;

  public int GetLen() {
    return lastSeen - firstSeen + 1;
  }
}


class Solution0697 {
  public int FindShortestSubArray(int[] nums) {
    var counter = new Dictionary<int, Tracker>();

    for (int i=0; i<nums.Length; i++) {
      if (counter.ContainsKey(nums[i])) {
        counter[nums[i]].count++;
        counter[nums[i]].lastSeen = i;
      }
      else {
        counter[nums[i]] = new Tracker();
        counter[nums[i]].count = 1;
        counter[nums[i]].firstSeen = i;
        counter[nums[i]].lastSeen = i;
      }
    }

    var deg = counter[nums[0]].count;
    var len = counter[nums[0]].GetLen();

    foreach (var v in counter.Values) {
      if (v.count > deg) {
        deg = v.count;
        len = v.GetLen();
        continue;
      }
      if (v.count == deg && v.GetLen() < len) {
        len = v.GetLen();
      }
    }
    return len;
  }

  public static void TestSolution() {
    var mycase1 = new int[]{1, 2, 1, 3, 2}; // 3
    var mycase2 = new int[]{1, 2, 3, 4, 5}; // 1
    var one = new int[]{1}; // 1
    var leet1 = new int[]{1,2,2,3,1}; // 2
    var leet2 = new int[]{1,2,2,3,1,4,2}; // 6

    var S = new Solution0697();
    Debug.Assert(S.FindShortestSubArray(mycase1) == 3);
    Debug.Assert(S.FindShortestSubArray(mycase2) == 1);
    Debug.Assert(S.FindShortestSubArray(one) == 1);
    Debug.Assert(S.FindShortestSubArray(leet1) == 2);
    Debug.Assert(S.FindShortestSubArray(leet2) == 6);
    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
