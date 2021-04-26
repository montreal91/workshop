//
// Author: montreal91
// Solved in 0:00
// Failed attempts: 1
//

using System;
using System.Collections.Generic;
using System.Diagnostics;

using Utils;


namespace leetsharp {

class Connection {
  public int label;
  public int time;
}

class Solution {
  public int NetworkDelayTime(int[][] times, int N, int K) {
    // Console.WriteLine(N);
    var visited = new bool[N];
    var results = new int[N];
    Array.Fill(results, Int32.MaxValue);

    var graph = MakeGraph(N, times);
    var queue = new Queue<int>();
    queue.Enqueue(K - 1);
    results[K - 1] = 0;

    int C;
    while (queue.Count != 0) {
      C = queue.Dequeue();
      visited[C] = true;
      foreach (var edge in graph[C]) {
        int E = edge.label;
        results[E] = Math.Min(results[E], results[C] + edge.time);

        if (!visited[E]) {
          queue.Enqueue(E);
        }
      }
    }
    var tmpRes = 0;
    foreach (var r in results) {
      tmpRes = Math.Max(r, tmpRes);
    }
    Tools.PrintArray(results);
    Console.WriteLine($"Answer: {tmpRes}\n");
    if (tmpRes == Int32.MaxValue) {
      return -1;
    }
    return tmpRes;
  }

  private List<List<Connection>> MakeGraph(int N, int[][] edges) {
    var res = new List<List<Connection>>();
    for (int i=0; i<N; i++) {
      res.Add(new List<Connection>());
    }

    foreach (var edge in edges) {
      var c = new Connection();
      c.label = edge[1] - 1;
      c.time = edge[2];

      res[edge[0] - 1].Add(c);
    }
    return res;
  }

  public static void TestSolution() {
    var S = new Solution();
    var data1 = new int[][] {
      new int[]{1, 3, 2},
      new int[]{1, 2, 1},
      new int[]{2, 4, 1},
      new int[]{3, 4, 2},
      new int[]{4, 5, 1},
      new int[]{5, 6, 2},
      new int[]{5, 8, 3},
      new int[]{5, 7, 1},
      new int[]{6, 8, 2},
      new int[]{7, 8, 1},
      new int[]{8, 1, 5}
    };

    var data2 = new int[][] {
      new int[]{1, 3, 2},
      new int[]{3, 5, 4},
      new int[]{3, 4, 4},
      new int[]{5, 1, 3},
      new int[]{4, 2, 3},
      new int[]{4, 6, 5},
      new int[]{2, 6, 4},
      new int[]{6, 5, 6}
    };

    var data3 = new int[][] {
      new int[]{1, 2, 2},
      new int[]{1, 3, 1},
      new int[]{3, 2, 2},
    };

    var data4 = new int[][] {
      new int[]{1, 2, 3},
      new int[]{1, 3, 1},
      new int[]{3, 2, 1},
    };
    var res = S.NetworkDelayTime(data1, 8, 1);
    // Console.WriteLine(res);
    Debug.Assert(res == 5);
    Debug.Assert(S.NetworkDelayTime(data2, 6, 1) == 11);
    Debug.Assert(S.NetworkDelayTime(data2, 6, 2) == 19);
    Debug.Assert(S.NetworkDelayTime(data2, 6, 3) == 9);
    Debug.Assert(S.NetworkDelayTime(data2, 6, 4) == 16);
    Debug.Assert(S.NetworkDelayTime(data2, 6, 5) == 14);
    Debug.Assert(S.NetworkDelayTime(data2, 6, 6) == 18);

    Debug.Assert(S.NetworkDelayTime(data3, 3, 1) == 2);
    Debug.Assert(S.NetworkDelayTime(data4, 3, 1) == 2);
    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
