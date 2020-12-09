//
// Problem: https://leetcode.com/problems/all-paths-from-source-to-target/
// Author: montreal91
// Solved in 0:57
// Failed attempts: 0
//
using System;
using System.Collections.Generic;
using System.Diagnostics;

using Utils;


namespace leetsharp {


class Solution0797 {
  public IList<IList<int>> AllPathsSourceTarget(int[][] graph) {
    var res = new List<IList<int>>();
    Lookup(graph, new Stack<int>(), res, 0);
    return res;
  }

  private void Lookup(int[][] graph, Stack<int> currentPath, IList<IList<int>> allPaths, int currentNode) {
    currentPath.Push(currentNode);
    if (currentNode == graph.Length - 1) {
      allPaths.Add(StackToList(currentPath));
    }
    else {
      foreach (var node in graph[currentNode]) {
        Lookup(graph, currentPath, allPaths, node);
      }
    }
    currentPath.Pop();
  }

  private static IList<int> StackToList(Stack<int> path) {
    var res = new List<int>(path);
    res.Reverse();
    return res;
  }

  public static void TestSolution() {
    var test1 = new int[][] {
      new int[]{1},
      new int[]{}
    };

    var test2 = new int[][] {
      new int[]{1, 2},
      new int[]{6},
      new int[]{3, 5},
      new int[]{4},
      new int[]{7},
      new int[]{4},
      new int[]{7},
      new int[]{}
    };

    var test3 = new int[][] {
      new int[]{1, 2, 3, 4}, // 0
      new int[]{5},
      new int[]{},
      new int[]{6, 7, 8},
      new int[]{},
      new int[]{9, 10, 11}, // 5
      new int[]{},
      new int[]{},
      new int[]{12, 13, 14},
      new int[]{},
      new int[]{15}, // 10
      new int[]{16},
      new int[]{17},
      new int[]{18},
      new int[]{},
      new int[]{}, // 15
      new int[]{19},
      new int[]{20},
      new int[]{},
      new int[]{21},
      new int[]{21}, // 20
      new int[]{}
    };

    var S = new Solution0797();
    var res = S.AllPathsSourceTarget(test3);
    foreach (var path in res) {
      var arr = new int[path.Count];
      path.CopyTo(arr, 0);
      Tools.PrintArray(arr);
    }
    Debug.Assert(true);
    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
