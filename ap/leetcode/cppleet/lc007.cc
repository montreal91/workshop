
#include <cmath>
#include <iostream>
#include <limits.h>
#include <string>

using namespace std;

class Solution {
public:
    int reverse(int x) {
        cout << "in : " << x << endl;
        auto sign = 1;
        if (x < 0) {
            sign = -1;
        }
        auto s = to_string(abs(x));
        int res = 0;
        for (auto i=0; i<s.size(); i++) {
            int d = (s[i] - '0') * pow(10, i);
            res += d;
            if (res < 0) {
                return 0;
            }
        }
        return res * sign;
    }
};


int main(int argc, char const *argv[]) {
    Solution s;
    cout << "out: " << s.reverse(1534236469) << endl;
    return 0;
}
