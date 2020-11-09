
//
// Problem: https://leetcode.com/problems/palindrome-linked-list/
// Author: montreal91
// Solved in 0:30
//

using System;
using System.Collections.Generic;
using System.Diagnostics;


namespace leetsharp {


class Solution0219 {
  public bool ContainsNearbyDuplicate(int[] nums, int k) {
    var counter = new Dictionary<int, int>();

    for (int i=0; i<nums.Length; i++) {
      if (counter.ContainsKey(nums[i])) {
        if (i - counter[nums[i]] <= k) {
          return true;
        }
      }
      counter[nums[i]] = i;
    }
    return false;
  }

  public static void TestSolution() {
    var array0 = new int[] {};
    var array1 = new int[] {1};
    var array2 = new int[] {1, 2, 3, 3, 2, 1};
    var array3 = new int[] {1, 2, 3, 1};
    var array4 = new int[] {1, 0, 1, 1};
    var array5 = new int[] {1, 2, 3, 1, 2, 3};
    var array6 = new int[] {1, 2, 3, 4, 5, 6};
    var array7 = new int[] {1, 2, 3, 4, 5, 6, 1, 7, 8, 9, 10, 7};

    var s = new Solution0219();

    Debug.Assert(s.ContainsNearbyDuplicate(array0, 0) == false);
    Debug.Assert(s.ContainsNearbyDuplicate(array0, 1) == false);

    Debug.Assert(s.ContainsNearbyDuplicate(array1, 0) == false);
    Debug.Assert(s.ContainsNearbyDuplicate(array1, 1) == false);

    Debug.Assert(s.ContainsNearbyDuplicate(array2, 3) == true);
    Debug.Assert(s.ContainsNearbyDuplicate(array2, 2) == true);
    Debug.Assert(s.ContainsNearbyDuplicate(array2, 1) == true);
    Debug.Assert(s.ContainsNearbyDuplicate(array2, 0) == false);

    Debug.Assert(s.ContainsNearbyDuplicate(array3, 3) == true);
    Debug.Assert(s.ContainsNearbyDuplicate(array4, 1) == true);

    Debug.Assert(s.ContainsNearbyDuplicate(array5, 1) == false);
    Debug.Assert(s.ContainsNearbyDuplicate(array5, 2) == false);
    Debug.Assert(s.ContainsNearbyDuplicate(array5, 3) == true);

    Debug.Assert(s.ContainsNearbyDuplicate(array6, 1) == false);
    Debug.Assert(s.ContainsNearbyDuplicate(array6, 2) == false);
    Debug.Assert(s.ContainsNearbyDuplicate(array6, 3) == false);
    Debug.Assert(s.ContainsNearbyDuplicate(array6, 4) == false);
    Debug.Assert(s.ContainsNearbyDuplicate(array6, 5) == false);
    Debug.Assert(s.ContainsNearbyDuplicate(array6, 6) == false);

    Debug.Assert(s.ContainsNearbyDuplicate(array7, 1) == false);
    Debug.Assert(s.ContainsNearbyDuplicate(array7, 2) == false);
    Debug.Assert(s.ContainsNearbyDuplicate(array7, 3) == false);
    Debug.Assert(s.ContainsNearbyDuplicate(array7, 4) == true);

    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
