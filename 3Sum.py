class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        nums.sort()
        ans = set()
        for i,v in enumerate(nums):
            self.twoSum(nums[i+1:],-v,ans)
        return ans
    def twoSum(self,nums,target,ans):
        d = {}
        for i,v in enumerate(nums):
            if target-v in d:
                ans.add((v,target-v,-target)) #3sum wants the numbers, while 2sum wanted the indices
            d[v] = i
