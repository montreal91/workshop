import socket

MSG_LEN = 13


class MySocket:
    def __init__(self, host, port):
        self.host = host
        self.port = port

        self.socket_io = socket.SocketIO(self._get_connection(), mode="rw")

        # if sock is None:
        #     self.sock = socket.SocketIO(socket.socket(socket.AF_INET, socket.SOCK_STREAM), mode="rw")
        # else:
        #     self.sock = socket.SocketIO(sock, mode="rw")

    def connect(self):
        self.disconnect()

        self.socket_io = socket.SocketIO(self._get_connection(), mode="rw")

    def disconnect(self):
        self.socket_io.close()

    def my_send(self, msg):
        # total_sent = 0
        # while total_sent < MSG_LEN:
        #     sent = self.sock.send(msg[total_sent:])
        #     if sent == 0:
        #         raise RuntimeError("Socket connection is broken")
        #     total_sent += sent
        self.socket_io.write(msg)
        # self.sock.flush()

    def my_receive(self):
        b = bytearray()
        read = self.socket_io.readinto(b)
        return b.decode("utf-8")

    def _get_connection(self):
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((self.host, self.port))
        return sock


def quicktest():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect(("127.0.0.1", 3000))
        s.sendall(b"hello server\n")
        data = s.recv(1024)

    print(f"received {data!r}")


if __name__ == "__main__":
    # print("Hello World!")
    # ms = MySocket("127.0.0.1", 3000)
    # # ms.connect("127.0.0.1", 3000)
    # ms.my_send("hello server\n".encode("utf-8"))
    # print(ms.my_receive())
    # # s = socket.SocketIO()
    # ms.disconnect()
    quicktest()
