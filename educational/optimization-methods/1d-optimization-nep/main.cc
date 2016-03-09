
#include <iostream>
#include <functional>

#include "tests.h"

using namespace std;

struct Point {
    double x, y;
};

double get_parabola_vertex(const Point& a, const Point& b, const Point& c) {
    double det_abc = b.x*b.x*c.x - b.x*c.x*c.x - a.x*a.x*c.x + a.x*c.x*c.x + a.x*a.x*b.x - a.x*b.x*b.x;
    double det_x1 = b.y*c.x - b.x*c.y - a.y*c.x + a.x*c.y + a.y*b.x - a.x*b.y;
    double det_x2 = b.x*b.x*c.y - b.y*c.x*c.x - a.x*a.x*c.y + a.y*c.x*c.x + a.x*a.x*b.y - a.y*b.x*b.x;
    double coef_a = det_x1 / det_abc;
    double coef_b = det_x2 / det_abc;
    return - coef_b / (2 * coef_a);
}

double find_min(double start, double end, double eps, function<double(double)> target) {
    while((end-start) > eps) {
        double mid = (start + end) / 2;
        Point a, b, c;
        a.x = start;
        a.y = target(start);
        b.x = mid;
        b.y = target(mid);
        c.x = end;
        c.y = target(end);
        double v = get_parabola_vertex(a, b, c);
        printf(
            "%.4f %.4f %.4f %.4f %.4f %.4f %.4f\n",
            start,
            target(start),
            mid,
            target(mid),
            end,
            target(end),
            v
        );
        if (v < mid) end = mid;
        else start = mid;
    }
    return (start + end) / 2;
}

int main(int argc, char const *argv[]) {
    printf("%.4f\n", find_min(0, 1, 0.01, test_1));
    printf("%.4f\n", find_min(-2, 3, 0.01, test_1));
    return 0;
}
