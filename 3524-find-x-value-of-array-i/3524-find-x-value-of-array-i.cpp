class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);

        // dp[r] = number of subarrays ending at previous position
        // whose product % k == r
        vector<long long> dp(k, 0);

        for (int num : nums) {
            int x = num % k;

            vector<long long> newDp(k, 0);

            // Start a new subarray with nums[i]
            newDp[x]++;

            // Extend previous subarrays
            for (int r = 0; r < k; r++) {
                int newR = (r * x) % k;
                newDp[newR] += dp[r];
            }

            dp = newDp;

            // Every subarray ending here is one valid operation
            for (int r = 0; r < k; r++) {
                ans[r] += dp[r];
            }
        }

        return ans;
    }
};