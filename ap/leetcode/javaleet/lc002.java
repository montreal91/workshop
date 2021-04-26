
// Definition for singly-linked list.

class ListNode {
    int val;
    ListNode next;
    ListNode(int x) { val = x; }
}

class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode curLeft = l1;
        ListNode curRight = l2;

        ListNode res = new ListNode(0);
        ListNode curRes = res;

        int remainder = 0;

        while (curLeft != null || curRight != null) {
            if (curLeft == null) {
                curLeft = new ListNode(0);
            }
            if (curRight == null) {
                curRight = new ListNode(0);
            }
            int newVal = curLeft.val + curRight.val + remainder;
            ListNode newEntry = new ListNode(newVal % 10);
            curRes.next = newEntry;

            if (newVal >= 10) {
                remainder = 1;
                newVal %= 10;
            }
            else {
                remainder = 0;
            }

            curRes = newEntry;

            curLeft = curLeft.next;
            curRight = curRight.next;
        }
        if (curLeft == null && curRight == null) {
            if (remainder > 0) {
                curRes.next = new ListNode(remainder);
            }
        }
        else if (curLeft == null) {
            curRight.val += remainder;
            curRes.next = curRight;
        }
        else if (curRight == null) {
            curLeft.val += remainder;
            curRes.next = curLeft;
        }
        return res.next;
    }

    private ListNode createNumber(int x) {
        int remainder = x;
        ListNode first = new ListNode(remainder % 10);
        ListNode previousNode = first;
        remainder /= 10;
        do {
            int digit = remainder % 10;
            ListNode newNode = new ListNode(digit);
            previousNode.next = newNode;
            previousNode = newNode;
            remainder /= 10;
        } while (remainder > 0);
        return first;
    }

    private void printNumber(ListNode firstDigit) {
        System.out.println("Printing number...");
        ListNode current = firstDigit;
        do {
            System.out.println(current.val);
            current = current.next;
        } while (current != null);
        System.out.print("\n");
    }

    public static void main(String[] args) {
        Solution s = new Solution();
        ListNode d1 = s.createNumber(1234);
        ListNode d2 = s.createNumber(888888);
        s.printNumber(s.addTwoNumbers(d1, d2));

        ListNode d3 = s.createNumber(342);
        ListNode d4 = s.createNumber(465);
        s.printNumber(s.addTwoNumbers(d3, d4));

        ListNode d5 = s.createNumber(1);
        ListNode d6 = s.createNumber(9999);
        s.printNumber(s.addTwoNumbers(d5, d6));
    }
}
