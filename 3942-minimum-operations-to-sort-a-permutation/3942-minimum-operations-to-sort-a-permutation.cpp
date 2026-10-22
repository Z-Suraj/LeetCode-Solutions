class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int s = nums[0];
        int ans = INT_MAX;

        // Case A: cyclic increasing
        bool inc = true;
        for (int i = 0; i < n; i++) {
            if (nums[i] != (s + i) % n) { inc = false; break; }
        }
        if (inc) {
            if (s == 0) return 0;
            ans = min(ans, min(n - s, s + 2));
        }

        // Case B: cyclic decreasing
        bool dec = true;
        for (int i = 0; i < n; i++) {
            if (nums[i] != ((s - i) % n + n) % n) { dec = false; break; }
        }
        if (dec) {
            int t = (s + 1) % n;
            ans = min(ans, min(t + 1, n - t + 1));
        }

        return ans == INT_MAX ? -1 : ans;
    }
};