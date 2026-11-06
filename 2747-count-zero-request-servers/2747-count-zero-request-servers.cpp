class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        sort(logs.begin(), logs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        int qn = queries.size();
        vector<int> order(qn);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return queries[a] < queries[b];
        });

        vector<int> cnt(n + 1, 0);
        vector<int> res(qn);
        int active = 0;
        int l = 0, r = 0, m = logs.size();

        for (int idx : order) {
            int q = queries[idx];

            // add logs with time <= q
            while (r < m && logs[r][1] <= q) {
                if (cnt[logs[r][0]]++ == 0) active++;
                r++;
            }

            // remove logs with time < q - x
            while (l < r && logs[l][1] < q - x) {
                if (--cnt[logs[l][0]] == 0) active--;
                l++;
            }

            res[idx] = n - active;
        }

        return res;
    }
};