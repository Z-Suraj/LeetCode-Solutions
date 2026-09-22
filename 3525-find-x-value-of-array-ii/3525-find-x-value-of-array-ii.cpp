class Solution {
public:
    int n, k;
    vector<array<long long, 5>> seg;
    vector<int> prod;

    void update(int p, int l, int r, int pos, int val) {
        if (l == r) {
            seg[p].fill(0);
            seg[p][val % k] = 1;
            prod[p] = val % k;
            return;
        }

        int m = (l + r) / 2;

        if (pos <= m)
            update(p * 2, l, m, pos, val);
        else
            update(p * 2 + 1, m + 1, r, pos, val);

        seg[p].fill(0);

        for (int x = 0; x < k; x++) {
            seg[p][x] += seg[p * 2][x];

            int r2 = (prod[p * 2] * x) % k;
            seg[p][r2] += seg[p * 2 + 1][x];
        }

        prod[p] = (prod[p * 2] * prod[p * 2 + 1]) % k;
    }

    void query(int p, int l, int r, int start,
               array<long long, 5>& ans, int& total) {

        if (r < start)
            return;

        if (l >= start) {
            // Add prefixes of this segment
            for (int x = 0; x < k; x++) {
                int rem = (total * x) % k;
                ans[rem] += seg[p][x];
            }

            total = (total * prod[p]) % k;
            return;
        }

        int m = (l + r) / 2;

        query(p * 2, l, m, start, ans, total);
        query(p * 2 + 1, m + 1, r, start, ans, total);
    }

    vector<int> resultArray(vector<int>& nums, int K,
                            vector<vector<int>>& queries) {

        n = nums.size();
        k = K;

        seg.resize(4 * n);
        prod.resize(4 * n);

        for (int i = 0; i < n; i++)
            update(1, 0, n - 1, i, nums[i]);

        vector<int> answer;

        for (auto &q : queries) {

            // Persistent update
            nums[q[0]] = q[1];
            update(1, 0, n - 1, q[0], q[1]);

            array<long long, 5> cnt{};
            int total = 1 % k;

            query(1, 0, n - 1, q[2], cnt, total);

            answer.push_back(cnt[q[3]]);
        }

        return answer;
    }
};