/*
Given an integer n, return the number of ways you can write n as the sum of consecutive positive integers.

 

Example 1:

Input: n = 5
Output: 2
Explanation: 5 = 2 + 3
Example 2:

Input: n = 9
Output: 3
Explanation: 9 = 4 + 5 = 2 + 3 + 4
Example 3:

Input: n = 15
Output: 4
Explanation: 15 = 8 + 7 = 4 + 5 + 6 = 1 + 2 + 3 + 4 + 5
*/

using ll = long long;

class Solution {
public:
    string encode(ll a, ll b) { return to_string(a) + "," + to_string(b); }
    int consecutiveNumbersSum(int a) {
        set<string> st;
        ll A = 2 * a;
        for (ll i = 1; i * i <= A; i++) {
            if (A % i == 0) {
                ll x = i;
                ll y = (A / i);

                if (x > y)
                    swap(x, y);

                ll N = (x + y - 1);
                ll M = (y - x - 1);
                if (N % 2 || M % 2)
                    continue;
                N /= 2;
                M /= 2;
                if (N >= 0 && M >= 0 && N >= M) {
                    st.insert(encode(N, M));
                }
            }
        }
        return (int)st.size();
    }
};
