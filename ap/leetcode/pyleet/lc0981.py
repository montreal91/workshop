# 7:00
# 8:05

class TimeMap:

    def __init__(self):
        self._storage = {}


    def set(self, key: str, value: str, timestamp: int) -> None:
        self._storage.setdefault(key, ([], []))
        slot = self._storage[key]
        pos = find_pos_to_insert(slot[0], timestamp)
        slot[0].insert(pos, timestamp)
        slot[1].insert(pos, value)


    def get(self, key: str, timestamp: int) -> str:
        self._storage.setdefault(key, ([], []))
        slot = self._storage[key]
        pos = find_pos_to_get(slot[0], timestamp)
        if pos == -1:
            return ""
        return slot[1][pos]

    def _find_pos_to_insert(self, timestamps, timestamp):
        if len(timestamps) == 0:
            return 0

        left = 0
        right = len(timestamps) - 1
        mid = (left + right) // 2

        while True:
            if timestamps[mid - 1] <= timestamp and timestamps[mid] > timestamp:
                return mid


def find_pos_to_insert(stamps, t):
    if len(stamps) == 0:
        return 0

    left = 0
    right = len(stamps) - 1

    if t < stamps[left]:
        return 0

    if stamps[right] < t:
        return len(stamps)

    while True:
        mid = (left + right) // 2
        if stamps[mid] == t:
            return -1

        if stamps[mid - 1] < t < stamps[mid]:
            return mid

        if stamps[mid] < t:
            left = mid + 1
        else:
            right = mid - 1


def find_pos_to_get(stamps, t):
    if len(stamps) == 0:
        return -1

    left = 0
    right = len(stamps) - 1

    if t < stamps[left]:
        return -1

    if stamps[right] <= t:
        return right

    while True:
        mid = (left + right) // 2

        if stamps[mid] <= t < stamps[mid + 1]:
            return mid

        if stamps[mid] < t:
            left = mid + 1
        else:
            right = mid - 1


if __name__ == "__main__":
    assert find_pos_to_insert([], 1) == 0
    assert find_pos_to_insert([1], 7) == 1
    assert find_pos_to_insert([1, 7], 7) == -1
    assert find_pos_to_insert([1, 7], 4) == 1
    assert find_pos_to_insert([1, 4, 7], 3) == 1
    assert find_pos_to_insert([1, 3, 4, 7], 9) == 4
    assert find_pos_to_insert([1, 3, 4, 7, 9], 6) == 3
    assert find_pos_to_insert([1, 3, 5, 7, 9], 0) == 0
    assert find_pos_to_insert([1, 3, 5, 7, 9], 2) == 1
    assert find_pos_to_insert([1, 3, 5, 7, 9], 4) == 2
    assert find_pos_to_insert([1, 3, 5, 7, 9], 6) == 3
    assert find_pos_to_insert([1, 3, 5, 7, 9], 8) == 4
    assert find_pos_to_insert([1, 3, 5, 7, 9], 10) == 5
    assert find_pos_to_insert([1, 3, 5, 7], 0) == 0
    assert find_pos_to_insert([1, 3, 5, 7], 2) == 1
    assert find_pos_to_insert([1, 3, 5, 7], 4) == 2
    assert find_pos_to_insert([1, 3, 5, 7], 6) == 3
    assert find_pos_to_insert([1, 3, 5, 7], 8) == 4

    assert find_pos_to_get([], 1) == -1
    assert find_pos_to_get([1, 3, 5, 7], 0) == -1
    assert find_pos_to_get([1, 3, 5, 7], 1) == 0
    assert find_pos_to_get([1, 3, 5, 7], 2) == 0
    assert find_pos_to_get([1, 3, 5, 7], 3) == 1
    assert find_pos_to_get([1, 3, 5, 7], 4) == 1
    assert find_pos_to_get([1, 3, 5, 7], 5) == 2
    assert find_pos_to_get([1, 3, 5, 7], 6) == 2
    assert find_pos_to_get([1, 3, 5, 7], 7) == 3
    assert find_pos_to_get([1, 3, 5, 7], 8) == 3
    print("All tests passed.")