class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res=0;
        for (auto i=1;i<prices.size();i++){
            if (prices[i]-prices[i-1]>0)
                res+=prices[i]-prices[i-1];
        }
        return res;
        
    }
};