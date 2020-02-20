class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        if(nums.size()==0 || nums.size()<k)
            return -1;
        priority_queue<int,vector<int>,greater<int>> pt;
        for (auto i:nums){
            pt.push(i);
            if (pt.size()>k)
                pt.pop();
            
        }
        return pt.top();
        
    }
};