
//
// I didn't solve this problem within 2 hours.
// This solution is based on Java Solution 1 from
// https://www.programcreek.com/2014/03/leetcode-house-robber-java/
//

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }
        if (nums.size() == 1) {
            return nums[0];
        }
        vector<int> dp(nums);
        dp[1] = max(nums[0], nums[1]);

        for (auto i=2; i < nums.size(); i++) {
            dp[i] = max(dp[i-2]+nums[i], dp[i-1]);
        }
        return dp[dp.size() - 1];
    }
};


int main() {
    Solution s;
    vector<int> v = {2, 3, 2};
    cout << s.rob(v) << endl;
    return 0;
}
