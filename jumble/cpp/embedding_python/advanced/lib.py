
class Counter(object):
    def __init__(self):
        super().__init__()

        self._c = 0

    def __repr__(self):
        return "Simple Counter" + str(self._c)


    def Drop(self):
        self._c = 0

    def GetValue(self):
        return str(self._c)

    def Inc(self):
        self._c += 1
