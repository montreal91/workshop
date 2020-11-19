using System.Collections.Generic;


namespace Utils {

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

public class Node {
  public int val;
  public IList<Node> children;

  public Node() {}

  public Node(int _val) {
    val = _val;
  }

  public Node(int _val, IList<Node> _children) {
    val = _val;
    children = _children;
  }
}

public class TreeNode {
  public int val;
  public TreeNode left;
  public TreeNode right;
  public TreeNode(int val=0, TreeNode left=null, TreeNode right=null) {
    this.val = val;
    this.left = left;
    this.right = right;
  }

  public static TreeNode ComposeTestTree0() {
    return new TreeNode(10);
  }

  public static TreeNode ComposeTestTree1() {
    var root = new TreeNode(5);
    var n1 = new TreeNode(4);
    var n2 = new TreeNode(8);
    var n3 = new TreeNode(11);
    var n4 = new TreeNode(13);
    var n5 = new TreeNode(4);
    var n6 = new TreeNode(7);
    var n7 = new TreeNode(2);
    var n8 = new TreeNode(1);

    root.left = n1;
    root.right = n2;

    n1.left = n3;
    n1.right = n4;

    n2.right = n5;

    n3.left = n6;
    n3.right = n7;
    n5.right = n8;

    return root;
  }

  public static TreeNode ComposeTestTree2() {
    var root = new TreeNode(-3);
    var n1 = new TreeNode(3);
    var n2 = new TreeNode(0);
    root.left = n1;
    root.right = n2;
    return root;
  }

  public static TreeNode ComposeTestTree3() {
    return null;
  }
}

} // namespace Utils
