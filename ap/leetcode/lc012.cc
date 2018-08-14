
#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        auto s = to_string(num);
        string res = "";
        for (auto i=0; i < s.size(); i++) {
            res += digitToRoman(s[i] - '0', s.size() - i - 1);
        }
        return res;
    }

private:
    typedef unordered_map<int, string> RomanMap;

    RomanMap digits = {
        {1, "I"},
        {5, "V"},
        {10, "X"},
        {50, "L"},
        {100, "C"},
        {500, "D"},
        {1000, "M"},
    };

    string fours[3] = {"IV", "XL", "CD"};
    string nines[3] = {"IX", "XC", "CM"};

    string digitToRoman(int digit, int pos) {
        string res = "";
        if (digit == 0) {
            return res;
        }
        if (digit == 9) {
            return nines[pos];
        }
        if (digit == 4) {
            return fours[pos];
        }
        if (digit >= 5) {
            res += digits[5 * pow(10, pos)];
            digit -= 5;
        }
        for (int i=0; i < digit; i++) {
            res += digits[pow(10, pos)];
        }
        return res;
    }
};

int main() {
    Solution slt;
    for (int i=1; i<10; i++) {
        cout << i << " " << slt.intToRoman(i) << endl;
    }
    for (int i=1; i<10; i++) {
        cout << i * 10 << " " << slt.intToRoman(i * 10) << endl;
    }
    for (int i=1; i<10; i++) {
        cout << i * 100 << " " << slt.intToRoman(i * 100) << endl;
    }
    cout << 1000 << " " << slt.intToRoman(1000) << endl;
    cout << 2000 << " " << slt.intToRoman(2000) << endl;
    cout << 3000 << " " << slt.intToRoman(3000) << endl;

    cout << 804 << " " << slt.intToRoman(804) << endl;
    cout << 58 << " " << slt.intToRoman(58) << endl;
    cout << 1994 << " " << slt.intToRoman(1994) << endl;

    return 0;
}
