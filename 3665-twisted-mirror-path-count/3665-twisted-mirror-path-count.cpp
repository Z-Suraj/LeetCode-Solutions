class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        const int MOD = 1e9 + 7;

        vector<vector<array<int, 2>>> memo(
            m, vector<array<int, 2>>(n, {-2, -2})
        );

        function<int(int, int, int)> solve =
        [&](int i, int j, int d) -> int {

            if (i >= m || j >= n) return -1;

            if (grid[i][j] == 0)
                return i * n + j;

            int &res = memo[i][j][d];

            if (res != -2) return res;

            if (d == 0)
                res = solve(i + 1, j, 1);
            else
                res = solve(i, j + 1, 0);

            return res;
        };

        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (dp[i][j] == 0) continue;

                int r = solve(i, j + 1, 0);
                int d = solve(i + 1, j, 1);

                if (r != -1) {
                    int x = r / n, y = r % n;
                    dp[x][y] = (dp[x][y] + dp[i][j]) % MOD;
                }

                if (d != -1) {
                    int x = d / n, y = d % n;
                    dp[x][y] = (dp[x][y] + dp[i][j]) % MOD;
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};