/*
Given an array of unique integers, arr, where each integer arr[i] is strictly greater than 1.

We make a binary tree using these integers, and each number may be used for any number of times. Each non-leaf node's value should be equal to the product of the values of its children.

Return the number of binary trees we can make. The answer may be too large so return the answer modulo 109 + 7.
*/

using ll = long long;

class Solution {
public:
    const ll mod = 1e9+7;
    int numFactoredBinaryTrees(vector<int>& arr) {
        int n = arr.size();
        sort(arr.begin(), arr.end());

        unordered_map<ll,ll> dp;
        dp[1] = 1;
        for(int i=0;i<n;i++) {
            ll ans = 1;
            for(int j=i-1;j>=0;j--) {
                if(arr[i]%arr[j]==0) {
                    ll a = arr[j];
                    ll b = arr[i]/arr[j];
                    if(dp.find(a)!=dp.end()) {
                        ans+= dp[a]*dp[b];
                        ans%=mod;
                    }
                }
            }
            dp[arr[i]] = ans;
        }

        ll res = 0;
        for(int i=0;i<n;i++) {
            res+= dp[arr[i]];
            res%=mod;
        }
        return (int) res;
    }
};
