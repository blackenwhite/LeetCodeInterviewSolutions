/*
You are given an integer n representing the number of nodes in a directed weighted graph, numbered from 0 to n - 1. This is represented by a 2D integer array edges, where edges[i] = [ui, vi, wi] represents a directed edge from node ui to node vi with weight wi.

You are also given a string labels of length n, where labels[i] is the character assigned to node i, and an integer k.

Return the minimum total edge weight of a path from node 0 to node n - 1 such that the concatenation of the labels of the nodes along the path contains at most k consecutive identical characters. If no valid path exists, return -1.

Great question. Here are the key transferable concepts:

---

## 1. Dijkstra on Augmented State Space

The most important takeaway. Whenever shortest path has a **constraint that depends on history**, the trick is:

> **"What's the minimum extra information I need to carry to make the next decision?"**

Here it was `cnt` — you don't need the full path, just the consecutive count at the current node. This pattern appears everywhere:

- Shortest path with at most `k` edges → `state = (node, edges_used)`
- Shortest path where you can remove at most `k` edges → `state = (node, removals_left)`
- Shortest path with fuel constraints → `state = (node, fuel_remaining)`

The state space becomes `O(n * extra_dimension)` and Dijkstra runs on it exactly the same way.

---

## 2. "Count Up" vs "Count Down" State Design

You used `rem` (countdown), your friend used `cnt` (count up). The lesson:

- **Count up** toward a hard limit (`cnt == k` → block) is usually cleaner
- **Count down** from a budget (`rem <= 0` → block) is more natural for *resource consumption* problems (fuel, lives, removals)

Both are equivalent, but count-up tends to have fewer off-by-one errors for *run-length style* constraints like this one.

---

## 3. What Resets vs What Accumulates in State

In this problem:
- Same label → `cnt` **accumulates**
- Different label → `cnt` **resets to 1**

Recognizing this reset pattern is key. Ask yourself:

> *"Does crossing this edge/node reset my constraint, or does it accumulate?"*

Other examples of this pattern: problems where moving through certain node types resets a counter, or problems where you get a "free pass" under certain conditions.

---

## 4. Early Termination in Dijkstra

When you only care about `dist[target]` (not all nodes), you can return the moment the target is **first popped** from the priority queue — not when it's first *relaxed*. This is guaranteed to be optimal because Dijkstra pops in non-decreasing distance order.

```cpp
if (u == target) return (int)d;
```

This matters more when the state space is large, since you may avoid processing many states.

---

## 5. Flat 1D Array vs 2D Array for State

When your state is `(node, extra)`, you can store distances as:
- `dist[node][extra]` — 2D, readable
- `dist[node * S + extra]` — 1D, cache-friendly

For competitive programming, the 1D encoding is faster in practice because it's a single contiguous block of memory. Worth switching to when TLE is a concern.

---

## 6. The "Stale State" Lazy Deletion Pattern

```cpp
if (d > dist[u][cnt]) continue;
```

This is the standard way to avoid a decrease-key operation in Dijkstra. Always include it. The insight is: priority queues in C++ don't support updating priorities, so you push duplicates and skip outdated ones when popped.

---

## Mental Checklist for Future Problems

When you see a shortest/cheapest path problem with extra constraints, run through this:

```
1. What constraint makes this not-plain-Dijkstra?
2. What is the minimum state I need to track it?
3. Does the state reset or accumulate at each step?
4. What are the valid transitions + what do I block?
5. Can I early-exit at the target?
```

Mastering point 1 and 2 covers probably 80% of hard graph problems in competitive programming.


*/

using ll = long long;
using pii = pair<ll, ll>;
const ll inf = 1e18;

struct State {
    ll d;
    ll node;
    ll cnt;

    bool operator>(const State& other) const { return d > other.d; }
};

class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pii>> adj(n);
        for (auto& edge : edges) {
            ll u = edge[0], v = edge[1], w = edge[2];
            adj[u].push_back({v, w});
        }

        // cnt ranges from 1...k, so k states per node
        vector<vector<ll>> dist(n, vector<ll>(k + 1, inf));

        priority_queue<State, vector<State>, greater<State>> pq;

        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [d, u, cnt] = pq.top();
            pq.pop();

            if (d > dist[u][cnt])
                continue;

            // early exit: first time n-1 is popped, its guaranteed minimum
            if (u == n - 1)
                return (int)d;

            for (auto& [v, w] : adj[u]) {
                ll nextCnt;
                if (labels[v] == labels[u]) {
                    if (cnt == k)
                        continue;
                    nextCnt = cnt + 1;
                } else {
                    nextCnt = 1;
                }

                if (dist[v][nextCnt] > d + w) {
                    dist[v][nextCnt] = d + w;
                    pq.push({d + w, v, nextCnt});
                }
            }
        }
        return -1;
    }
};
