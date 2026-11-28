class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> freq(n + 1, 0);
        vector<int> bonus(n + 1, 0);

        int minPrice = INT_MAX;

        for (auto& item : items) {
            freq[item[0]]++;
            minPrice = min(minPrice, item[1]);
        }

        // Count eligible free items
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j += i) {
                bonus[i] += freq[j];
            }
        }

        vector<pair<int, int>> offers;

        for (auto& item : items) {
            int factor = item[0];
            int price = item[1];

            int freeCount = bonus[factor] - 1;

            if (freeCount > 0) {
                offers.push_back({price, freeCount});
            }
        }

        sort(offers.begin(), offers.end());

        long long ans = budget / minPrice;
        long long remaining = budget;
        long long total = 0;

        for (auto& [price, count] : offers) {

            if (price >= 2LL * minPrice)
                break;

            long long buy = min((long long)count,
                                remaining / price);

            total += 2 * buy;
            remaining -= buy * price;

            ans = max(ans, total + remaining / minPrice);
        }

        return ans;
    }
};