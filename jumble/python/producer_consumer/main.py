
import random
import time

from threading import Lock
from threading import Thread


class CubbyHole(object):
    def __init__(self):
        super().__init__()
        self._queue = []
        self._lock = Lock()

    def put(self, value):
        with self._lock:
            self._queue.append(value)

    def get(self):
        with self._lock:
            if self._queue:
                return self._queue.pop(0)
            else:
                return None


class ProducerThread(Thread):
    def __init__(self, cubby_hole):
        super().__init__()
        self._cubby_hole = cubby_hole

    def run(self):
        nums = range(5)
        for _ in range(10):
            num = random.choice(nums)
            self._cubby_hole.put(num)
            print("Produced", num)
            time.sleep(random.uniform(0.1, 2.0))


class ConsumerThread(Thread):
    def __init__(self, cubby_hole):
        super().__init__()
        self._cubby_hole = cubby_hole

    def run(self):
        to_consume = 10
        while to_consume > 0:
            val = self._cubby_hole.get()
            if val is not None:
                to_consume -= 1
            print("\tConsumed", val)
            time.sleep(random.uniform(0.1, 2.0))


if __name__ == '__main__':
    ch = CubbyHole()
    pt = ProducerThread(ch)
    ct = ConsumerThread(ch)
    pt.start()
    ct.start()
