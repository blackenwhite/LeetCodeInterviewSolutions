class Solution:
    def singleNumber(self, nums: List[int]) -> int:
        count={}
        for i in nums:
            if i not in count:
                count[i]=1
            else:
                count[i]+=1
        
        for i in count:
            if count[i]==1:
                return i
        return 