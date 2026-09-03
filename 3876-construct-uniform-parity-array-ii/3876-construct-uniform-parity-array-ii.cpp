#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int minOdd = INT_MAX;
        int minEven = INT_MAX;

        for (int x : nums1) {
            if (x % 2 == 0) {
                minEven = min(minEven, x);
            } else {
                minOdd = min(minOdd, x);
            }
        }

        // All elements are even OR all elements are odd
        if (minOdd == INT_MAX || minEven == INT_MAX) {
            return true;
        }

        // Mixed parity:
        // We can make every element odd only if
        // the smallest odd number is smaller than
        // the smallest even number.
        return minOdd < minEven;
    }
};