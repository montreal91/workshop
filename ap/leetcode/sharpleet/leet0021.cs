//
// Problem: https://leetcode.com/problems/merge-two-sorted-lists/
// Author: montreal91
// Solved in 0:41
//


using System;

using Utils;

namespace leetsharp {


class Mixer21 {
  private ListNode l1, l2;
  
  public Mixer21(ListNode l1, ListNode l2) {
    this.l1 = l1;
    this.l2 = l2;
  }

  public int NextVal() {
    var tmp = GetVal();
    if (l1 != null && l1.val == tmp) {
      l1 = l1.next;
      return tmp;
    }
    if (l2 != null && l2.val == tmp) {
      l2 = l2.next;
      return tmp;
    }
    return Int32.MaxValue;
  }

  private int GetVal() {
    if (l1 != null && l2 != null) {
      return Math.Min(l1.val, l2.val);
    }
    if (l1 != null) {
      return l1.val;
    }
    if (l2 != null) {
      return l2.val;
    }
    return Int32.MaxValue;
  }
}

class Solution0021 {
  public ListNode MergeTwoLists(ListNode l1, ListNode l2) {
    
    var mixer = new Mixer21(l1, l2);
    var result = new ListNode(mixer.NextVal());
    var prev = result;
    var curr = new ListNode();
    int tmp = result.val;

    do {
      tmp = mixer.NextVal();
      if (tmp == Int32.MaxValue) {
        break;
      }
      curr.val = tmp;
      prev.next = curr;
      prev = curr;
      curr = new ListNode();
    } while (tmp != Int32.MaxValue);
    if (result.val == Int32.MaxValue) {
      return null;
    }
    return result;
  }
  public static void TestSolution() {
    var S = new Solution0021();
    var l1 = new int[]{1, 2, 3};
    var l2 = new int[]{};
    var l3 = new int[]{1, 2, 3};
    var l4 = new int[]{1};
    var l5 = new int[]{1, 2};
    PrintLinkedList(S.MergeTwoLists(MakeLinkedList(l1), MakeLinkedList(l4)));
  }

  private static void PrintLinkedList(ListNode node) {
    if (node == null) {
      Console.WriteLine("[]");
    }
    var curr = node;
    while (curr != null) {
      Console.WriteLine(curr.val);
      curr = curr.next;
    }
  }

  private static ListNode MakeLinkedList(int[] array) {
    if (array.Length == 0) {
      return null;
    } 
    var res = new ListNode(array[0]);
    var prev = res;
    var curr = new ListNode();
    for (int i=1; i<array.Length; i++) {
      curr = new ListNode(array[i]);
      prev.next = curr;
      prev = curr;
    }
    return res;
  }
}


} // namespace leetsharp
