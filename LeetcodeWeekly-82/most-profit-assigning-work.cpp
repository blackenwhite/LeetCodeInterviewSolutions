/*
You have n jobs and m workers. You are given three arrays: difficulty, profit, and worker where:

difficulty[i] and profit[i] are the difficulty and the profit of the ith job, and
worker[j] is the ability of jth worker (i.e., the jth worker can only complete a job with difficulty at most worker[j]).
Every worker can be assigned at most one job, but one job can be completed multiple times.

For example, if three workers attempt the same job that pays $1, then the total profit will be $3. If a worker cannot complete any job, their profit is $0.
Return the maximum profit we can achieve after assigning the workers to the jobs.

 

Example 1:

Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
Output: 100
Explanation: Workers are assigned jobs of difficulty [4,4,6,6] and they get a profit of [20,20,30,30] separately.
Example 2:

Input: difficulty = [85,47,57], profit = [24,66,99], worker = [40,25,25]
Output: 0

*/

using pii = pair<int, int>;
class Solution {
public:
    int maxProfitAssignment(vector<int>& diff, vector<int>& p,
                            vector<int>& worker) {
        vector<pii> v;
        int n = diff.size();
        for (int i = 0; i < n; i++) {
            v.push_back({diff[i], p[i]});
        }

        sort(v.begin(), v.end());
        vector<int> maxProf(n);
        int maxx = -1e9;
        for (int i = 0; i < n; i++) {
            maxProf[i] = max(maxx, v[i].second);
            maxx = maxProf[i];
        }
        sort(worker.begin(), worker.end());
        int ind = 0;
        int ans = 0;
        for (int j = 0; j < worker.size(); j++) {
            // find best work
            while (ind < n && v[ind].first <= worker[j]) {
                ind++;
            }
            if (ind > 0) {
                ans += maxProf[ind - 1];
            }
        }
        return ans;
    }
};
