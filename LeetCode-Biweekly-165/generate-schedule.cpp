/*
You are given an integer n representing n teams. You are asked to generate a schedule such that:

Each team plays every other team exactly twice: once at home and once away.
There is exactly one match per day; the schedule is a list of consecutive days and schedule[i] is the match on day i.
No team plays on consecutive days.
Return a 2D integer array schedule, where schedule[i][0] represents the home team and schedule[i][1] represents the away team. If multiple schedules meet the conditions, return any one of them.

If no schedule exists that meets the conditions, return an empty array.

 

Example 1:

Input: n = 3

Output: []

Explanation:

​​​​​​​Since each team plays every other team exactly twice, a total of 6 matches need to be played: [0,1],[0,2],[1,2],[1,0],[2,0],[2,1].

It's not possible to create a schedule without at least one team playing consecutive days.

Example 2:

Input: n = 5

Output: [[0,1],[2,3],[0,4],[1,2],[3,4],[0,2],[1,3],[2,4],[0,3],[1,4],[2,0],[3,1],[4,0],[2,1],[4,3],[1,0],[3,2],[4,1],[3,0],[4,2]]

Explanation:

Since each team plays every other team exactly twice, a total of 20 matches need to be played.

The output shows one of the schedules that meet the conditions. No team plays on consecutive days.

 

Constraints:

2 <= n <= 50​​​​​​​
*/

using pii = pair<int, int>;

class Solution {
public:
    vector<vector<int>> generateSchedule(int n) {
        if (n <= 4)
            return {};
        vector<vector<int>> rem(n, vector<int>(n, 1));

        int totalMatches = n * (n - 1);

        vector<pii> schedule;
        vector<int> remCount(n, 2 * (n - 1));

        function<bool(int, int, int)> dfs = [&](int day, int lastA, int lastB) {
            if (day == totalMatches)
                return true;
            vector<array<int, 2>> cands;
            int max_score = 0;

            for (int i = 0; i < n; i++) {
                if (i == lastA || i == lastB)
                    continue;
                for (int j = 0; j < n; j++) {
                    if (j == lastA || j == lastB || i == j || rem[i][j] == 0)
                        continue;
                    int score = remCount[i] + remCount[j];

                    if (score == max_score) {
                        cands.push_back({i, j});
                    }

                    if (score > max_score) {
                        max_score = score;
                        cands.clear();
                        cands.push_back({i, j});
                    }
                }
            }

            if (cands.size() == 0)
                return false;

            for (auto& cand : cands) {
                int i = cand[0], j = cand[1];
                rem[i][j] = 0;
                remCount[i]--;
                remCount[j]--;
                schedule.push_back({i, j});
                if (dfs(day + 1, i, j))
                    return true;

                schedule.pop_back();
                rem[i][j] = 1;
                remCount[i]++;
                remCount[j]++;
            }
            return false;
        };
        bool check = dfs(0, -1, -1);
        if (!check)
            return {}; // should never reach
        vector<vector<int>> ans;
        for (auto& p : schedule) {
            ans.push_back({p.first, p.second});
        }
        return ans;
    }
};
