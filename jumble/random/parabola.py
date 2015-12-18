class Point(object):
    """docstring for Ve"""
    self.x = 0
    self.y = 0

def parabola_vertex(a, b, c):
    det_abc = b.x*b.x*c.x - b.x*c.x*c.x - a.x*a.x*c.x + a.x*c.x*c.x + a.x*a.x*b.x - a.x*b.x*b.x
    det_x1 = b.y*c.x - b.x*c.y - a.y*c.x + a.x*c.y + a.y*b.x - a.x*b.y
    det_x2 = b.x*b.x*c.y - b.y*c.x*c.x - a.x*a.x*c.y + a.y*c.x*c.x + a.x*a.x*b.y - a.y*b.x*b.x
        