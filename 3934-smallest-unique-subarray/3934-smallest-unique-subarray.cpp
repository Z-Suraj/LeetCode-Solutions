class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return n;

        using ull = unsigned long long;

        auto key = [](int a, int b) -> ull {
            return ((ull)(unsigned int)a << 32) |
                   (unsigned int)b;
        };

        vector<vector<int>> ranks;
        ranks.push_back(nums);

        for (int len = 2; len <= n; len *= 2) {
            int half = len / 2;

            unordered_map<ull, int> freq;
            vector<int> curr(n - len + 1);

            int id = 0;

            for (int i = 0; i + len <= n; i++) {
                ull sub = key(ranks.back()[i],
                              ranks.back()[i + half]);

                if (!freq.count(sub))
                    freq[sub] = ++id;

                curr[i] = freq[sub];
            }

            ranks.push_back(move(curr));
        }

        int low = 1, high = n;

        while (low < high) {
            int len = low + (high - low) / 2;

            unordered_map<ull, int> freq;

            int k = __lg(len);
            int block = 1 << k;

            for (int i = 0; i + len <= n; i++) {
                ull sub = key(ranks[k][i],
                              ranks[k][i + len - block]);

                freq[sub]++;
            }

            bool found = false;

            for (auto& p : freq) {
                if (p.second == 1) {
                    found = true;
                    break;
                }
            }

            if (found)
                high = len;
            else
                low = len + 1;
        }

        return low;
    }
};