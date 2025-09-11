/*
Your car starts at position 0 and speed +1 on an infinite number line. Your car can go into negative positions. Your car drives automatically according to a sequence of instructions 'A' (accelerate) and 'R' (reverse):

When you get an instruction 'A', your car does the following:
position += speed
speed *= 2
When you get an instruction 'R', your car does the following:
If your speed is positive then speed = -1
otherwise speed = 1
Your position stays the same.
For example, after commands "AAR", your car goes to positions 0 --> 1 --> 3 --> 3, and your speed goes to 1 --> 2 --> 4 --> -1.

Given a target position target, return the length of the shortest sequence of instructions to get there.

©leetcode
*/

struct State {
    int pos;
    int speed;
    State(int p, int s) : pos(p), speed(s) {}
};

class Solution {
public:
    int racecar(int target) {
        if (target == 0) return 0;
        
        queue<State> q;
        unordered_set<string> visited;

        auto encode = [](int p, int s) {
            return to_string(p) + "," + to_string(s);
        };

        State init(0, 1);
        q.push(init);
        visited.insert(encode(0,1));

        int lvl = 0;

        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                State cur = q.front(); q.pop();

                if (cur.pos == target) return lvl;

                // 1/ Accelerate
                State nextA(cur.pos + cur.speed, cur.speed * 2);
                if (abs(nextA.pos) <= 2 * target) {
                    string keyA = encode(nextA.pos, nextA.speed);
                    if (!visited.count(keyA)) {
                        visited.insert(keyA);
                        q.push(nextA);
                    }
                }

                // 2/ Reverse
                int newSpeed = (cur.speed > 0) ? -1 : 1;
                State nextR(cur.pos, newSpeed);
                string keyR = encode(nextR.pos, nextR.speed);
                if (!visited.count(keyR)) {
                    visited.insert(keyR);
                    q.push(nextR);
                }
            }
            lvl++;
        }

        return -1; // Should never happen
    }
};©leetcode
