class Solution:
    def inorderTraversal(self, root: TreeNode) -> List[int]:
        res = []
        self.travers(root, res)
        return res
        
    def travers(self, root, res):
        if not root:
            return
        self.travers(root.left, res)
        res.append(root.val)
        self.travers(root.right, res)