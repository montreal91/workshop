#
# Author: montreal91
# Solved in 0:27
# Failed attempts: 1
#

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def removeElements(self, head: ListNode, val: int) -> ListNode:
        while head is not None and head.val == val:
            head = head.next

        if head is None:
            return head

        curr = head.next
        prev = head
        while curr is not None:
            if curr.val == val:
                prev.next = curr.next
                curr = curr.next
                continue

            prev = curr
            curr = curr.next

        return head
