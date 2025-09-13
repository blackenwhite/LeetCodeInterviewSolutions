/*
You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.

Return the size of the largest island in grid after applying this operation.

An island is a 4-directionally connected group of 1s.

 

Example 1:

Input: grid = [[1,0],[0,1]]
Output: 3
Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
Example 2:

Input: grid = [[1,1],[1,0]]
Output: 4
Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.
Example 3:

Input: grid = [[1,1],[1,1]]
Output: 4
Explanation: Can't change any 0 to 1, only one island with area = 4.
*/

using pii = pair<int,int>;

class Solution {
public:
    int dirs[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    vector<vector<int>> mat;

    void dfs(int x, int y, int parx, int pary,
             vector<vector<bool>>& visited,
             map<pii, pii>& parent,
             map<pii, int>& size) {
        visited[x][y] = true;
        parent[{x,y}] = {parx, pary};
        size[{parx, pary}]++;

        int n = mat.size();
        int m = mat[0].size();

        for(int k=0;k<4;k++){
            int nx = x+dirs[k][0];
            int ny = y+dirs[k][1];

            if(nx>=0 && nx<n && ny>=0 && ny<m &&
               mat[nx][ny]==1 && !visited[nx][ny]) {
                dfs(nx, ny, parx, pary, visited, parent, size);
            }
        }
    }

    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        mat = grid;

        map<pii, pii> parent;  // {x,y} -> root of its island
        map<pii, int> size;    // {rootx,rooty} -> size of island
        vector<vector<bool>> visited(n, vector<bool>(m, false));

        int ans = 0;

        // Step 1: find all islands and their sizes
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                if(grid[i][j]==1 && !visited[i][j]) {
                    dfs(i, j, i, j, visited, parent, size);
                    ans = max(ans, size[{i,j}]);
                }
            }
        }

        // Step 2: try flipping each 0
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                if(mat[i][j]==0) {
                    int temp = 1; // flip this 0
                    set<pii> seen;
                    for(int k=0;k<4;k++) {
                        int nx = i+dirs[k][0];
                        int ny = j+dirs[k][1];
                        if(nx>=0 && nx<n && ny>=0 && ny<m &&
                           mat[nx][ny]==1) {
                            auto root = parent[{nx, ny}];
                            if(seen.insert(root).second) { // only add once
                                temp += size[root];
                            }
                        }
                    }
                    ans = max(ans, temp);
                }
            }
        }

        return ans;
    }
};
