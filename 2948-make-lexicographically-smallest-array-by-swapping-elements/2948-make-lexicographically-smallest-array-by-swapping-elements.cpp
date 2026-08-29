class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {

        int n = nums.size();

        // Store {value, original index}
        vector<pair<int, int>> arr;

        for (int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});
        }

        // Sort according to value
        sort(arr.begin(), arr.end());

        int start = 0;

        while (start < n) {

            int end = start;

            // Find the current group
            while (end + 1 < n &&
                   arr[end + 1].first - arr[end].first <= limit) {
                end++;
            }

            // Get original indices of this group
            vector<int> indices;

            for (int i = start; i <= end; i++) {
                indices.push_back(arr[i].second);
            }

            // Sort original indices
            sort(indices.begin(), indices.end());

            // Put sorted values at sorted indices
            for (int i = 0; i < indices.size(); i++) {
                nums[indices[i]] = arr[start + i].first;
            }

            // Move to next group
            start = end + 1;
        }

        return nums;
    }
};