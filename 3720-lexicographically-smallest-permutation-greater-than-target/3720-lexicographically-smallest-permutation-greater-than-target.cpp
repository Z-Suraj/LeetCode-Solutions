class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int cnt[26] = {};

        for (char c : s)
            cnt[c - 'a']++;

        int n = target.size();

        for (int i = n - 1; i >= 0; i--) {

            // target ke prefix ke characters remove karo
            int temp[26];
            copy(cnt, cnt + 26, temp);

            bool possible = true;

            for (int j = 0; j < i; j++) {
                if (--temp[target[j] - 'a'] < 0) {
                    possible = false;
                    break;
                }
            }

            if (!possible)
                continue;

            // Current character se bada smallest character
            for (int j = target[i] - 'a' + 1; j < 26; j++) {

                if (temp[j] > 0) {
                    string ans = target.substr(0, i);
                    ans += char('a' + j);
                    temp[j]--;

                    // Remaining characters smallest order mein
                    for (int k = 0; k < 26; k++)
                        ans += string(temp[k], char('a' + k));

                    return ans;
                }
            }
        }

        return "";
    }
};