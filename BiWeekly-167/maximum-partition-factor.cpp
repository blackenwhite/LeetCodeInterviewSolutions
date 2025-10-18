/*
You are given a 2D integer array points, where points[i] = [xi, yi] represents the coordinates of the ith point on the Cartesian plane.

The Manhattan distance between two points points[i] = [xi, yi] and points[j] = [xj, yj] is |xi - xj| + |yi - yj|.

Split the n points into exactly two non-empty groups. The partition factor of a split is the minimum Manhattan distance among all unordered pairs of points that lie in the same group.

Return the maximum possible partition factor over all valid splits.

Note: A group of size 1 contributes no intra-group pairs. When n = 2 (both groups size 1), there are no intra-group pairs, so define the partition factor as 0.

Key Learnings:
1. Use binary Search on ans
2. for each candidate D, check if it is possible to split into two partitions (using bipartiteness)
*/

using ll = long long;
using pii = pair<ll, ll>;

class Solution {
public:
    bool isBipartite(vector<vector<ll>>& adj) {
        int n = adj.size();
        vector<ll> color(n, -1);
        for (ll i = 0; i < n; i++) {
            if (color[i] == -1) {
                color[i] = 0;
                // bool possible = bfs(adj, color);
                queue<ll> q;
                q.push(i);
                while (q.size() > 0) {
                    ll cur = q.front();
                    q.pop();
                    for (auto it : adj[cur]) {
                        if (color[it] == -1) {
                            color[it] = (1 + color[cur]) % 2;
                            q.push(it);
                        } else if (color[it] == color[cur])
                            return false;
                    }
                }
            }
        }
        return true;
    }
    bool check(int k, vector<pii>& v) {
        int n = v.size();
        vector<vector<ll>> adj; // adjacency list
        adj.assign(n, {});

        for (ll i = 0; i < n; i++) {
            for (ll j = i + 1; j < n; j++) {
                ll dist = abs(v[i].first - v[j].first) +
                          abs(v[i].second - v[j].second);
                if (dist < k) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        return isBipartite(adj);
    }
    int maxPartitionFactor(vector<vector<int>>& points) {
        if (points.size() <= 2)
            return 0;
        vector<pii> v;
        for (auto it : points) {
            v.push_back({it[0], it[1]});
        }
        ll ans = -1;
        ll lo = 0, hi = 1e10;
        while (lo <= hi) {
            ll mid = (lo + hi) / 2;
            if (check(mid, v)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return ans;
    }
};
