/*
A company is organizing a meeting and has a list of n employees, waiting to be invited. They have arranged for a large circular table, capable of seating any number of employees.

The employees are numbered from 0 to n - 1. Each employee has a favorite person and they will attend the meeting only if they can sit next to their favorite person at the table. The favorite person of an employee is not themself.

Given a 0-indexed integer array favorite, where favorite[i] denotes the favorite person of the ith employee, return the maximum number of employees that can be invited to the meeting.
*/

using pii = pair<int, int>;

class Solution {
public:
    int maximumInvitations(vector<int>& favorite) {
        return max(findMaxCycle(favorite), topoSort(favorite));
    }

    int findMaxCycle(vector<int>& fav) {
        int n = fav.size();
        vector<int> seen(n, 0); // 0 = not processed yet, 1 = processed
        int ans = 0;

        for (int i = 0; i < n; ++i) {
            if (seen[i])
                continue;
            unordered_map<int, int> local; // node -> depth in this traversal
            int cur = i;
            int depth = 0;
            while (local.find(cur) == local.end() && !seen[cur]) {
                local[cur] = depth++;
                cur = fav[cur];
            }
            // if cur is in local, we found a cycle that lies inside this
            // traversal
            if (local.find(cur) != local.end()) {
                ans = max(ans, depth - local[cur]);
            }
            // mark all nodes visited in this traversal as globally seen
            for (auto& p : local)
                seen[p.first] = 1;
        }
        return ans;
    }

    int dfs(pii node, vector<int>& fav, unordered_map<int, int>& visited) {
        visited[node.first] = node.second;
        int next = fav[node.first];

        if (visited.find(next) != visited.end()) {
            return node.second - visited[next] + 1;
        } else {
            return dfs({next, node.second + 1}, fav, visited);
        }
    }

    int topoSort(vector<int>& fav) {
        int n = fav.size();
        vector<int> indeg(n);
        for (int i = 0; i < n; i++) {
            indeg[fav[i]]++;
        }

        vector<int> dist(n, 1);
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indeg[i] == 0) {
                q.push(i);
            }
        }

        while (q.size() > 0) {
            int cur = q.front();
            q.pop();
            int next = fav[cur];
            dist[next] = max(dist[next], dist[cur] + 1);
            --indeg[next];
            if (indeg[next] == 0) {
                q.push(next);
            }
        }

        int ans = 0;
        for (int i = 0; i < n; i++) {
            // cout<<dist[i]<<"\n";
            if (fav[fav[i]] == i) {
                // cout<<"hello at i= "<<i<<"\n";
                ans += dist[i];
            }
        }
        return ans;
    }
};
