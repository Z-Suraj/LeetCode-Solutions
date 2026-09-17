class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        int ans = 1e9;
        int sum = 0, l = 0;

        vector<int> dp(n, 1e9);

        for (int r = 0; r < n; r++) {
            sum += arr[r];

            while (sum > target)
                sum -= arr[l++];

            if (sum == target) {
                int len = r - l + 1;

                if (l > 0)
                    ans = min(ans, len + dp[l - 1]);

                dp[r] = len;
            }

            if (r > 0)
                dp[r] = min(dp[r], dp[r - 1]);
        }

        return ans == 1e9 ? -1 : ans;
    }
};