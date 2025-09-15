/*
You are given an integer array nums.

A subsequence is stable if it does not contain three consecutive elements with the same parity when the subsequence is read in order (i.e., consecutive inside the subsequence).

Return the number of stable subsequences.

Since the answer may be too large, return it modulo 109 + 7.

 

Example 1:

Input: nums = [1,3,5]

Output: 6

Explanation:

Stable subsequences are [1], [3], [5], [1, 3], [1, 5], and [3, 5].
Subsequence [1, 3, 5] is not stable because it contains three consecutive odd numbers. Thus, the answer is 6.
Example 2:

Input: nums = [2,3,4,2]

Output: 14

Explanation:

The only subsequence that is not stable is [2, 4, 2], which contains three consecutive even numbers.
All other subsequences are stable. Thus, the answer is 14.
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 10​​​​​​​5
*/

using ll = long long;
#define N 100005

class Solution {
public:
    const ll mod = 1e9 + 7;

    int countStableSubsequences(vector<int>& nums) {
        int n = nums.size();
        vector<vector<array<ll, 3>>> dp(n + 1,
                                        vector<array<ll, 3>>(3, {0, 0, 0}));
        for (int p = 0; p < 3; p++)
            for (int k = 0; k < 3; k++)
                dp[n][p][k] = 1;
        for (int i = n - 1; i >= 0; --i) {
            int cur = nums[i] % 2;
            for (int p = 0; p < 3; p++) {
                for (int k = 0; k < 3; k++) {
                    ll take = 0;
                    if (p == 2) {
                        take = dp[i + 1][cur][1];
                    } else if (p == cur) {
                        if (k < 2)
                            take = dp[i + 1][cur][k + 1];
                    } else {
                        take = dp[i + 1][cur][1];
                    }
                    ll skip = dp[i + 1][p][k];
                    dp[i][p][k] = (take + skip) % mod;
                }
            }
        }
        ll ans = dp[0][2][0] - 1;
        if (ans < 0)
            ans += mod;
        return (int)ans;
    }
};
