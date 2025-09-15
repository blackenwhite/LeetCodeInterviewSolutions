/*
You are given an integer array nums of size n and a positive integer k.

An array capped by value x is obtained by replacing every element nums[i] with min(nums[i], x).

For each integer x from 1 to n, determine whether it is possible to choose a subsequence from the array capped by x such that the sum of the chosen elements is exactly k.

Return a 0-indexed boolean array answer of size n, where answer[i] is true if it is possible when using x = i + 1, and false otherwise.

 

Example 1:

Input: nums = [4,3,2,4], k = 5

Output: [false,false,true,true]

Explanation:

For x = 1, the capped array is [1, 1, 1, 1]. Possible sums are 1, 2, 3, 4, so it is impossible to form a sum of 5.
For x = 2, the capped array is [2, 2, 2, 2]. Possible sums are 2, 4, 6, 8, so it is impossible to form a sum of 5.
For x = 3, the capped array is [3, 3, 2, 3]. A subsequence [2, 3] sums to 5, so it is possible.
For x = 4, the capped array is [4, 3, 2, 4]. A subsequence [3, 2] sums to 5, so it is possible.
Example 2:

Input: nums = [1,2,3,4,5], k = 3

Output: [true,true,true,true,true]

Explanation:

For every value of x, it is always possible to select a subsequence from the capped array that sums exactly to 3.

 

Constraints:

1 <= n == nums.length <= 4000
1 <= nums[i] <= n
1 <= k <= 4000

*/
class Solution {
public:
    int binSearch(vector<int>& v, int x) {
        int ans = -1;
        int lo = 0, hi = v.size() - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (v[mid] <= x) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return ans;
    }

    vector<bool> subsequenceSumAfterCapping(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(k + 1, false));
        dp[0][0] = true;

        for (int ind = 0; ind < n; ind++) {
            for (int j = 0; j <= k; j++) {
                bool ans = dp[ind][j];
                if (j >= nums[ind]) {
                    ans = ans || dp[ind][j - nums[ind]];
                }
                dp[ind + 1][j] = ans;
            }
        }

        vector<bool> res;

        for (int cap = 1; cap <= n; cap++) {
            bool ans = false;
            int ind = binSearch(nums, cap); // last index <= cap
            ind++;

            for (int m = 0; m <= min(k / cap, n-ind); m++) {
                int rem = k - m * cap;
                if (rem < 0) break;
                if (dp[ind][rem]) {
                    // printf("this works! m=%d, dp[%d][%d]=%d \n", m, ind, rem, dp[ind][rem]);
                    ans = true;
                    break;
                }
            }
            res.push_back(ans);
        }
        return res;
    }
};
