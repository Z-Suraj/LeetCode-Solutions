class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        long long ans = 0;
        int mod = 1e9 + 7;
        int bits[32] = {};

        for (int n : nums) {
            for (int b = 0; b < 32; b++) {
                if (n & (1LL << b))
                    bits[b]++;
            }
        }

        for (int i = 0; i < k; i++) {
            long long x = 0;

            for (int b = 0; b < 32; b++) {
                if (bits[b] > 0) {
                    x |= (1LL << b);
                    bits[b]--;
                }
            }

            ans = (ans + x * x) % mod;
        }

        return ans;
    }
};