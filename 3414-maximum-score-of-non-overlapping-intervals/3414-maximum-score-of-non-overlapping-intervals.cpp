class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {

        int n = intervals.size();

        // {left, right, weight, original index}
        vector<array<long long, 4>> a(n);

        for (int i = 0; i < n; i++) {
            a[i] = {
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            };
        }

        // Sort by right endpoint
        sort(a.begin(), a.end(), [](auto &x, auto &y) {
            if (x[1] != y[1])
                return x[1] < y[1];

            return x[3] < y[3];
        });

        // dp[i][k] = best answer using first i intervals
        // and choosing at most k intervals
        vector<vector<pair<long long, vector<int>>>> dp(
            n + 1,
            vector<pair<long long, vector<int>>>(5)
        );

        for (int i = 1; i <= n; i++) {

            // Don't take current interval
            for (int k = 1; k <= 4; k++) {
                dp[i][k] = dp[i - 1][k];
            }

            // Find previous interval
            // whose right < current left
            int p = -1;

            int lo = 0;
            int hi = i - 2;

            while (lo <= hi) {

                int mid = (lo + hi) / 2;

                if (a[mid][1] < a[i - 1][0]) {
                    p = mid;
                    lo = mid + 1;
                }
                else {
                    hi = mid - 1;
                }
            }

            for (int k = 1; k <= 4; k++) {

                long long score = a[i - 1][2];

                vector<int> ids = {
                    (int)a[i - 1][3]
                };

                // Take current interval
                if (p != -1 && k > 1) {

                    score += dp[p + 1][k - 1].first;

                    for (int x : dp[p + 1][k - 1].second)
                        ids.push_back(x);

                    sort(ids.begin(), ids.end());
                }

                // Check if taking is better
                if (score > dp[i][k].first) {

                    dp[i][k] = {score, ids};
                }
                else if (score == dp[i][k].first) {

                    if (ids < dp[i][k].second) {
                        dp[i][k] = {score, ids};
                    }
                }
            }
        }

        return dp[n][4].second;
    }
};