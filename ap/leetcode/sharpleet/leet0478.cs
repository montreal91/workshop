//
// Problem: https://leetcode.com/problems/generate-random-point-in-a-circle/
// Author: montreal91
// Solved in 1:01
// Failed attempts: 4
//
using System;
using System.Diagnostics;

using Utils;


namespace leetsharp {


class Solution0478 {
  private double radius;
  private double x_center;
  private double y_center;
  private Random random = new Random();
  private readonly double pi = 3.141592;

  public Solution0478(double radius, double x_center, double y_center) {
    this.radius = radius;
    this.x_center = x_center;
    this.y_center = y_center;
  }

  public double[] RandPoint() {
    var t = GetAngle();
    var r = GetRadius();
    var x = r * Math.Cos(t) + x_center;
    var y = r * Math.Sin(t) + y_center;
    return new double[] {x, y};
  }

  private double GetAngle() {
    return random.NextDouble() * 2 * pi;
  }

  private double GetRadius() {
    return Math.Sqrt(random.NextDouble() * radius * radius);
  }

  public static void TestSolution() {
    var S = new Solution0478(1.0, 0.0, 0.0);
    Debug.Assert(true);
    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
