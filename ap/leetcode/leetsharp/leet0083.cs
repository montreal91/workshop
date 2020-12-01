//
// Problem: https://leetcode.com/problems/remove-duplicates-from-sorted-list/
// Author: montreal91
// Solved in 0:21
// Failed attempts: 0
//
using System;
using System.Diagnostics;

using Utils;


namespace leetsharp {


class Solution0083 {
  public ListNode DeleteDuplicates(ListNode head) {
    if (head == null) {
      return head;
    }
    var curr = head;
    while (curr.next != null) {
      if (curr.val == curr.next.val) {
        curr.next = curr.next.next;
      }
      else {
        curr = curr.next;
      }
    }
    return head;
  }
  public static void TestSolution() {
    var S = new Solution0083();
    Debug.Assert(true);

    var test1 = new int[] {1, 2, 3};
    var test2 = new int[] {1, 2, 3, 4};
    var empty = new int[]{};
    var single = new int[]{1};
    var pair = new int[]{1, 1};
    var diff = new int[]{1, 2};
    var commonCase1 = new int[] {1, 2, 2, 2, 2, 2, 3, 3, 4, 5, 6, 7, 7, 7, 7, 8, 9};
    var commonCase2 = new int[] {1, 2, 3, 4, 4, 4, 4, 5, 5, 5, 6, 6, 7, 8, 9, 9, 9};
    var rainbow = new int[] {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Debug.Assert(Tools.CompareLinkedLists(ListNode.FromArray(test1), ListNode.FromArray(test2)) == false);
    Debug.Assert(Tools.CompareLinkedLists(ListNode.FromArray(test2), ListNode.FromArray(test1)) == false);

    Debug.Assert(Tools.CompareLinkedLists(
      S.DeleteDuplicates(ListNode.FromArray(empty)),
      ListNode.FromArray(empty)
    ));
    Debug.Assert(Tools.CompareLinkedLists(
      S.DeleteDuplicates(ListNode.FromArray(test1)),
      ListNode.FromArray(test1)
    ));
    Debug.Assert(Tools.CompareLinkedLists(
      S.DeleteDuplicates(ListNode.FromArray(test2)),
      ListNode.FromArray(test2)
    ));
    Debug.Assert(Tools.CompareLinkedLists(
      S.DeleteDuplicates(ListNode.FromArray(pair)),
      ListNode.FromArray(single)
    ));
    Debug.Assert(Tools.CompareLinkedLists(
      S.DeleteDuplicates(ListNode.FromArray(single)),
      ListNode.FromArray(single)
    ));
    Debug.Assert(Tools.CompareLinkedLists(
      S.DeleteDuplicates(ListNode.FromArray(diff)),
      ListNode.FromArray(diff)
    ));
    Debug.Assert(Tools.CompareLinkedLists(
      S.DeleteDuplicates(ListNode.FromArray(rainbow)),
      ListNode.FromArray(rainbow)
    ));
    Debug.Assert(Tools.CompareLinkedLists(
      S.DeleteDuplicates(ListNode.FromArray(commonCase1)),
      ListNode.FromArray(rainbow)
    ));
    Debug.Assert(Tools.CompareLinkedLists(
      S.DeleteDuplicates(ListNode.FromArray(commonCase2)),
      ListNode.FromArray(rainbow)
    ));
    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
