/*
You are given a m x n 2D integer array grid and an integer k. You start at the top-left cell (0, 0) and your goal is to reach the bottom‐right cell (m - 1, n - 1).

There are two types of moves available:

Normal move: You can move right or down from your current cell (i, j), i.e. you can move to (i, j + 1) (right) or (i + 1, j) (down). The cost is the value of the destination cell.

Teleportation: You can teleport from any cell (i, j), to any cell (x, y) such that grid[x][y] <= grid[i][j]; the cost of this move is 0. You may teleport at most k times.

Return the minimum total cost to reach cell (m - 1, n - 1) from (0, 0).
*/

using pii = pair<int,int>;
// author: Nabajyoti
class Solution {
public:
    const int inf = 1e9;

    int binSearch(vector<pii>& v, int val) {
        int ans = -1;
        int lo = 0, hi = v.size() - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (v[mid].first >= val) {
                ans = mid;
                hi = mid-1;
            } else {
                lo = mid+1;
            }
        }
        return ans;
    }

    int minCost(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size();
        
        // dp[i][j][kk] = minimum cost to reach (i,j) using at most kk teleportations
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k + 1, inf)));
        
        // Base case: starting position
        for (int kk = 0; kk <= k; kk++) {
            dp[0][0][kk] = 0;
        }
        
        
        for (int kk = 0; kk <= k; kk++) {
            vector<pii> cells;  
            vector<int> suffixMin;
            // If we can teleport, collect all reachable cells from kk-1 teleportations
            if (kk > 0) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        if (dp[i][j][kk-1] < inf) {
                            cells.push_back({grid[i][j], dp[i][j][kk-1]});
                        }
                    }
                }
                sort(cells.begin(), cells.end());
                
                // Create suffix minimum array for efficient range minimum queries
                suffixMin.resize(cells.size());
                if (!cells.empty()) {
                    suffixMin[cells.size()-1] = cells[cells.size()-1].second;
                    for (int i = cells.size()-2; i >= 0; i--) {
                        suffixMin[i] = min(cells[i].second, suffixMin[i+1]);
                    }
                }
            }
            
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (i == 0 && j == 0) continue;  // Already initialized
                    
                    int res = inf;
                    
                    // Normal moves (right and down)
                    if (i > 0) {
                        res = min(res, dp[i-1][j][kk] + grid[i][j]);
                    }
                    if (j > 0) {
                        res = min(res, dp[i][j-1][kk] + grid[i][j]);
                    }
                    
                    // teleport
                    if (kk > 0 && !cells.empty()) {
                        // Find all cells with value >= grid[i][j] (can teleport from them)
                        int idx = binSearch(cells, grid[i][j]);
                        if (idx >= 0) {
                            // Get minimum cost among all valid teleportation sources
                            res = min(res, suffixMin[idx]);  // Cost is destination cell value
                        }
                    }
                    
                    dp[i][j][kk] = res;
                }
            }
        }
        
        // Return minimum cost using at most k teleportations
        int result = inf;
        for (int kk = 0; kk <= k; kk++) {
            result = min(result, dp[n-1][m-1][kk]);
        }
        return result;
    }
};
