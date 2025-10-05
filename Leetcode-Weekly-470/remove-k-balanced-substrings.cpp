/*
You are given a string s consisting of '(' and ')', and an integer k.

A string is k-balanced if it is exactly k consecutive '(' followed by k consecutive ')', i.e., '(' * k + ')' * k.

For example, if k = 3, k-balanced is "((()))".

You must repeatedly remove all non-overlapping k-balanced substrings from s, and then join the remaining parts. Continue this process until no k-balanced substring exists.

Return the final string after all possible removals.

A substring is a contiguous non-empty sequence of characters within a string.

*/

using pci = pair<char, int>;
#define ff first
#define ss second

class Solution {
public:
    void tryMerge(vector<pci>& v, int k) {
        if (v.size() < 2)
            return;
        int n = v.size();
        pci a = v[n - 2], b = v[n - 1];
        if (!(a.ff == '(' && b.ff == ')'))
            return;
        if (a.ss < k || b.ss < k)
            return;
        v.pop_back();
        v.pop_back();
        int z = min(a.ss, b.ss);
        int remove = (z / k) * k;
        a.ss -= remove;
        b.ss -= remove;
        if (a.ss > 0)
            v.push_back(a);
        if (b.ss > 0)
            v.push_back(b);
    }

    string removeSubstring(string s, int k) {
        vector<pci> v;

        for (char c : s) {
            if (v.size() == 0) {
                pci temp = {c, 1};
                v.push_back(temp);
                continue;
            }
            if (v.back().ff == c) {
                v.back().ss++;
            } else {
                pci temp = {c, 1};
                v.push_back(temp);
            }

            tryMerge(v, k);
        }

        string ans = "";
        for (auto it : v) {
            for (int j = 0; j < it.ss; j++) {
                ans += it.ff;
            }
        }
        return ans;
    }
};
