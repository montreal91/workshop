
//
// Problem: https://leetcode.com/problems/palindrome-linked-list/
// Author: montreal91
// Solved in 1:47
//
// The only objection is time.
// I generated idea quite quckly and passed all tests from the first attempt.
//

using System;
using System.Collections.Generic;
using System.Diagnostics;


namespace leetsharp {


public class ListNode {
  public int val;
  public ListNode next;
  public ListNode(int val=0, ListNode next=null) {
    this.val = val;
    this.next = next;
  }

  public static ListNode FromArray(int[] vals) {
    if (vals.Length == 0) {
      return null;
    }
    var nodes = new List<ListNode>();
    foreach (int v in vals) {
      nodes.Add(new ListNode(v, null));
    }

    for (int i=0; i<nodes.Count - 1; i++) {
      nodes[i].next = nodes[i+1];
    }
    return nodes[0];
  }
}


public class Solution {
  bool IsPalindrome(ListNode head) {
    if (head == null) {
      return true;
    }

    var tail = Reverse(head);
    var curr = head;

    do {
      if (tail.val != curr.val) {
        return false;
      }
      tail = tail.next;
      curr = curr.next;
    } while (tail != null);
    return true;
  }


  ListNode Reverse(ListNode head) {
    var newList = new List<ListNode>();
    var curr = head;
    do {
      newList.Add(CopyNode(curr));
      curr = curr.next;
    } while (curr != null);

    for (int i=newList.Count-1; i>0; i--) {
      newList[i].next = newList[i-1];
    }

    newList[0].next = null;
    return newList[newList.Count - 1];
  }

  ListNode CopyNode(ListNode node) {
    return new ListNode(node.val, node.next);
  }

  public static void TestSolution() {

    var s = new Solution();
    var posCase0 = ListNode.FromArray(new int[]{});
    var posCase1 = ListNode.FromArray(new int[]{1});
    var posCase2 = ListNode.FromArray(new int[]{1, 1});
    var posCase3 = ListNode.FromArray(new int[]{1, 2, 1});
    var posCase4 = ListNode.FromArray(new int[]{1, 2, 2, 1});
    var posCase5 = ListNode.FromArray(new int[]{5, 4, 3, 2, 1, 2, 3, 4, 5});
    var posCase6 = ListNode.FromArray(new int[]{5, 4, 3, 2, 1, 1, 2, 3, 4, 5});
    var negCase0 = ListNode.FromArray(new int[]{1, 2});
    var negCase1 = ListNode.FromArray(new int[]{1, 2, 1, 1});
    var negCase2 = ListNode.FromArray(new int[]{1, 2, 3, 3, 2, 9});
    var negCase3 = ListNode.FromArray(new int[]{1, 1, 1, 2});

    Debug.Assert(s.IsPalindrome(posCase0) == true);
    Debug.Assert(s.IsPalindrome(posCase1) == true);
    Debug.Assert(s.IsPalindrome(posCase2) == true);
    Debug.Assert(s.IsPalindrome(posCase3) == true);
    Debug.Assert(s.IsPalindrome(posCase4) == true);
    Debug.Assert(s.IsPalindrome(posCase5) == true);

    Debug.Assert(s.IsPalindrome(negCase0) == false);
    Debug.Assert(s.IsPalindrome(negCase1) == false);
    Debug.Assert(s.IsPalindrome(negCase2) == false);
    Debug.Assert(s.IsPalindrome(negCase3) == false);

    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
