class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int n = nums.size();
        vector<int> pre(n + 1, 0);
        for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + nums[i];

        int ans = INT_MAX;
        for (int len = l; len <= r; len++) {
            for (int i = 0; i + len <= n; i++) {
                int sum = pre[i + len] - pre[i];
                if (sum > 0) ans = min(ans, sum);
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};