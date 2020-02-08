class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        if len(nums)==0:
            return 0
        if len(nums)==1:
            return 1
        
        x=nums[0]
        count=1
        i=1
        while i<len(nums):
            if nums[i]==x:
                del nums[i]
            else:
                count+=1
                x=nums[i]
                i+=1
        return count