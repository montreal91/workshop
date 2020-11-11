
//
// Problem: https://leetcode.com/problems/find-the-town-judge/
// Author: montreal91
// Solved in 1:00
//
// The only objection is time.
// I generated idea quite quckly and passed all tests from the first attempt.
//

using System;
using System.Collections.Generic;
using System.Diagnostics;


namespace leetsharp {


class Solution0997 {
  public int FindJudge(int N, int[][] trust) {
    if (N == 1) {
      return 1;
    }
    var potentialJudges = GetTrustedPeople(N, trust);
    if (potentialJudges.Count != 1) {
      return -1;
    }
    return CheckJudge(potentialJudges[0], trust);
  }

  private static int CheckJudge(int label, int[][] E) {
    foreach (var e in E) {
      if (e[0] == label) {
        return -1;
      }
    }
    return label;
  }

  private static List<int> GetTrustedPeople(int N, int[][] V) {
    var counter = new int[N+1];
    counter[0] = -1;
    foreach (var v in V) {
      counter[v[1]]++;
    }

    var result = new List<int>();
    for (int i=0; i<counter.Length; i++) {
      if (counter[i] + 1 == N) {
        result.Add(i);
      }
    }
    return result;
  }

  private static int[] MakeEdge(int a, int b) {
    return new int[]{a, b};
  }

  public static void TestSolution() {
    var leet1 = new int[][]{
      MakeEdge(1, 2)
    }; // N = 2
    var leet2 = new int[][]{
      MakeEdge(1, 3),
      MakeEdge(2, 3)
    }; // N = 3
    var leet3 = new int[][] {
      MakeEdge(1, 3),
      MakeEdge(2, 3),
      MakeEdge(3, 1)
    }; // N = 3
    var leet4 = new int[][] {
      MakeEdge(1, 2),
      MakeEdge(2, 3)
    };  // N = 3
    var leet5 = new int[][] {
      MakeEdge(1, 3),
      MakeEdge(1, 4),
      MakeEdge(2, 3),
      MakeEdge(2, 4),
      MakeEdge(4, 3)
    };
    var empty = new int[][]{};
    var my1 = new int[][] {
      MakeEdge(1, 5),
      MakeEdge(2, 1),
      MakeEdge(2, 5),
      MakeEdge(3, 1),
      MakeEdge(3, 5),
      MakeEdge(4, 1),
      MakeEdge(4, 5)
    };
    var my1plus1 = new int[][] {
      MakeEdge(1, 5),
      MakeEdge(2, 1),
      MakeEdge(2, 5),
      MakeEdge(3, 1),
      MakeEdge(3, 5),
      MakeEdge(4, 1),
      MakeEdge(4, 5),
      MakeEdge(5, 1)
    };

    var my2 = new int [][] {
      MakeEdge(1, 4),
      MakeEdge(2, 1),
      MakeEdge(2, 5),
      MakeEdge(2, 4),
      MakeEdge(6, 2),
      MakeEdge(6, 4),
      MakeEdge(6, 5),
      MakeEdge(5, 4),
      MakeEdge(3, 5),
      MakeEdge(3, 4),
      MakeEdge(3, 6),
      MakeEdge(1, 6),
      MakeEdge(2, 3)
    };

    var S = new Solution0997();
    Debug.Assert(S.FindJudge(2, leet1) == 2);
    Debug.Assert(S.FindJudge(3, leet2) == 3);
    Debug.Assert(S.FindJudge(3, leet3) == -1);
    Debug.Assert(S.FindJudge(3, leet4) == -1);
    Debug.Assert(S.FindJudge(4, leet5) == 3);
    Debug.Assert(S.FindJudge(1, empty) == 1);
    Debug.Assert(S.FindJudge(2, empty) == -1);
    Debug.Assert(S.FindJudge(5, my1) == 5);
    Debug.Assert(S.FindJudge(6, my1) == -1);
    Debug.Assert(S.FindJudge(5, my1plus1) == -1);
    Debug.Assert(S.FindJudge(6, my2) == 4);
    Debug.Assert(S.FindJudge(7, my2) == -1);

    Console.WriteLine("All tests passed.");
  }

  private void PrintList(List<int> l) {
    foreach (var a in l) {
      Console.WriteLine(a);
    }
  }
}


} // namespace leetsharp
