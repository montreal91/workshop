
import time
from multiprocessing import Pipe
from multiprocessing import Process
from multiprocessing import Queue
from typing import Any
from typing import Dict
from typing import List


class Counter(object):
    _i: int

    def __init__(self):
        super().__init__()
        self._i = 0

    def drop(self):
        self._i = 0

    def inc(self):
        self._i += 1

    @property
    def i(self) -> int:
        return self._i


class Action(object):
    _data: Dict[str, Any]
    _label: str

    def __init__(self, label: str, data: Dict[str, Any]):
        super().__init__()
        self._data = data
        self._label = label

    @property
    def data(self) -> Dict[str, Any]:
        return self._data

    @property
    def label(self) -> str:
        return self._label


class CounterProcess(Process):
    _counters: Dict[str, Counter]
    _in_queue: Queue
    _out_queue: Queue

    def __init__(self, in_queue: Queue, out_queue: Queue):
        super().__init__()
        self._in_queue = in_queue
        self._out_queue = out_queue
        self._counters = {}
        self._counters["a"] = Counter()
        self._counters["b"] = Counter()

    def run(self):
        for i in range(15):
            time.sleep(0.5)
            self._process_actions()
            self._update()
            self._emit()

    def _dispatch_action(self, action: Action):
        if action.label != "drop":
            return
        if "label" not in action.data:
            return
        self._drop_counter(action.data["label"])

    def _drop_counter(self, label: str):
        if label in self._counters:
            self._counters[label].drop()

    def _emit(self):
        msg = {}
        for c in self._counters:
            msg[c] = self._counters[c].i
        self._out_queue.put(msg)

    def _get_actions(self) -> List[Action]:
        actions = []
        while not self._in_queue.empty():
            actions.append(self._in_queue.get(False))
        return actions

    def _process_actions(self):
        for action in self._get_actions():
            self._dispatch_action(action)

    def _update(self):
        for c in self._counters.values():
            c.inc()


def print_output(queue: Queue, to_receive: int, dt: float):
    while to_receive > 0:
        if not queue.empty():
            print(queue.get(False))
            to_receive -= 1
        time.sleep(dt)


if __name__ == '__main__':
    oq = Queue()
    iq = Queue()

    proc = CounterProcess(iq, oq)
    proc.start()

    print_output(oq, 5, 0.1)

    iq.put(Action(label="drop", data=dict(label="a")))

    # Try to send incorrect actions
    iq.put(Action(label="notdrop", data=dict(lbl="b")))
    iq.put(Action(label="drop", data=dict()))

    print()
    print_output(oq, 5, 0.1)

    iq.put(Action(label="drop", data=dict(label="b")))

    print()
    print_output(oq, 5, 0.1)

    proc.join()
