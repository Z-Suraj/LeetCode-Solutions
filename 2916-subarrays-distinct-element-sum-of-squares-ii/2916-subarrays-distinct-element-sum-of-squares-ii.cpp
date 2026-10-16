class Solution {
public:
    int sumCounts(vector<int>& nums) {
        const long long MOD = 1000000007;
        int n = nums.size();

        vector<long long> sum(4 * n, 0);
        vector<long long> sq(4 * n, 0);
        vector<long long> lazy(4 * n, 0);

        auto update = [&](auto&& self, int node, int l, int r,
                          int ql, int qr) -> void {
            if (ql > r || qr < l)
                return;

            if (ql <= l && r <= qr) {
                sq[node] = (sq[node] + 2 * sum[node]
                    + (r - l + 1LL)) % MOD;

                sum[node] = (sum[node] + (r - l + 1LL)) % MOD;
                lazy[node]++;
                return;
            }

            int mid = (l + r) / 2;

            if (lazy[node] != 0) {
                long long v = lazy[node];

                sq[node * 2] = (sq[node * 2]
                    + 2 * v * sum[node * 2]
                    + (mid - l + 1LL) * v * v) % MOD;

                sum[node * 2] = (sum[node * 2]
                    + (mid - l + 1LL) * v) % MOD;

                lazy[node * 2] += v;

                sq[node * 2 + 1] = (sq[node * 2 + 1]
                    + 2 * v * sum[node * 2 + 1]
                    + (r - mid) * v * v) % MOD;

                sum[node * 2 + 1] = (sum[node * 2 + 1]
                    + (r - mid) * v) % MOD;

                lazy[node * 2 + 1] += v;
                lazy[node] = 0;
            }

            self(self, node * 2, l, mid, ql, qr);
            self(self, node * 2 + 1, mid + 1, r, ql, qr);

            sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
            sq[node] = (sq[node * 2] + sq[node * 2 + 1]) % MOD;
        };

        vector<int> last(100001, -1);
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int p = last[nums[i]] + 1;

            update(update, 1, 0, n - 1, p, i);

            ans = (ans + sq[1]) % MOD;
            last[nums[i]] = i;
        }

        return ans;
    }
};