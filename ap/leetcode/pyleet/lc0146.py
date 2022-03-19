#
# Author: montreal91
# Time: 1:30
# Failed attempts: 0
#

class DllNode:
    def __init__(self, key, value, next=None, prev=None):
        self.key = key
        self.value = value
        self.next = next
        self.prev = prev


class LRUCache:
    def __init__(self, capacity: int):
        self._capacity = capacity
        self._values = {}
        self._dll_head = None
        self._dll_tail = None

    def get(self, key: int) -> int:
        node = self._values.get(key, None)
        if node is None:
            return -1
        self._move_to_head(node)
        return node.value

    def put(self, key: int, value: int) -> None:
        self._pop(key)

        node = DllNode(key=key, value=value)
        self._append_to_head(node)
        self._values[key] = node

        if len(self._values) > self._capacity:
            node = self._pop_from_tail()
            self._values.pop(node.key)

    def _move_to_head(self, node):
        self._pop(node.key)
        self._append_to_head(node)

    def _pop(self, key):
        if key not in self._values:
            return None
        node = self._values[key]

        if node.prev is not None:
            node.prev.next = node.next
        else:
            self._dll_head = node.next

        if node.next is not None:
            node.next.prev = node.prev
        else:
            self._dll_tail = node.prev

        node.next = None
        node.prev = None
        return node

    def _pop_from_tail(self):
        node = self._dll_tail
        self._dll_tail.prev.next = None
        self._dll_tail = self._dll_tail.prev
        return node

    def _pop_from_middle(self, node):
        node.prev.next = node.next
        node.next.prev = node.prev
        return node

    def _append_to_head(self, node):
        if self._dll_head is None:
            self._dll_head = node
            self._dll_tail = node
            return

        self._dll_head.prev = node
        node.next = self._dll_head
        self._dll_head = node

    def _get_values_list_for_test_head_to_tail(self):
        res = []
        curr = self._dll_head

        while not curr is None:
            res.append(curr.value)
            curr = curr.next

        return res

    def _get_values_list_for_test_tail_to_head(self):
        res = []
        curr = self._dll_tail

        while curr is not None:
            res.append(curr.value)
            curr = curr.prev

        return res


def smoke_test():
    cache = LRUCache(capacity=5)

    assert cache.get(1) == -1
    cache.put(1, 1)
    assert cache.get(1) == 1
    assert cache._get_values_list_for_test_head_to_tail() == [1]
    assert cache._get_values_list_for_test_tail_to_head() == [1]

    assert cache.get(4) == -1
    cache.put(4, 16)
    assert cache.get(4) == 16
    assert cache._get_values_list_for_test_head_to_tail() == [16, 1]
    assert cache._get_values_list_for_test_tail_to_head() == [1, 16]

    assert cache.get(5) == -1
    cache.put(5, 25)
    assert cache.get(5) == 25
    assert cache._get_values_list_for_test_head_to_tail() == [25, 16, 1]
    assert cache._get_values_list_for_test_tail_to_head() == [1, 16, 25]

    assert cache.get(6) == -1
    cache.put(6, 36)
    assert cache.get(6) == 36
    assert cache._get_values_list_for_test_head_to_tail() == [36, 25, 16, 1]
    assert cache._get_values_list_for_test_tail_to_head() == [1, 16, 25, 36]

    assert cache.get(8) == -1
    cache.put(8, 64)
    assert cache.get(8) == 64
    assert cache._get_values_list_for_test_head_to_tail() == [64, 36, 25, 16, 1]
    assert cache._get_values_list_for_test_tail_to_head() == [1, 16, 25, 36, 64]

    assert cache.get(12) == -1
    cache.put(12, 144)
    assert cache.get(12) == 144
    assert cache._get_values_list_for_test_head_to_tail() == [144, 64, 36, 25, 16]
    assert cache._get_values_list_for_test_tail_to_head() == [16, 25, 36, 64, 144]


    assert cache.get(1) == -1
    assert cache._get_values_list_for_test_head_to_tail() == [144, 64, 36, 25, 16]
    assert cache._get_values_list_for_test_tail_to_head() == [16, 25, 36, 64, 144]

    assert cache.get(4) == 16
    assert cache._get_values_list_for_test_head_to_tail() == [16, 144, 64, 36, 25]
    assert cache._get_values_list_for_test_tail_to_head() == [25, 36, 64, 144, 16]

    cache.put(4, 4)
    assert cache.get(4) == 4
    assert cache._get_values_list_for_test_head_to_tail() == [4, 144, 64, 36, 25]
    assert cache._get_values_list_for_test_tail_to_head() == [25, 36, 64, 144, 4]

    assert cache.get(8) == 64
    assert cache._get_values_list_for_test_head_to_tail() == [64, 4, 144, 36, 25]
    assert cache._get_values_list_for_test_tail_to_head() == [25, 36, 144, 4, 64]


if __name__ == "__main__":
    smoke_test()
    print("All tests passed.")
