class Solution {
public:

    // Function returns:
    // {sum of subtree, number of nodes in subtree}
    pair<int, int> dfs(TreeNode* root, int &ans) {

        // If node is NULL
        if (root == NULL) {
            return {0, 0};
        }

        // Get sum and count from left subtree
        pair<int, int> left = dfs(root->left, ans);

        // Get sum and count from right subtree
        pair<int, int> right = dfs(root->right, ans);

        // Calculate total sum of current subtree
        int sum = root->val + left.first + right.first;

        // Calculate total number of nodes
        int count = 1 + left.second + right.second;

        // Calculate average
        int average = sum / count;

        // Check if current node value == average
        if (root->val == average) {
            ans++;
        }

        // Return sum and count to parent
        return {sum, count};
    }

    int averageOfSubtree(TreeNode* root) {

        int ans = 0;

        // Start DFS
        dfs(root, ans);

        return ans;
    }
};