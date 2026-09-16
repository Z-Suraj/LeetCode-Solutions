class Solution {
public:
    int numberOfSets(int n, int k) {
        const int MOD = 1e9 + 7;

        vector<long long> dp(k + 1, 0);
        vector<long long> sum(k + 1, 0);

        dp[0] = 1;

        for (int i = 1; i < n; i++) {
            // Update from right to left
            for (int j = min(k, i); j >= 1; j--) {
                sum[j] = (sum[j] + dp[j - 1]) % MOD;
                dp[j] = (dp[j] + sum[j]) % MOD;
            }
        }

        return dp[k];
    }
};