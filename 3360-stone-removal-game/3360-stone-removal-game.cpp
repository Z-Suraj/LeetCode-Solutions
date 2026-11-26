class Solution {
public:
    bool canAliceWin(int n) {
        int count = 0;

        for (int i = 10; i >= 1; i--) {
            if (n < i)
                break;

            n = n - i;
            count++;
        }

        return count % 2 == 1;
    }
};