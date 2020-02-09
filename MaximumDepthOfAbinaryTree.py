
class Solution:
    def maxDepth(self, root: TreeNode) -> int:
        if root is None:
            return 0
        maxi=[0]
        depth=0
        self.foo(root,depth,maxi)
        #print(maxi)
        return 1+maxi[0]
        
    
    def foo(self,root,depth,maxi):
        if root is None:
            return
        a=max(depth,maxi[0])
        maxi[0]=a
        # print(root.val,depth,maxi)
        self.foo(root.left,depth+1,maxi)
        self.foo(root.right,depth+1,maxi)
        