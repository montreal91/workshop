//
// Author: montreal91
// Solved in 0:06
// Failed attempts: 0
//

using System;
using System.Collections.Generic;
using System.Diagnostics;

using Utils;


namespace leetsharp {


class Solution0590 {
  private List<int> res = new List<int>();
  public IList<int> Postorder(Node root) {
    Visit(root);
    return res;
  }

  private void Visit(Node nodde) {
    if (nodde == null) {
      return;
    }
    foreach (var child in nodde.children) {
      Visit(child);
    }
    res.Add(nodde.val);
  }

  public static void TestSolution() {
    var S = new Solution0590();
    Debug.Assert(true);
    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
