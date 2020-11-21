//
// Problem: https://leetcode.com/problems/flower-planting-with-no-adjacent/
// Author: montreal91
// Solved in 0:48
// Failed attempts: 0
//

using System;
using System.Collections.Generic;
using System.Diagnostics;

using Utils;


namespace leetsharp {

class GardenGraph {
  private List<int> flowers;
  private List<List<int>> paths;

  public GardenGraph(int n, int[][] paths) {
    this.flowers = new List<int>(new int[n]);
    InitPaths(n);

    foreach (var path in paths) {
      var i = path[0] - 1;
      var j = path[1] - 1;
      this.paths[i].Add(j);
      this.paths[j].Add(i);
    }
  }

  public int[] GetFlowers() {
    return flowers.ToArray();
  }

  public void AutoPlant() {
    for (int i=0; i<flowers.Count; i++) {
      flowers[i] = GetPossibleFlower(GetNeighbourFlowers(i));
    }
  }

  private void InitPaths(int n) {
    this.paths = new List<List<int>>();
    for (int i=0; i<n;i++) {
      paths.Add(new List<int>());
    }
  }

  private List<int> GetNeighbourFlowers(int garden) {
    var res = new List<int>();
    var neighbours = paths[garden];
    foreach (var n in neighbours) {
      res.Add(flowers[n]);
    }
    return res;
  }

  private int GetPossibleFlower(List<int> nFlowers) {
    for (int i=1; i<=4; i++) {
      if(nFlowers.IndexOf(i) == -1) {
        return i;
      }
    }
    return -1; // this should never happen
  }
}


class Solution {
  public int[] GardenNoAdj(int n, int[][] paths) {
    var garden = new GardenGraph(n, paths);
    garden.AutoPlant();
    return  garden.GetFlowers();
  }

  public static void TestSolution() {
    var S = new Solution();
    var paths = new int[][]{
      new int[]{1, 2},
      new int[]{1, 3},
      // new int[]{1, 4},
      new int[]{1, 5},
      new int[]{2, 3},
      // new int[]{2, 4},
      new int[]{2, 5},
      new int[]{3, 4},
      new int[]{4, 5}
    };
    Tools.PrintArray(S.GardenNoAdj(5, paths));
  }
}


} // namespace leetsharp
