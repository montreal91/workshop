
import math


class Vector2(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, vec):
        return Vector2(self.x + vec.x, self.y + vec.y)


def circle(center, radius, segments):
    alpha = math.pi / segments
    line = "{0:8.4f} {1:8.4f}"
    for i in range(segments + 1):
        print(line.format(
            radius * math.cos(i * alpha) + center.x,
            radius * math.sin(i * alpha) + center.y
        ))


if __name__ == "__main__":
    import sys
    center = Vector2(float(sys.argv[1]), float(sys.argv[2]))
    circle(center, float(sys.argv[3]), int(sys.argv[4]))
