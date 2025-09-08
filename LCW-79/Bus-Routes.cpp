/*
You are given an array routes representing bus routes where routes[i] is a bus route that the ith bus repeats forever.

For example, if routes[0] = [1, 5, 7], this means that the 0th bus travels in the sequence 1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ... forever.
You will start at the bus stop source (You are not on any bus initially), and you want to go to the bus stop target. You can travel between bus stops by buses only.

Return the least number of buses you must take to travel from source to target. Return -1 if it is not possible.

 

Example 1:

Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
Output: 2
Explanation: The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
Example 2:

Input: routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target = 12
Output: -1

*/

using ll = long long;

class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source,
                              int target) {
        if (source == target)
            return 0;

        map<ll, ll> dist;
        map<ll, vector<ll>> mp; // city -> [] of bus routes it is part of

        int n = routes.size();
        for (ll i = 0; i < n; i++) {
            for (ll j = 0; j < routes[i].size(); j++) {
                mp[routes[i][j]].push_back(i);
            }
        }

        map<ll, bool>
            visited; // tracks which bus route is already put in the queue
        map<ll, bool> cityVisited; // tracks which city ialready visited

        dist[source] = 0;
        cityVisited[source] = true;

        queue<ll> q;
        for (auto it : mp[source]) {
            visited[it] = true;
            q.push(it);
        }
        ll lvl = 1;

        while (q.size() > 0) {
            ll sz = q.size();
            while (sz--) {
                ll cur = q.front();
                q.pop();
                // get all the routes it is part of and put them in the queue if
                // not visited already
                for (auto city : routes[cur]) {
                    if (cityVisited.count(city))
                        continue;
                    cityVisited[city] = true;
                    dist[city] = lvl;
                    if (city == target)
                        return lvl;
                    for (auto x : mp[city]) {
                        if (!visited.count(x)) {
                            visited[x] = true;
                            q.push(x);
                        }
                    }
                }
            }
            lvl++;
        }
        return -1;
    }
};
