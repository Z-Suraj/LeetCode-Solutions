class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> a(nums.rbegin(), nums.rend());

        deque<int> dq;          // indices, values strictly decreasing
        long long sumMax = 0;   // sum of suffix-max over the window
        long long sumA = 0;     // sum of a over the window
        long long ans = 0;
        int left = 0;

        for (int right = 0; right < n; right++) {
            while (!dq.empty() && a[dq.back()] <= a[right]) {
                int j = dq.back();
                dq.pop_back();
                int prev = dq.empty() ? left - 1 : dq.back();
                sumMax -= 1LL * a[j] * (j - prev);
            }
            int prev = dq.empty() ? left - 1 : dq.back();
            sumMax += 1LL * a[right] * (right - prev);
            dq.push_back(right);
            sumA += a[right];

            while (sumMax - sumA > k) {
                sumA -= a[left];
                sumMax -= a[dq.front()];     // suffix max at position left
                if (dq.front() == left) dq.pop_front();
                left++;
            }

            ans += right - left + 1;
        }
        return ans;
    }
};