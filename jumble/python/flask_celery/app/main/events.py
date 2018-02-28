
import time
from threading import Thread
from app import socketio

namespace = "/test/"


pings = 0


class CountdownThread(Thread):
    _threadholder = {}
    def __init__(self, loops, emitter, namespace):
        super(CountdownThread, self).__init__()
        self._loops = loops
        self._emitter = emitter
        self._namespace = namespace

    def run(self):
        for i in range(self._loops):
            time.sleep(1)
            self._emitter.emit(
                "countdown",
                {"remaining": 12 - i},
                namespace=self._namespace
            )
        CountdownThread.destroy_thread(self._namespace)

    @staticmethod
    def create_thread(loops, emitter, namespace):
        if namespace in CountdownThread._threadholder:
            if CountdownThread._threadholder[namespace] is not None:
                return None
            else:
                cdt = CountdownThread(loops, emitter, namespace)
                CountdownThread._threadholder[namespace] = cdt
                return cdt
        else:
            cdt = CountdownThread(loops, emitter, namespace)
            CountdownThread._threadholder[namespace] = cdt
            return cdt

    @staticmethod
    def destroy_thread(namespace):
        if namespace in CountdownThread._threadholder:
            CountdownThread._threadholder[namespace] = None


@socketio.on("ping", namespace=namespace)
def ping():
    global pings
    pings += 1
    # print(pings)
    socketio.emit(
        "pong",
        {"message": "Pings: {}".format(pings)},
        namespace="/test/"
    )


@socketio.on("connect", namespace=namespace)
def connect():
    t = CountdownThread.create_thread(loops=13, emitter=socketio, namespace=namespace)
    if t:
        t.daemon = True
        t.start()
    socketio.emit(
        "pong",
        {"message": "Pings: {}".format(pings)},
        namespace="/test/"
    )

@socketio.on("start_countdown", namespace=namespace)
def start_countdown(message):
    # print(__name__)
    t = CountdownThread.create_thread(
        loops=message["loops"],
        emitter=socketio,
        namespace=namespace
    )
    if t:
        t.daemon = True
        t.start()
